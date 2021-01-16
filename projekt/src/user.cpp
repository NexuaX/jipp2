/* User class implementation
** Author: Albert Mouhoubi
*/

#include <projekt/user.hpp>
#include <string>

using namespace std;

User::User() {
    this->username = "";
    this->password = "";
}

User::User(string username, string password) {
    this->username = username;
    this->password = password;
}
