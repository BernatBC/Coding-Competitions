#include <iostream>
#include <string>
using namespace std;

int letter_to_num(char c) {
    if (c == 'I') return 1;
    if (c == 'V') return 5;
    if (c == 'X') return 10;
    if (c == 'L') return 50;
    if (c == 'C') return 100;
    if (c == 'D') return 500;
    if (c == 'M') return 1000;
    return 0;
}

int roman_to_num(string a) {
    int result = 0;
    int max = 0;
    for (int i = a.size() - 1; i >= 0; i--) {
        int current = letter_to_num(a[i]);
        if (max > current) {
            result -= current;
        }
        else {
            result += current;
            max = current;
        }
    }
    return result;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string x;
        cin >> x;
        cout << roman_to_num(x) << endl;
    }
}