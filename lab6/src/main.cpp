#include <iostream>
#include <cstring>
#include <lab6/hrms.hpp>

using namespace std;

const string commands[] = {"list", "add", "changeSalary", "load", "save", "exit"};
HRMS hrms_system;

int getCommand();

int main(int argc, char const * argv[]) {

    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        cout << "Usage: lab6" << endl;
        cout << "HRMS System with Employee class" << endl << endl;
        return 0;
    }

    cout << "Welcome to HRMS System!" << endl;
    cout << "Author: Alber Mouhoubi" << endl << endl;

    while(getCommand()) {
    }

    return 0;
}

int getCommand() {

    string input;
    cout << "$: ";
    cin >> input;

    if (input.compare(commands[0]) == 0) {
        int choice;
        cout << "Choose what to list:" << endl;
        cout << "1. All employees" << endl;
        cout << "2. Department employees" << endl;
        cout << "3. Salaries" << endl;
        cout << "Choice: ";
        cin >> choice;
        cout << endl;

        string d_id;
        switch(choice) {
            case 1:
                hrms_system.listEmployees();
                break;
            case 2:
                cout << "Department ID: ";
                cin >> d_id;
                hrms_system.printDepartment(d_id);
                break;
            case 3:
                char sort;
                cout << "Sorted? (Y): ";
                cin >> sort;
                if (sort == 'Y') {
                    hrms_system.printSalariesSorted();
                } else {
                    hrms_system.printSalaries();
                }
                break;
            default:
                cout << "Unknown choice!" << endl;
        }
        return 1;
    } else if (input.compare(commands[1]) == 0) {
        string id, name, surname, department_id, position;
        int salary;
        cout << "Add employee:" << endl;
        cout << "ID: ";
        cin >> id;
        cout << "Name: ";
        cin >> name;
        cout << "surname: ";
        cin >> surname;
        cout << "department_id: ";
        cin >> department_id;
        cout << "position: ";
        cin >> position;
        cout << "salary: ";
        cin >> salary;
        int result;
        result = hrms_system.addEmployee(Employee(id, name, surname, department_id, position), department_id, salary);
        if (result == 0) {
            cout << "Failed." << endl;
        } else {
            cout << "Added!" << endl;
        }
        return 1;
    } else if (input.compare(commands[2]) == 0) {
        string id;
        int salary;
        cout << "Change salary" << endl;
        cout << "ID: ";
        cin >> id;
        salary = hrms_system.getSalary(id);
        if (salary == -1) {
            cout << "No employee of id: " << id << endl;
            return 1;
        }
        cout << "Current: " << salary << endl;
        cout << "New: ";
        cin >> salary;
        if (hrms_system.changeSalary(id, salary) == 0) {
            cout << "Failed." << endl;
        } else {
            cout << "Success" << endl;
        }
        return 1;

    } else if (input.compare(commands[3]) == 0) {
        cout << "Load from database" << endl;
        string name;
        cout << "Enter database name: ";
        cin >> name;
        hrms_system.loadFromDatabase(name);
        return 1;
    } else if (input.compare(commands[4]) == 0) {
        cout << "Save to database" << endl;
        string name;
        cout << "Enter database name: ";
        cin >> name;
        hrms_system.saveToDatabase(name);
        return 1;
    } else if (input.compare(commands[5]) == 0) {
        cout << "Exiting!" << endl;
        return 0;
    } else {
        cout << "Unknown command!" << endl;
        return 1;
    }

}
