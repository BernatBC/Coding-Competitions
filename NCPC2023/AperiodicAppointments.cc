#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

using ll = long long;

int main(){
    ll N, K;
    cin >> N >> K;

    vector<ll> pattern(N, 0);

    ll i = 0, result = 0;
    for (; pattern[N-1] < K; i++){
        //cerr << i << "::" << innerPattern << " " << pattern << " " << outerPattern << endl;
        if (i >= N) {
            cerr << "\nBreak up early" << endl;
            cout << result << endl;
            return 0;
        }
        bool flag = true;
        for (ll j = 0; j < N-1; j++){
            if (pattern[j] >= K){
                pattern[j] = 0;
                pattern[j+1]++; result++;
                cerr << "1";
                flag = false;
                break;
            }
        }
        if (flag) {
            pattern[0]++;
            cerr << "0";
        }
    }

    result--;
    //cerr << "\nOnly ones are coming after: " << result << " " << N << " " << i << endl;
    cout << result + N - (i-1) << endl;

    return 0;
}