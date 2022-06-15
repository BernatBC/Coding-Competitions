#include <iostream>
#include <set>
#include <string>
using namespace std;

int count(string k, const set<string>& s) {
    int c = 0;
    auto it = s.begin();
    while (it != s.end()) {
        bool b = true;
        string s2 = *it;
        if (k.size() <= s2.size()) {
            for (int i = 0; i < s.size(); ++i) {
                if (k[i] != s2[i + (s2.size() - k.size())]) b = false;
            }
            if (b) ++c;
        }
        ++it;
    }
    return c;
}

void calculate(char a, set<string>& s) {
    if (a == 'R') {
        s = set<string>();
        cout << "---" << endl;
        return;
    }
    string k;
    cin >> k;
    if (a == 'I') s.insert(k);
    else if (a == 'E') s.erase(k);
    else cout << count(k, s) << endl;
    return;
}

int main() {
    char a;
    set<string> s;
    while (cin >> a) {
        calculate(a, s);
    }
}