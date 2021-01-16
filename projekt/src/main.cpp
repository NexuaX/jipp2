#include <iostream>
#include <cstring>
#include <projekt/hrms.hpp>

using namespace std;

int main(int argc, char const * argv[]) {

    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        cout << "Usage: " << argv[0] << endl;
        cout << "Extended HRMS System project" << endl << endl;
        return 0;
    }

    cout << "Welcome to HRMS System!" << endl;
    cout << "Author: Alber Mouhoubi" << endl << endl;

    HRMS::getInstance().init();

    while(HRMS::getInstance().prompt());

    return 0;

}
