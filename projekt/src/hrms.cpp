/* HRMS class implementation
** Author: Albert Mouhoubi
*/
#include <projekt/hrms.hpp>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sha256.h>

using namespace std;

int help(), list(), add(), del(), change(), load(), save(), danger_zone(), exit_hrms();

vector<Command> HRMS::commands = {
    Command("help", help),
    Command("list", list),
    Command("add", add),
    Command("delete", del),
    Command("change", change),
    Command("load", load),
    Command("save", save),
    Command("danger_zone", danger_zone),
    Command("exit", exit_hrms)
};

HRMS & HRMS::getInstance() {
    static HRMS instance;

    return instance;
}

int HRMS::prompt() {
    string input, flush;
    getline(cin, flush);
    flush.clear();
    cout << "$: ";
    cin >> input;

    for (Command & cmd : commands) {
        if (cmd == input) return cmd.func();
    }
    cout << "Command not found! Type 'help' for available list." << endl;
    return 1;
}

int HRMS::init() {
    cout << "Initializing.." << endl;
    ifstream conf_file("conf.cfg");
    if (!conf_file.good()) {
        conf_file.close();
        cout << "conf.cfg file missing." << endl;
        cout << "create one? (Y/n): ";
        string ans;
        cin >> ans;
        if (ans.at(0) == 'Y') {
            this->createConfiguration();
        } else {
            exit_hrms();
            return 0;
        }
        conf_file.open("conf.cfg");
    }
    string line;
    conf_file >> line;
    string database_name = line.substr(line.find('=')+1);
    conf_file >> line;
    string username_hash = line.substr(line.find('=')+1);
    conf_file >> line;
    string password_hash = line.substr(line.find('=')+1);
    conf_file >> line;
    string hash = line.substr(line.find('=')+1);

    cout << endl;

    string user, password;
    int counter = 1, flag = 1;
    while (flag) {
        cout << "Login to access Database: " << counter << " of 3" << endl;
        cout << "Login: ";
        cin >> user;
        cout << "Password: ";
        cin >> password;

        string user_sha = sha256(user);
        string password_sha = sha256(password);

        if (user_sha.compare(username_hash) != 0 || password_sha.compare(password_hash) != 0) {
            counter++;
            if (counter == 4) {
                break;
            }
            continue;
        }
        string check_hash = sha256(user + "secret_code" + password);
        if (check_hash.compare(hash) != 0) {
            cout << "Unauthorized conf.cfg changes. Aborted." << endl;
            break;
        }

        this->user.password = password_sha;
        this->user.username = user_sha;

        flag = 0;
    }

    if (flag) {
        cout << "Login failed." << endl;
        exit_hrms();
        return 0;
    }

    int result = sqlite3_open((database_name).c_str(), &db);

    if (result) {
        cout << "Database open error! " << sqlite3_errmsg(db) << endl;
        exit_hrms();
        return 0;
    }

    this->db_name = database_name;

    cout << "Logged successfully!" << endl;

    cout << "Loading data from database.." << endl;

    this->loadFromDatabase();

    cout << endl;

    return 1;
}

int HRMS::createConfiguration() {
    ofstream conf_file("conf.cfg");
    if (!conf_file.good()) {
        cout << "Errors during creation!" << endl;
        exit_hrms();
        return 0;
    }
    string database_name, username, password;
    cout << "Database file name: ";
    cin >> database_name;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;
    conf_file << "DATABASE=" << database_name << endl;
    conf_file << "USER=" << sha256(username) << endl;
    conf_file << "PASSWORD=" << sha256(password) << endl;
    conf_file << "HASH=" << sha256(username + "secret_code" + password) << endl;
    conf_file.close();
    cout << "file created." << endl;

    return 0;
}

int HRMS::addEmployee(Employee emp, string department_id, double salary) {
    // check if emp exist
    if (employee_salary.count(emp.getID()) == 1) {
        return 0;
    }
    // check salary
    if (salary < 0) {
        return 0;
    }
    // add emp to list, department and salary map
    employee_list.push_back(emp);
    department_employee_map[department_id].push_back(emp.getID());
    employee_salary[emp.getID()] = salary;

    return 1;
}

