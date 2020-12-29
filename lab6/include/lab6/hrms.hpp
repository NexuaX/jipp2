/* HRMS class header
** Author: Albert Mouhoubi
*/
#ifndef HRMS_CLASS
#define HRMS_CLASS

#include <vector>
#include <map>
#include <lab6/employee.hpp>
#include <sqlite3/sqlite3.h>

using namespace std;

class HRMS {
private:
    vector<Employee> employee_list;
    map<string, vector<string>> department_employee_map;
    map<string, double> employee_salary;
    sqlite3 * db;
public:
    int addEmployee(Employee emp, string department_id, double salary);
    void printDepartment(string department_id);
    int changeSalary(string emp_id, double new_salary);
    void printSalaries();
    void printSalariesSorted();
    void listEmployees();
    int getSalary(string id);

    // dodatkowe metody sqlite3
    int loadFromDatabase(string file_name);
    int saveToDatabase(string file_name);

    friend int callbackLoad(void *data, int argc, char **argv, char **azColName);
    friend int callbackSave(void *data, int argc, char **argv, char **azColName);
};

#endif