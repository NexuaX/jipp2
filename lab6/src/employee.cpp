/* Employee class implementation
** Author: Albert Mouhoubi
*/
#include <lab6/employee.hpp>

using namespace std;

Employee::Employee(string id, string name, string surname, string department_id, string position) {
    this->id = id;
    this-> name = name;
    this->surname = surname;
    this->department_id = department_id;
    this->position = position;
}

string Employee::getID() {
    return this->id;
}

string Employee::getName() {
    return this->name;
}

string Employee::getSurname() {
    return this->surname;
}

string Employee::getDepartmentID() {
    return this->department_id;
}

string Employee::getPosition() {
    return this->position;
}

string Employee::setID(string new_id) {
    return this->id = new_id;
}

string Employee::setName(string new_name) {
    return this->name = new_name;
}

string Employee::setSurname(string new_surname) {
    return this->surname = new_surname;
}

string Employee::setDepartmentID(string new_department_id) {
    return this->department_id = new_department_id;
}

string Employee::setPosition(string new_position) {
    return this->position = new_position;
}
