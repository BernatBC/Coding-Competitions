#include <iostream>
#include <string>
#include <vector>
using namespace std;

int Cost(const vector<char>& vec, int costCJ, int costJC) {
  int cost = 0;
  for (int i = 0; i < vec.size() - 1; ++i) {
    if (vec[i] == 'C' and vec[i + 1] == 'J') cost += costCJ;
    else if (vec[i] == 'J' and vec[i + 1] == 'C') cost += costJC;
  }
  return cost;
}

char find(string seq) {
  int i = 0;
  while (i < seq.size()) {
    if (seq[i] == 'C' or seq[i] == 'J') return seq[i];
    ++i;
  }
  return '-';
}

vector<char> Generator(string seq) {
  char to_fit = find(seq);
  vector<char> vec(seq.size());
  for (int i = 0; i < seq.size(); ++i) {
    if (seq[i] == 'C' or seq[i] == 'J') vec[i] = seq[i];
    else vec[i] = to_fit;
    to_fit = vec[i];
  }
  return vec;
}

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    int costCJ, costJC;
    string seq;
    cin >> costCJ >> costJC;
    cin >> seq;
    vector<char> v = Generator(seq);
    int cost = Cost(v, costCJ, costJC);
    cout << "Case #" << i + 1 << ": " << cost << endl;
  }
}
