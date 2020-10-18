#include <iostream>
#include <algorithm>
#include <string>
#include <cctype>

using namespace std;

int main(int argc, char const *argv[]) {

    if (argc == 1) {
        cout << "Usage: zad2 [word to check]" << endl;
        cout << "Checks if the word/sentence is a palindrome" << endl << endl;
        return 0;
    }

    // wprowadzenie wpisanej sentencji do stringa
    string input;
    for (int i = 1; i < argc ; i++) {
        input.append(argv[i]);
        input.append(" ");
    }
    input.pop_back();

    // operacja toLowerCase na całym ciagu tekstowym
    transform(input.begin(), input.end(), input.begin(), [](char c) { return tolower(c); });

    // porownanie pierwszej polowy z druga
    if (equal(input.begin(), input.begin() + input.size()/2, input.rbegin())) {
        cout << "This is a palindrome" << endl;
    } else {
        cout << "It's not a palindrome" << endl;
    }

    
    return 0;

}
