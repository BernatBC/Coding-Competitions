#include <iostream>
#include <cmath>
using namespace std;

bool is_prime(int n) {
    if (n == 2) return true;
    unsigned long long i = 3;
    while (i <= n/2) {
        if (n%i == 0) return false;
        i += 2;
    }
    return true;
}

int primes(unsigned long long l, unsigned long long r) {
    int s = 0;
    if (l == 0) ++s;
    bool stop = false;
    unsigned long long i = 2;
    while (not stop) {
        if (is_prime(i)) {
            long long k = pow(i, i);
            if (k < 0 or k > r) stop = true;
            else if (k >= l and k <= r) ++s;
        }
        if (i == 2) ++i;
        else i += 2;
    }
    return s;
}

int main() {
    unsigned long long l, r;
    while (cin >> l >> r) {
        cout << primes(l, r) << endl;
    }
}
