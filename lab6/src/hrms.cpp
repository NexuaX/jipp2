/* HRMS class implementation
** Author: Albert Mouhoubi
*/
#include <lab6/hrms.hpp>
#include <iostream>
#include <algorithm>

using namespace std;

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

void HRMS::printDepartment(string department_id) {
    // check if department exist
    if (department_employee_map.count(department_id) == 0) {
        cout << "Department " << department_id << " does NOT exist!" << endl;
        return;
    }
    // print employees
    // TODO: print all employee info
    for (auto i : department_employee_map[department_id]) {
        cout << i << " ";
    }
    cout << "Done." << endl;
}

int HRMS::changeSalary(string emp_id, double salary) {
    // check if emp exist
    if (employee_salary.count(emp_id) == 0) {
        return 0;
    }
    // check salary
    if (salary < 0) {
        return 0;
    } 
    // change salary of emp of id emp_id
    employee_salary[emp_id] = salary;

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
        cout << it->first << " " << it->second << endl;
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

        cout << i.getID() << ": " << i.getName() << " " << i.getSurname() << endl;
        cout << i.getDepartmentID() << " " << i.getPosition() << " " << this->getSalary(i.getID()) << endl << endl;

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

int HRMS::loadFromDatabase(string file_name) {

    int result = sqlite3_open((file_name + ".db").c_str(), &db);

    if (result) {
        cout << "Database open error! " << sqlite3_errmsg(db) << endl;
        return 1;
    } else {
        cout << "Database opened successfully!" << endl;
    }

    string stmn = "SELECT * FROM employees;";
    sqlite3_stmt * ppStmn;
    result = sqlite3_prepare_v2(db, stmn.c_str(), stmn.length(), &ppStmn, NULL);
    if (result != SQLITE_OK) {
        cout << "PREPARE stmt error! code: " << result << endl;
        return 1;
    }

    int count = 0;
    while (sqlite3_step(ppStmn) == SQLITE_ROW) {

        cout << sqlite3_column_text(ppStmn, 0) << endl;

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

    sqlite3_close(db);

    return 0;

}

int HRMS::saveToDatabase(string file_name) {

    int result = sqlite3_open((file_name + ".db").c_str(), &db);

    if (result) {
        cout << "Database open error! " << sqlite3_errmsg(db) << endl;
        return 1;
    } else {
        cout << "Database opened successfully!" << endl;
    }

    string stmn = "DROP TABLE IF EXISTS employees;";

    char * error;
    result = sqlite3_exec(db, stmn.c_str(), 0, 0, &error);
    if (result != SQLITE_OK) {
        cout << "Database exec error! (DROP)" << endl;
        cout << error << endl;
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

    cout << employee_list.size() << endl;

    for (auto & i : employee_list) {
        int salary = employee_salary[i.getID()];
        sqlite3_bind_text(ppStmn, 1, i.getID().c_str(), i.getID().length(), SQLITE_TRANSIENT);
        sqlite3_bind_text(ppStmn, 2, i.getName().c_str(), i.getName().length(), SQLITE_TRANSIENT);
        sqlite3_bind_text(ppStmn, 3, i.getSurname().c_str(), i.getSurname().length(), SQLITE_TRANSIENT);
        sqlite3_bind_text(ppStmn, 4, i.getDepartmentID().c_str(), i.getDepartmentID().length(), SQLITE_TRANSIENT);
        sqlite3_bind_text(ppStmn, 5, i.getPosition().c_str(), i.getPosition().length(), SQLITE_TRANSIENT);
        sqlite3_bind_int(ppStmn, 6, salary);

        cout << sqlite3_expanded_sql(ppStmn) << endl;

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

    sqlite3_close(db);

    cout << "Employees saved to database!" << endl;

    return 0;

}
