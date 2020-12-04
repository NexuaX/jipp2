#include <iostream>
#include <cstring>
#include <random>
#include <iomanip>
#include <lab4/matrix.hpp>

using namespace std;

void populateMatrix(DoubleMatrix & dm);

// random doubles
uniform_real_distribution<double> unif(0, 10);
default_random_engine re;

int main(int argc, char const * argv[]) {

    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        cout << "Usage: zad" << endl;
        cout << "Rich C++ Class example + sqlite implementation" << endl << endl;
        return 0;
    }
    
    // konstruktory liczbowe
    DoubleMatrix dm1(4, 5);
    DoubleMatrix dm2(5, 4);

    // losowanie wartosci
    populateMatrix(dm1);
    populateMatrix(dm2);

    // stala precyzja
    cout << setprecision(6) << fixed;

    dm1.print();
    cout << endl;
    dm2.print();
    cout << endl;

    dm1.addMatrices(dm2).print();
    cout << endl;

    dm1.multiplyMatrices(dm2).print();
    cout << endl;

    dm1.storeSQLite("dm1");
    cout << endl;

    DoubleMatrix dm3("dm1", SQLite);

    dm3.print();
    cout << endl;

    return 0;
}

void populateMatrix(DoubleMatrix & dm) {

    for (size_t i = 0; i < dm.rows(); i++) {
        for (size_t j = 0; j < dm.cols(); j++) {
            dm.setElement(i, j, unif(re));
        }
    }

    return;
}