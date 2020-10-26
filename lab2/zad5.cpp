#include <iostream>
#include <cstring>

using namespace std;

void mySwap(void*, void*, size_t);

int main(int argc, char const *argv[]) {
    
    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        cout << "Usage: zad5" << endl;
        cout << "Swap function for any data type" << endl;
        cout << "(using references and pointers)" << endl << endl;
        return 0;
    }

    cout << endl;

    cout << "Double: " << "[x y] = [5.2 3.13]" << endl;
    double x = 5.2, y = 3.13;

    mySwap(&x, &y, sizeof(double));

    cout << "x: " << x << endl << "y: " << y << endl;

    cout << "Struct: " << endl << "[x: a, b] = [x: 3, 6.2]" << endl;
    cout << "[y: a, b] = [y: 7, 2.66]" << endl << endl;

    struct z {
        int a;
        double b;
    } m, n;

    m.a = 3, m.b = 6.2;
    n.a = 7, n.b = 2.66;

    mySwap(&m, &n, sizeof(z));

    cout << "x: " << m.a << " " << m.b << endl;
    cout << "y: " << n.a << " " << n.b << endl;

    cout << endl;

    return 0;
}

void mySwap(void* a, void* b, size_t size) {

    void* temp = malloc(size);
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);

    free(temp);

}
