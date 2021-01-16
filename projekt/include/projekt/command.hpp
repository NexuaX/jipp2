/* Command class header
** Author: Albert Mouhoubi
*/
#ifndef COMMAND_CLASS
#define COMMAND_CLASS

#include <string>

using namespace std;

class Command {
private:
    string name;

public:
    int (*func)();
    Command(string name);
    Command(string name, int (*func)());
    bool operator==(const string & compare_name);

    string getName();
};

#endif