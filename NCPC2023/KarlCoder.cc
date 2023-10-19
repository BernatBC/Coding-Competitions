#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

using ll = long long;

//vector<ll> buffer = {12, 12, 6 ,7, 8, 9, 10, 0 , 0, 0, 0, 0 , 0, 0};
vector<ll> buffer = {78, 67, 0, 0};

bool go_left(ll index) {
    cout << "buf[" << index << "]" << endl;
    string s;
    cin >> s;
    return s=="0";
}

bool go_left_test(ll index){
    return (index >= buffer.size() ? true : (buffer[index] == 0));
} 

int main() {
    ll l = 0, r = pow(10, 18);
    ll k = 1;
    while (not go_left(k)) k*=2;

    r = k;
    l = k/2;

    ll middle = (r + l) / 2;

    while (l+1 < r){
        //cout <<l << " " << r << " " << middle << endl;
        if (go_left(middle)){
            r = middle;
        }    
        else {
            l = middle;
        }
        middle = (r + l) / 2;
    }
    //cout <<l << " " << r << " " << middle << endl;
    //cout <<l << " " << r << " " << middle << endl;
    //if (go_left(r)) cout << "strlen(buf) = " << r << endl;
    /*else*/ cout << "strlen(buf) = " << r << endl;
    //cout << "strlen(buf) = " << r + 1 << endl;
    

    return 0;
}