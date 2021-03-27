#include <iostream>
#include <vector>
using namespace std;

void Reverse(vector<int>& v, int i, int j) {
  while (i < j) {
    int aux = v[i];
    v[i] = v[j];
    v[j] = aux;
    ++i;
    --j;
  }
}

int Cost(vector<int>& v) {
  int cost = 0;
  for (int i = 1; i < v.size(); ++i) {
    int min = v[i - 1];
    int pos = i;
    for (int j = i + 1; j <= v.size(); ++j) {
      if (v[j - 1] < min) {
        min = v[j - 1];
        pos = j;
      }
    }
    Reverse(v, i - 1, pos - 1);
    cost += pos - i + 1;
  }
  return cost;
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
      int size;
      cin >> size;
      vector<int> vec(size);
      for (int j = 0; j < size; ++j) {
        cin >> vec[j];
      }
      int cost = Cost(vec);
      cout << "Case #" << i << ": " << cost << endl;
    }
}
