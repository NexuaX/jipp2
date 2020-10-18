#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

int main(int argc, char const *argv[]) {
    
    if (argc == 2 && strcmp(argv[1], "--help")) {
        cout << "Usage: zad3 [body mass (kg)] [height (m)]" << endl;
        cout << "Calculates one's BMI" << endl << endl;
        return 0;
    }

    // definicja zmiennych
    double bmass, height;

    // rozgalezienie dla podania i braku argumentow
    if (argc == 1) {
        cout << "Body mass [kg]: ";
        cin >> bmass;

        cout << "Height [m]: ";
        cin >> height;
    } else {
        bmass = atof(argv[1]);
        height = atof(argv[2]);
    }

    // przeliczenie BMI
    double bmi = bmass/(height*height);

    // sprawdzenie przypadku
    if (bmi < 16) {
        cout << "Severe Thinnes";
    } else if (bmi < 17) {
        cout << "Moderate Thinnes";
    } else if (bmi < 18.5) {
        cout << "Mild Thinnes";
    } else if (bmi < 25) {
        cout << "Normal";
    } else if (bmi < 30) {
        cout << "Overweight";
    } else if (bmi < 35) {
        cout << "Obese Class 1";
    } else if (bmi < 40) {
        cout << "Obese Class 2";
    } else if (bmi >= 40) {
        cout << "Obese Class 3";
    }
    cout << endl;

    return 0;
}
