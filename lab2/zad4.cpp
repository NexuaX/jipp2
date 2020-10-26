#include <iostream>
#include <cstring>

using namespace std;

int myCalc(int&, int&, int&);

int main(int argc, char const *argv[]) {
    
    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        cout << "Usage: zad4" << endl;
        cout << "Calculates sum and product of two ints" << endl;
        cout << "(using references and pointers)" << endl << endl;
        return 0;
    }

    int x, y;

    cout << "Enter your numbers [x y]: ";
    cin >> x >> y;

    int sum = 0;

    int product = myCalc(x, y, sum);

    cout << "product: " << product << endl << "sum: " << sum << endl;

    cout << endl; 

    return 0;
}

int myCalc(int& x, int& y, int& sum) {

    sum = x + y;
    return x * y;

}
