#include <iostream>
#include <random>
using namespace std;

mt19937 rng;

int recalculate(int pos) {
    if (pos == 2) return 38;
    if (pos == 7) return 14;
    if (pos == 8) return 31;
    if (pos == 15) return 26;
    if (pos == 21) return 42;
    if (pos == 28) return 84;
    if (pos == 36) return 44;
    if (pos == 51) return 67;
    if (pos == 71) return 91;
    if (pos == 78) return 98;
    if (pos == 87) return 94;

    if (pos == 16) return 6;
    if (pos == 46) return 25;
    if (pos == 49) return 11;
    if (pos == 62) return 19;
    if (pos == 64) return 60;
    if (pos == 74) return 53;
    if (pos == 89) return 68;
    if (pos == 92) return 88;
    if (pos == 95) return 75;
    if (pos == 99) return 80;

    if (pos > 100) return recalculate(200 - pos);

    return pos;
}

int dice() {
    unsigned int r = rng();
    return r%6 + 1;
}

string winner() {
    int posx = 1;
    int posy = 1;
    bool torn = true;
    while (posx != 100 and posy != 100) {
        int d = dice();
        if (torn) {
            posx += d;
            posx = recalculate(posx);
            if (posx == 100) return "RED";
        }
        else {
            posy += d;
            posy = recalculate(posy);
            if (posy == 100) return "BLUE";
        }
        if (d != 6) torn = not torn;
    }
    return "";
}

int main() {
    int seed;
    while (cin >> seed) {
        rng.seed(seed);
        cout << winner() << endl;
    }
}