int HRMS::delEmployee(string id) {
    // check if emp exist
    if (employee_salary.count(id) == 0) {
        return 0;
    }

    size_t i;
    for (i = 0; i < employee_list.size(); i++) {
        if (employee_list[i].getID() == id) break;
    }
    employee_salary.erase(id);
    string dep_id = employee_list[i].getDepartmentID();
    auto & temp = department_employee_map[dep_id];
    employee_list.erase(employee_list.begin()+i);
    for (i = 0; i < temp.size(); i++) {
        if (temp[i] == id) break;
    }
    temp.erase(temp.begin()+i);
    if (temp.size() == 0) {
        department_employee_map.erase(dep_id);
    }

    return 1;
}

Employee HRMS::getEmployee(string id) {
    for (Employee & emp : employee_list) {
        if (emp.getID() == id) return emp;
    }
    return Employee(id, "dont exist", "-", "-", "-");
}

User HRMS::getUser() {
    return this->user;
}

int HRMS::updateID(string old_id, string new_id) {
    if (employee_salary.count(new_id) == 1) {
        return 0;
    }
    string dep_id;
    for (auto & emp : employee_list) {
        if (emp.getID() == old_id) {
            emp.setID(new_id);
            dep_id = emp.getDepartmentID();
            break;
        } 
    }
    employee_salary[new_id] = employee_salary[old_id];
    employee_salary.erase(old_id);
    for (auto & id : department_employee_map[dep_id]){
        if (id == old_id) {
            id = new_id;
            break;
        }
    }
    return 1;
}

int HRMS::updateName(string id, string new_name) {
    for (auto & emp : employee_list) {
        if (emp.getID() == id) {
            emp.setName(new_name);
            break;
        } 
    }
    return 1;
}

int HRMS::updateSurname(string id, string new_surname) {
    for (auto & emp : employee_list) {
        if (emp.getID() == id) {
            emp.setSurname(new_surname);
            break;
        } 
    }
    return 1;
}

int HRMS::updateDepID(string id, string new_dep_id) {
    string old_dep_id;
    for (auto & emp : employee_list) {
        if (emp.getID() == id) {
            old_dep_id = emp.getDepartmentID();
            emp.setDepartmentID(new_dep_id);
            break;
        }
    }
    auto & temp = department_employee_map[old_dep_id];
    size_t i;
    for (i = 0; i < temp.size(); i++) {
        if (temp[i] == id) break;
    }
    temp.erase(temp.begin()+i);
    department_employee_map[new_dep_id].push_back(id);
    if (temp.size() == 0) {
        department_employee_map.erase(old_dep_id);
    }
    return 1;
}

int HRMS::updatePosition(string id, string new_pos) {
    for (auto & emp : employee_list) {
        if (emp.getID() == id) {
            emp.setPosition(new_pos);
            break;
        }
    }
    return 1;
}

void HRMS::printDepartment(string department_id) {
    // check if department exist
    if (department_employee_map.count(department_id) == 0) {
        cout << "Department " << department_id << " does NOT exist!" << endl;
        return;
    }
    // print employees
    // TODO: print all employee info
    cout << "IDs: ";
    for (auto i : department_employee_map[department_id]) {
        cout << i << ", ";
    }
    cout << "Done." << endl;
}

int HRMS::updateSalary(string id, double salary) {
    // check salary
    if (salary < 0) {
        return 0;
    } 
    // change salary of emp of id emp_id
    employee_salary[id] = salary;

    return 1;
}

void HRMS::printSalaries() {
    // check if there is anything to print
    if (employee_salary.size() == 0) {
        cout << "No employees to print!" << endl;
        return;
    }
    // print one by one
    // TODO: print employee's all info
    auto it = employee_salary.begin();
    for ( ; it != employee_salary.end(); it++) {
        cout << "ID: " <<it->first << ", " << it->second << endl;
    }
    cout << "Done." << endl;
}

void HRMS::printSalariesSorted() {
    // check if there is anything to print
    if (employee_salary.size() == 0) {
        cout << "No employees to print!" << endl;
        return;
    }
    // print one by one
    // TODO: print employee's all info
    bool comp(pair<string, double> & a, pair<string, double> & b);

    vector<pair<string, double>> temp;

    for (auto & i: employee_salary) {
        temp.push_back(i);
    }
    sort(temp.begin(), temp.end(), comp);

    for (auto & i: temp) {
        cout << i.first << " " << i.second << endl;
    }

    cout << "Done." << endl;
}

