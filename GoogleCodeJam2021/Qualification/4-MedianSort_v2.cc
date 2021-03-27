#include <iostream>
#include <vector>
using namespace std;

int main() {
  int cases, full_size, questions;
  cin >> cases >> full_size >> questions;
  while (cases > 0) {
    vector<int> v;
    cout << "1 2 3" << endl;
    int size = 3;
    int p;
    cin >> p;
    if (p == 2) {
      v.push_back(1);
      v.push_back(2);
      v.push_back(3);
    }
    else if (p == 3) {
      v.push_back(1);
      v.push_back(3);
      v.push_back(2);
    }
    else {
      v.push_back(2);
      v.push_back(1);
      v.push_back(3);
    }
    for (int i = 4; i <= full_size; ++i) {
      int j = 0;
      int k = size - 1;
      bool exit = false;
      while (j < k and not exit) {
        int middle = j + ((k - j)/2);
        cout << v[middle] << " " << v[middle + 1] << " " << i << endl;
        cin >> p;
        if (p == v[middle]) k = middle;
        else if (p == v[middle + 1]) j = middle + 1;
        else {
          v.insert(v.begin() + middle + 1, i);
          ++size;
          exit = true;;
        }
      }
      if (size != i) {
        if (j == 0) v.insert(v.begin(), i);
        else v.push_back(i);
        ++size;
      }
    }
    for (int i = 0; i < v.size(); ++i) {
      cout << v[i] << " ";
    }
    cout << endl;
    cin >> p;
    --cases;
  }
}
