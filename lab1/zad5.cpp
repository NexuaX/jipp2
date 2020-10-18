#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

void printMatix(int (&tab)[2][3]);

int main(int argc, char const *argv[]) {

    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        cout << "Usage: zad5" << endl;
        cout << "Adds two matixes together, prints result" << endl << endl;
        cout << "Possible option --random // generates random matrixes" << endl << endl;
        return 0;
    }

    int matrix1[2][3], matrix2[2][3];

    if (argc == 2 && strcmp(argv[1], "--random") == 0) {
        srand(time(NULL));
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 3; j++) {
                matrix1[i][j] = rand() % 10;
                matrix2[i][j] = rand() % 10;
            }
        }
        cout << "First matrix: " << endl;
        printMatix(matrix1);
        cout << endl;
        cout << "Second matrix: " << endl;
        printMatix(matrix2);
    } else {
        cout << "First matix: " << endl;
        for (int i = 0; i < 2; i++) {
            cout << "Row " << i+1 << ": ";
            for (int j = 0; j < 3; j++) {
                cin >> matrix1[i][j];
            }
        }
        cout << endl;
        cout << "Second matix: " << endl;
        for (int i = 0; i < 2; i++) {
            cout << "Row " << i+1 << ": ";
            for (int j = 0; j < 3; j++) {
                cin >> matrix1[i][j];
            }
        }
    }

    cout << endl;
    cout << "Result:" << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            cout << matrix1[i][j] + matrix2[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;

    return 0;
}

void printMatix(int (&tab)[2][3]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            cout << tab[i][j] << " ";
        }
        cout << endl;
    }
}