void HRMS::listEmployees() {

    for (auto & i : this->employee_list) {

        cout << "ID, name    : " << i.getID() << " | " << i.getName() << " " << i.getSurname() << endl;
        cout << "Dep_ID, pos : " << i.getDepartmentID() << " | " << i.getPosition() << " " << this->getSalary(i.getID()) << endl << endl;

    }

    cout << "Total of " << this->employee_list.size() << endl;

}

int HRMS::getSalary(string id) {

    if (employee_salary.count(id) == 0) return -1;
    return this->employee_salary[id];

}

bool comp(pair<string, double> & a, pair<string, double> & b) {
    return a.second < b.second;
}

int HRMS::loadFromDatabase() {

    int result;

    string stmn = "CREATE TABLE IF NOT EXISTS employees("
                "id text,"
                "name text,"
                "surname text,"
                "department_id text,"
                "position text,"
                "salary int"
                ");";

    result = sqlite3_exec(db, stmn.c_str(), 0, 0, 0);
    if (result != SQLITE_OK) {
        cout << "Database exec error! (CREATE)" << endl;
        return 1;
    }

    stmn = "SELECT * FROM employees;";
    sqlite3_stmt * ppStmn;
    result = sqlite3_prepare_v2(db, stmn.c_str(), stmn.length(), &ppStmn, NULL);
    if (result != SQLITE_OK) {
        cout << "PREPARE stmt error! code: " << result << endl;
        return 1;
    }

    int count = 0;
    while (sqlite3_step(ppStmn) == SQLITE_ROW) {

        // cout << sqlite3_column_text(ppStmn, 0) << endl;

        Employee temp = Employee(
            string(reinterpret_cast<const char*>(sqlite3_column_text(ppStmn, 0))),
            string(reinterpret_cast<const char*>(sqlite3_column_text(ppStmn, 1))),
            string(reinterpret_cast<const char*>(sqlite3_column_text(ppStmn, 2))),
            string(reinterpret_cast<const char*>(sqlite3_column_text(ppStmn, 3))),
            string(reinterpret_cast<const char*>(sqlite3_column_text(ppStmn, 4)))
        );
        this->addEmployee(temp, string(reinterpret_cast<const char*>(sqlite3_column_text(ppStmn, 3))), sqlite3_column_int(ppStmn, 5));
        count++;
    }

    sqlite3_finalize(ppStmn);

    cout << "Loaded " << count << " employees" << endl;

    return 0;

}

int HRMS::saveToDatabase() {

    int result;

    string stmn = "DROP TABLE IF EXISTS employees;";

    //char * error;
    result = sqlite3_exec(db, stmn.c_str(), 0, 0, 0);
    if (result != SQLITE_OK) {
        cout << "Database exec error! (DROP)" << endl;
        //cout << error << endl;
    }

    stmn = "CREATE TABLE employees("
                "id text,"
                "name text,"
                "surname text,"
                "department_id text,"
                "position text,"
                "salary int"
                ");";

    result = sqlite3_exec(db, stmn.c_str(), 0, 0, 0);
    if (result != SQLITE_OK) {
        cout << "Database exec error! (CREATE)" << endl;
        return 1;
    }

    stmn = "INSERT INTO employees VALUES(@id, @name, @surname, @department_id, @position, @salary);";

    sqlite3_stmt * ppStmn;
    result = sqlite3_prepare_v2(db, stmn.c_str(), stmn.length(), &ppStmn, NULL);
    if (result != SQLITE_OK) {
        cout << "PREPARE stmt error! code: " << result << endl;
        cout << sqlite3_errmsg(db) << endl;
        return 1;
    }

    for (auto & i : employee_list) {
        int salary = employee_salary[i.getID()];
        sqlite3_bind_text(ppStmn, 1, i.getID().c_str(), i.getID().length(), SQLITE_TRANSIENT);
        sqlite3_bind_text(ppStmn, 2, i.getName().c_str(), i.getName().length(), SQLITE_TRANSIENT);
        sqlite3_bind_text(ppStmn, 3, i.getSurname().c_str(), i.getSurname().length(), SQLITE_TRANSIENT);
        sqlite3_bind_text(ppStmn, 4, i.getDepartmentID().c_str(), i.getDepartmentID().length(), SQLITE_TRANSIENT);
        sqlite3_bind_text(ppStmn, 5, i.getPosition().c_str(), i.getPosition().length(), SQLITE_TRANSIENT);
        sqlite3_bind_int(ppStmn, 6, salary);

        // cout << sqlite3_expanded_sql(ppStmn) << endl;

        result = sqlite3_step(ppStmn);
        if (result != SQLITE_DONE) {
            cout << "STEP error!" << endl;
            cout << sqlite3_errmsg(db) << endl;
        } else {
            cout << "written id " << i.getID().c_str() << endl;
        }
        sqlite3_clear_bindings(ppStmn);
        sqlite3_reset(ppStmn);
    }

    sqlite3_finalize(ppStmn);

    cout << "Employees saved to database!" << endl;

    return 0;

}

