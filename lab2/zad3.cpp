#include <iostream>
#include <cstring>

using namespace std;

void mySwap(int&, int*);

int main(int argc, char const *argv[]) {
    
    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        cout << "Usage: zad3" << endl;
        cout << "Swaps int numbers if the second one is smaller" << endl;
        cout << "(using reference and pointer)" << endl << endl;
        return 0;
    }

    int x, y;

    cout << "Enter your numbers [x y]: ";
    cin >> x >> y;

    mySwap(x, &y);

    cout << "x: " << x << endl << "y: " << y << endl;

    cout << endl; 

    return 0;
}

void mySwap(int& a, int* b) {

    a = a + *b;
    *b = a - *b;
    a = a - *b;

}
