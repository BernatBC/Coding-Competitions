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

void Show(const vector<int>& v) {
  for (int i = 0; i < v.size(); ++i) {
    cout << " " << v[i];
  }
  cout << endl;
}

void Generator(int size, int cost) {
  vector<int> v(size);
  for (int i = 0; i < size; ++i) {
    v[i] = i + 1;
  }
  int i = size - 2;
  int j = size - 1;
  cost = cost - size + 1;
  while (cost > 0) {
    int max_cost = j - i;
    if (cost <= max_cost) {
      Reverse(v, i, i + cost);
      cost = 0;
    }
    else {
      Reverse(v, i, size - 1);
      cost = cost - (size - 1 - i);
    }
    --i;
  }
  Show(v);
};

int Possibilities(int num) {
  int total = 0;
  for (int i = 2; i <= num; ++i) {
    total += i;
  }
  return total;
}

int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    int size, cost;
    cin >> size >> cost;
    cout << "Case #" << i << ":";
    if (cost >= size - 1 and cost <= Possibilities(size)) {
      Generator(size, cost);
    }
    else cout << " IMPOSSIBLE" << endl;
  }
}