int HRMS::closeConnection() {
    sqlite3_close(db);
    return 1;
}

int HRMS::updateDatabaseName(string new_name, string user, string password) {
    ofstream conf_file("conf.cfg");
    if (!conf_file.good()) {
        cout << "Errors during opening!" << endl;
        exit_hrms();
        return 0;
    }
    conf_file << "DATABASE=" << new_name << endl;
    conf_file << "USER=" << this->user.username << endl;
    conf_file << "PASSWORD=" << this->user.password << endl;
    conf_file << "HASH=" << sha256(user + "secret_code" + password) << endl;
    conf_file.close();

    this->closeConnection();

    int result = sqlite3_open((new_name).c_str(), &db);

    if (result) {
        cout << "Database open error! " << sqlite3_errmsg(db) << endl;
        exit_hrms();
        return 0;
    }

    this->db_name = new_name;

    cout << "Database opened successfully!" << endl;

    return 1;
}

int HRMS::updateUsername(string new_user, string user, string password) {
    ofstream conf_file("conf.cfg");
    if (!conf_file.good()) {
        cout << "Errors during opening!" << endl;
        exit_hrms();
        return 0;
    }
    string new_user_sha = sha256(new_user);
    conf_file << "DATABASE=" << this->db_name << endl;
    conf_file << "USER=" << new_user_sha << endl;
    conf_file << "PASSWORD=" << this->user.password << endl;
    conf_file << "HASH=" << sha256(new_user + "secret_code" + password) << endl;
    conf_file.close();

    this->user.username = new_user_sha;

    return 1;
}

int HRMS::updatePassword(string new_pass, string user, string password) {
    ofstream conf_file("conf.cfg");
    if (!conf_file.good()) {
        cout << "Errors during opening!" << endl;
        exit_hrms();
        return 0;
    }
    string new_pass_sha = sha256(new_pass);
    conf_file << "DATABASE=" << this->db_name << endl;
    conf_file << "USER=" << this->user.username << endl;
    conf_file << "PASSWORD=" << new_pass_sha << endl;
    conf_file << "HASH=" << sha256(user + "secret_code" + new_pass) << endl;
    conf_file.close();

    this->user.password = new_pass_sha;

    return 1;
}

int HRMS::deleteAllEmployees() {
    employee_list.clear();
    department_employee_map.clear();
    employee_salary.clear();

    return 1;
}

int help() {
    cout << "Available commands: ";
    for (Command & cmd : HRMS::commands) {
        cout << cmd.getName() << ", ";
    }
    cout << endl;
    return 1;
}

int list() {
    int choice;
    cout << "Choose what to list:" << endl;
    cout << "1. All employees" << endl;
    cout << "2. Department employees" << endl;
    cout << "3. Salaries" << endl;
    cout << "Choice: ";
    cin >> choice;
    cout << endl;

    string dep_id;
    switch(choice) {
        case 1:
            HRMS::getInstance().listEmployees();
            break;
        case 2:
            cout << "Department ID: ";
            cin >> dep_id;
            HRMS::getInstance().printDepartment(dep_id);
            break;
        case 3:
            char sort;
            cout << "Sorted? (Y): ";
            cin >> sort;
            if (sort == 'Y') {
                HRMS::getInstance().printSalariesSorted();
            } else {
                HRMS::getInstance().printSalaries();
            }
            break;
        default:
            cout << "Unknown choice!" << endl;
    }
    return 1;
}

