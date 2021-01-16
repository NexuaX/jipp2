/* User class header
** Author: Albert Mouhoubi
*/
#ifndef USER_CLASS
#define USER_CLASS

#include <string>

using namespace std;

class User {
public:
    string username;
    string password;
    User();
    User(string username, string password);
};

#endif