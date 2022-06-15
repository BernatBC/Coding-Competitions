#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

double average(const vector<long long>& v) {
    double s = 0;
    for (int i = 0; i < v.size(); ++i) s += (double)v[i]/(v.size() - 1);
    return s;
}

int median(const vector<long long>& v, int n) {
    if (v.size()%2 == 0) {
        if (n < v.size()/2) return v[v.size()/2];
        else return v[v.size()/2 - 1];
    }
    else {
        if (n == (v.size() - 1)/2) return (v[(v.size() - 1)/2 - 1] + v[(v.size() - 1)/2 + 1])/2;
        else return v[(v.size() - 1)/2];
    }
}

int main() {
    cout.setf(ios::fixed);
    cout.precision(2);
    int n;
    while (cin >> n) {
        vector<long long> v(n);
        int x;
        for (int i = 0; i < n; ++i) cin >> v[i];
        sort(v.begin(), v.end());
        double dif = 0;
        double avg = average(v);
        for (int i = 0; i < n; ++i) {
            double avg2 = avg - (double)v[i]/(v.size() - 1);
            int med = median(v, i);
            double dif2 = avg2 - med;
            if (dif2 < 0) dif2 *= -1;
            if (dif2 > dif) {
                dif = dif2;
            }
        }
        cout << dif << endl;
    }
}
