#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>

using namespace std;

int main(int argc, char const *argv[]) {

    if (argc == 1) {
        cout << "Usage: zad1 [numbers to sort]" << endl;
        cout << "Sorts given integers numbers." << endl << endl;
        return 0;
    }

    // vector dla naszych liczb
    vector<int> tab(argc-1, 0);

    // zapis z tablicy argv do vectora + konwersja
    for (int i = 0; i < argc-1; i++) {
        const char* number = argv[i+1];
        tab[i] = atoi(number);
    }

    // podstawowe sortowanie
    sort(tab.begin(), tab.end());

    // wypisanie posortowanych danych
    cout << "out: ";
    for (const auto &i: tab) {
        cout << i << " ";
    }
    cout << endl;


    return 0;
    
}
