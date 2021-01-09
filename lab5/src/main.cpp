#include <iostream>
#include <fstream>
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

    // operator strumienia
    cout << dm1;

    // dodawanie
    DoubleMatrix added = dm1 + dm3;
    cout << "dm1 + dm3"<< endl;
    added.print();
    cout << endl;

    // odejmowanie
    DoubleMatrix subed = dm1 - dm3;
    cout << "dm1 - dm3"<< endl;
    subed.print();
    cout << endl;

    // mnozenie
    // pokazanie dzialania erroru
    DoubleMatrix muledNOT = dm1 * dm3;
    // poprawne
    DoubleMatrix muled = dm1 * dm4;
    cout << "dm1 * dm4"<< endl;
    muled.print();
    cout << endl;

    // zapis do pliku strumieniem
    ofstream file("temp.txt");
    file << muled;
    file.close();

    // wczytanie
    DoubleMatrix temp = DoubleMatrix("temp.txt");
    temp.print();

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