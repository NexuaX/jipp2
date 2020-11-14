#include <iostream>
#include <cstring>
#include <random>
#include <iomanip>
#include "matrix.hpp"

using namespace std;

void populateMatrix(DoubleMatrix & dm);

// random doubles
uniform_real_distribution<double> unif(0, 10);
default_random_engine re;

int main(int argc, char const * argv[]) {

    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        cout << "Usage: zad" << endl;
        cout << "Rich C++ Class example" << endl << endl;
        return 0;
    }
    
    // konstruktory liczbowe
    DoubleMatrix dm1(4, 5);
    DoubleMatrix dm2(5);
    DoubleMatrix dm3(4, 5);
    DoubleMatrix dm4(5, 7);

    // losowanie wartosci
    populateMatrix(dm1);
    populateMatrix(dm2);
    populateMatrix(dm3);
    populateMatrix(dm4);

    // stala precyzja
    cout << setprecision(6) << fixed;

    dm1.print();
    cout << endl;

    dm2.print();
    cout << endl;

    dm3.print();
    cout << endl;

    dm4.print();
    cout << endl;

    // dodawanie
    DoubleMatrix added = dm1.addMatrices(dm3);
    cout << "dm1 + dm3"<< endl;
    added.print();
    cout << endl;

    // odejmowanie
    DoubleMatrix subed = dm1.subtractMatrices(dm3);
    cout << "dm1 - dm3"<< endl;
    subed.print();
    cout << endl;

    // mnozenie
    // pokazanie dzialania erroru
    DoubleMatrix muledNOT = dm1.multiplyMatrices(dm3);
    // poprawne
    DoubleMatrix muled = dm1.multiplyMatrices(dm4);
    cout << "dm1 * dm4"<< endl;
    muled.print();
    cout << endl;

    // zapis do pliku
    muled.store("muled.txt", ".");
    // odczyt pliku
    DoubleMatrix fromFile("muled.txt");
    cout << "fromFile muled.txt" << endl;
    fromFile.print();

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