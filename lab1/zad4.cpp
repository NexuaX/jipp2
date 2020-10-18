#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

// deklaracja funkcji, def ponizej main
int findSumOfDivisors(int &);

int main(int argc, char const *argv[]) {
    
    if (argc == 1) {
        cout << "Usage: zad4 [number 1] [number 2]" << endl;
        cout << "Checks if the numbers are associated" << endl << endl;
        return 0;
    }

    // definicja zmiennych
    int number1, number2;

    // konwersja argumentow
    number1 = atoi(argv[1]);
    number2 = atoi(argv[2]);

    int sum1 = 0, sum2 = 0;

    // funckja znajdujaca sumy dzielnikow
    sum1 = findSumOfDivisors(number1);
    sum2 = findSumOfDivisors(number2);

    // wypisanie wyniku
    if (sum1 == number2+1 && sum2 == number1+1) {
        cout << "Numbers are associated" << endl;
    } else {
        cout << "Number are NOT associated" << endl;
    }


    return 0;
}


int findSumOfDivisors(int & number) {

    int sum = 0;

    // algorytm naiwny zoptymalizowany O(sqrt(number))
    for (int i = 2; i < sqrt(number); i++) {
        if (number%i == 0) {
            if (number/i == i) {
                sum += i;
            } else {
                sum += i + number/i;
            }
        }
    }
    
    return sum+1;
}
