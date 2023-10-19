#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

float prob(const vector<int>& d1, const vector<int>& d2) {
    int win = 0;
    int count = 0;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (d1[i] > d2[j]) win++;
            if (d1[i] != d2[j]) count++;
        }
    }
    if (count == 0) return 0;
    return float(win)/float(count);
}

float probability(const vector<int>& d1, const vector<int>& d2, const vector<int>& d3) {
    return min(prob(d1, d2), prob(d1, d3));
}

int main() {
    vector<int> d1(6);
    vector<int> d2(6);
    vector<int> d3(6);
    sort(d1.begin(), d1.end());
    sort(d2.begin(), d2.end());
    sort(d3.begin(), d3.end());
    for (int i = 0; i < 6; i++) cin >> d1[i];
    for (int i = 0; i < 6; i++) cin >> d2[i];
    for (int i = 0; i < 6; i++) cin >> d3[i];
    if (probability(d1, d2, d3) >= 0.5) cout << "1" << endl;
    else if (probability(d2, d1, d3) >= 0.5) cout << "2" << endl;
    else if (probability(d3, d2, d1) >= 0.5) cout << "3" << endl;
    else cout << "No dice" << endl;
}