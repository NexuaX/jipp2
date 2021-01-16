/* HRMS class header
** Author: Albert Mouhoubi
*/
#ifndef HRMS_CLASS
#define HRMS_CLASS

#include <vector>
#include <map>
#include <projekt/employee.hpp>
#include <projekt/command.hpp>
#include <projekt/user.hpp>
#include <sqlite3/sqlite3.h>

using namespace std;

class HRMS {
private:
    vector<Employee> employee_list;
    map<string, vector<string>> department_employee_map;
    map<string, double> employee_salary;
    sqlite3 * db;
    User user;
    string db_name;
    HRMS() {};
public:
    static vector<Command> commands;

    HRMS(HRMS const &) = delete;
    void operator=(HRMS const &) = delete;
    static HRMS & getInstance();

    int prompt();
    int init();
    int createConfiguration();

    int addEmployee(Employee emp, string department_id, double salary);
    int delEmployee(string id);
    Employee getEmployee(string id);
    User getUser();
    int updateID(string old_id, string new_id);
    int updateName(string id, string new_name);
    int updateSurname(string id, string new_surname);
    int updateDepID(string id, string new_dep_id);
    int updatePosition(string id, string new_position);
    void printDepartment(string department_id);
    int updateSalary(string id, double new_salary);
    void printSalaries();
    void printSalariesSorted();
    void listEmployees();
    int getSalary(string id);
    
    // Danger Zone
    int updateDatabaseName(string new_name, string user, string password);
    int updateUsername(string new_username, string user, string password);
    int updatePassword(string new_password, string user, string password);
    int deleteAllEmployees();

    // dodatkowe metody sqlite3
    int closeConnection();
    int loadFromDatabase();
    int saveToDatabase();

    friend int callbackLoad(void *data, int argc, char **argv, char **azColName);
    friend int callbackSave(void *data, int argc, char **argv, char **azColName);
};

#endif