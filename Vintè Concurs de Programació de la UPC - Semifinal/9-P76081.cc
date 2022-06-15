#include <iostream>
#include <string>
using namespace std;

int main() {
    int n;
    string x, y;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> x >> y;
        if (x.size() < y.size()) cout << "NO BRAINS" << endl;
        else if (x.size() > y.size()) cout << "MMM BRAINS" << endl;
        else if (x < y) cout << "NO BRAINS" << endl;
        else cout << "MMM BRAINS" << endl;
    }
}