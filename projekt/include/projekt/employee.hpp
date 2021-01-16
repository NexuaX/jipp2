/* Employee class header
** Author: Albert Mouhoubi
*/
#ifndef EMPLOYEE_CLASS
#define EMPLOYEE_CLASS

#include <string>
#include <sqlite3/sqlite3.h>
using namespace std;

class Employee {

private:
    string id;
    string name;
    string surname;
    string department_id;
    string position;
public:
    Employee(string id, string name, string surname, string department_id, string position);

    string getID();
    string getName();
    string getSurname();
    string getDepartmentID();
    string getPosition();

    string setID(string new_id);
    string setName(string new_name);
    string setSurname(string new_surname);
    string setDepartmentID(string new_department_id);
    string setPosition(string new_position);
};

#endif