int add() {
    string id, name, surname, department_id, position;
    int salary;
    cout << "Add employee:" << endl;
    cout << "ID: ";
    cin >> id;
    cout << "Name: ";
    cin >> name;
    cout << "Surname: ";
    cin >> surname;
    cout << "Dep_ID: ";
    cin >> department_id;
    cout << "Position: ";
    cin >> position;
    cout << "Salary: ";
    cin >> salary;
    int result;
    result = HRMS::getInstance().addEmployee(Employee(id, name, surname, department_id, position), department_id, salary);
    if (result == 0) {
        cout << "Failed." << endl;
    } else {
        cout << "Added!" << endl;
    }
    return 1;
}

int del() {
    string id;
    cout << "Delete employee:" << endl;
    cout << "ID: ";
    cin >> id;
    int result;
    result = HRMS::getInstance().delEmployee(id);
    if (result == 0) {
        cout << "Failed." << endl;
    } else {
        cout << "Deleted!" << endl;
    }
    return 1;
}

int change() {
    string id;
    cout << "Change employee" << endl;
    cout << "ID: ";
    cin >> id;
    Employee emp = HRMS::getInstance().getEmployee(id);
    if (emp.getName() == "dont exist") {
        cout << "No employee of id: " << id << endl;
        return 1;
    }
    cout << endl;
    cout << "Current: " << endl;
    cout << "ID, name    : " << emp.getID() << " | " << emp.getName() << " " << emp.getSurname() << endl;
    cout << "Dep_ID, pos : " << emp.getDepartmentID() << " | " << emp.getPosition() << endl;
    cout << "Salary      : " << HRMS::getInstance().getSalary(emp.getID()) << endl << endl;

    int choice;
    cout << "What to change?" << endl;
    cout << "0. All" << endl;
    cout << "1. ID" << endl << "2. name" << endl << "3. surname" << endl;
    cout << "4. Dep_ID" << endl << "5. pos" << endl << "6. salary" << endl;
    cout << "Choice: ";
    cin >> choice;

    cout << endl;

    string new_id, name, surname, dep_id, pos;
    int salary;
    int result;

    switch(choice) {
        case 0:
            cout << "New ID: ";
            cin >> new_id;
            cout << "New name: ";
            cin >> name;
            cout << "New surname: ";
            cin >> surname;
            cout << "New Dep_ID: ";
            cin >> dep_id;
            cout << "New pos: ";
            cin >> pos;
            cout << "New salary: ";
            cin >> salary;
            result = HRMS::getInstance().updateID(id, new_id);
            if (result == 0) {
                cout << "Failed." << endl;
            } else {
                cout << "Success." << endl;
                id = new_id;
            }
            result = HRMS::getInstance().updateName(id, name);
            if (result == 0) {
                cout << "Failed." << endl;
            } else {
                cout << "Success." << endl;
            }
            result = HRMS::getInstance().updateSurname(id, surname);
            if (result == 0) {
                cout << "Failed." << endl;
            } else {
                cout << "Success." << endl;
            }
            result = HRMS::getInstance().updateDepID(id, dep_id);
            if (result == 0) {
                cout << "Failed." << endl;
            } else {
                cout << "Success." << endl;
            }
            result = HRMS::getInstance().updatePosition(id, pos);
            if (result == 0) {
                cout << "Failed." << endl;
            } else {
                cout << "Success." << endl;
            }
            result = HRMS::getInstance().updateSalary(id, salary);
            if (result == 0) {
                cout << "Failed." << endl;
            } else {
                cout << "Success." << endl;
            }
            break;
        case 1:
            cout << "New ID: ";
            cin >> new_id;
            result = HRMS::getInstance().updateID(id, new_id);
            if (result == 0) {
                cout << "Failed." << endl;
            } else {
                cout << "Success." << endl;
            }
            break;
        case 2:
            cout << "New name: ";
            cin >> name;
            result = HRMS::getInstance().updateName(id, name);
            if (result == 0) {
                cout << "Failed." << endl;
            } else {
                cout << "Success." << endl;
            }
            break;
        case 3:
            cout << "New surname: ";
            cin >> surname;
            result = HRMS::getInstance().updateSurname(id, surname);
            if (result == 0) {
                cout << "Failed." << endl;
            } else {
                cout << "Success." << endl;
            }
            break;
        case 4:
            cout << "New Dep_ID: ";
            cin >> dep_id;
            result = HRMS::getInstance().updateDepID(id, dep_id);
            if (result == 0) {
                cout << "Failed." << endl;
            } else {
                cout << "Success." << endl;
            }
            break;
        case 5:
            cout << "New pos: ";
            cin >> pos;
            result = HRMS::getInstance().updatePosition(id, pos);
            if (result == 0) {
                cout << "Failed." << endl;
            } else {
                cout << "Success." << endl;
            }
            break;
        case 6:
            cout << "New salary: ";
            cin >> salary;
            result = HRMS::getInstance().updateSalary(id, salary);
            if (result == 0) {
                cout << "Failed." << endl;
            } else {
                cout << "Success." << endl;
            }
            break;
        default:
            cout << "Unknown choice!" << endl;
    }

    return 1;
}

