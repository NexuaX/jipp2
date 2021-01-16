/* Command class implementation
** Author: Albert Mouhoubi
*/
#include <projekt/command.hpp>

Command::Command(string name) {
    this->name = name;
    this->func = nullptr;
}

Command::Command(string name, int (*func)()) {
    this->name = name;
    this->func = func;
}

bool Command::operator==(const string & comapre_name) {
    return !(this->name.compare(comapre_name));
}

string Command::getName() {
    return this->name;
}