int load() {
    cout << "Load from database" << endl;
    HRMS::getInstance().loadFromDatabase();
    return 1;
}

int save() {
    cout << "Save to database" << endl;
    HRMS::getInstance().saveToDatabase();
    return 1;
}

int danger_zone() {
    cout << "CAUTION! These are dangerous functions. Use with care." << endl;
    cout << "1. Change database name" << endl;
    cout << "2. Change username" << endl;
    cout << "3. Change password" << endl;
    cout << "4. Delete all employees" << endl;

    int choice; 
    cout << "Choice: ";
    cin >> choice;

    string change;
    string user_confirm, pass_confirm;
    string pass = HRMS::getInstance().getUser().password;
    string user = HRMS::getInstance().getUser().username;
    int result;

    switch(choice) {
        case 1:
            cout << "Enter new database name: ";
            cin >> change;
            cout << "Typed: " << change << endl;

            cout << "Confirm with login and password: ";
            cin >> user_confirm >> pass_confirm;

            if (pass.compare(sha256(pass_confirm)) != 0 || user.compare(sha256(user_confirm)) != 0) {
                cout << "Wrong credentials. Aborted." << endl;
                return 1;
            }
            result = HRMS::getInstance().updateDatabaseName(change, user_confirm, pass_confirm);
            if (result == 0) {
                cout << "Failed." << endl;
            }
            cout << "Success." << endl;
            cout << "Remember to save data to new database!" << endl;
            break;
        case 2:
            cout << "Enter new username: ";
            cin >> change;
            cout << "Typed: " << change << endl;

            cout << "Confirm with current login and password: ";
            cin >> user_confirm >> pass_confirm;

            if (pass.compare(sha256(pass_confirm)) != 0 || user.compare(sha256(user_confirm)) != 0) {
                cout << "Wrong credentials. Aborted." << endl;
                return 1;
            }
            result = HRMS::getInstance().updateUsername(change, user_confirm, pass_confirm);
            if (result == 0) {
                cout << "Failed." << endl;
            }
            cout << "Success." << endl;
            break;
        case 3:
            cout << "Enter new password: ";
            cin >> change;
            cout << "Typed: " << change << endl;

            cout << "Confirm with login and current password: ";
            cin >> user_confirm >> pass_confirm;

            if (pass.compare(sha256(pass_confirm)) != 0 || user.compare(sha256(user_confirm)) != 0) {
                cout << "Wrong credentials. Aborted." << endl;
                return 1;
            }
            result = HRMS::getInstance().updatePassword(change, user_confirm, pass_confirm);
            if (result == 0) {
                cout << "Failed." << endl;
            }
            cout << "Success." << endl;
            break;
        case 4:
            cout << "You are about to delete all employees!" << endl;
            cout << "Confirm with login and password: ";
            cin >> user_confirm >> pass_confirm;

            if (pass.compare(sha256(pass_confirm)) != 0 || user.compare(sha256(user_confirm)) != 0) {
                cout << "Wrong credentials. Aborted." << endl;
                return 1;
            }
            result = HRMS::getInstance().deleteAllEmployees();
            if (result == 0) {
                cout << "Failed." << endl;
            }
            cout << "Success." << endl;
            break;
        default:
            cout << "Unknown choice!" << endl;
            break;
    }
    return 1;

}

int exit_hrms() {
    HRMS::getInstance().closeConnection();
    cout << "Exiting!" << endl;
    exit(0);
}
