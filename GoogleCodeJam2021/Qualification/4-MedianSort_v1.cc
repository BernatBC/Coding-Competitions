#include <iostream>
#include <vector>
using namespace std;

vector<int> Median_sort(const vector<int>& v);

void Show(const vector<int>& v) {
  for (int i = 0; i < v.size(); ++i) {
    if (i != 0) cout << " ";
    cout <<  v[i];
  }
  cout << endl;
}

//Generates a vector filled: 1, 2, 3, ..., size
vector<int> Generator(int size) {
  vector<int> v(size);
  for (int i = 0; i < size; ++i) {
    v[i] = i + 1;
  }
  return v;
}

//Returns the position of a in v
int pos(const vector<int>& v, int a) {
  for (int i = 0; i < v.size(); ++i) {
    if (v[i] == a) return i;
  }
  return -1;
}

//Inserts and moves the vector
vector<int> Insert(vector<int>& v, int element, int pos) {
  vector<int> s(v.size() + 1);
  for (int i = 0; i < s.size(); ++i) {
    if (i < pos) {
      s[i] = v[i];
    }
    else if (i > pos) {
      s[i] = v[i - 1];
    }
    else {
      s[i] = element;
    }
  }
  return s;
}

void Split_left(const vector<int>& v, vector<int>& v1, vector<int>& v2, int j) {
  for (int i = 0; i < v.size(); ++i) {
    if (i == 1 and j == 1) {
      v1.push_back(v[i]);
    }
    else if (i < j) {
      v1.push_back(v[i]);
    }
    else {
      v2.push_back(v[i]);
    }
  }
}

void Split_right(const vector<int>& v, vector<int>& v1, vector<int>& v2, int j) {
  for (int i = 0; i < v.size(); ++i) {
    if (i < j - 1) {
      v1.push_back(v[i]);
    }
    else {
      v2.push_back(v[i]);
    }
  }
}

void Split_middle(const vector<int>& v, vector<int>& v1, vector<int>& v2, vector<int>& v3, int i, int j) {
  for (int k = 0; k < v.size(); ++k) {
    if (k < i) {
      v1.push_back(v[k]);
    }
    else if (k > j) {
      v3.push_back(v[k]);
    }
    else {
      v2.push_back(v[k]);
    }
  }
}

vector<int> Merge(const vector<int>& v1, const vector<int>& v2) {
  vector<int> v = v1;
  for (int i = 0; i < v2.size(); ++i) {
    v.push_back(v2[i]);
  }
  return v;
}

vector<int> Reversing(vector<int>& v) {
  vector<int> s(v.size());
  for (int i = 0; i < s.size(); ++i) {
    s[i] = v[s.size() - i - 1];
  }
  return s;
}

//Inserts the new element in the vector
void Insert_vector(vector<int>& full, const vector<int>& sub) {
  if (full.empty()) {
    full = sub;
  }
  else {
    int a = sub[0];
    int pos_a = pos(full, sub[0]);
    int b = sub[1];
    int pos_b = pos(full, sub[1]);
    int c = sub[2];
    int pos_c = pos(full, sub[2]);

    if (pos_b == -1) {
      //Pos a < B < c
      if (pos_a < pos_c) {
        if (pos_a == pos_c - 1) {
          full = Insert(full, b, pos_c);
        }
        else {
          vector<int> sub1;
          vector<int> sub2;
          vector<int> sub3;
          Split_middle(full, sub1, sub2, sub3, pos_a, pos_c);
          sub2 = Insert(sub2, b, 0);
          sub2 = Median_sort(sub2);
          full = Merge(sub1, sub2);
          full = Merge(full, sub3);
        }
      }
      //Pos c < B < a
      else {
        if (pos_a == pos_c + 1) {
          full = Insert(full, b, pos_a);
        }
        else {
          vector<int> sub1;
          vector<int> sub2;
          vector<int> sub3;
          Split_middle(full, sub1, sub2, sub3, pos_c, pos_a);
          sub2 = Insert(sub2, b, 0);
          sub2 = Median_sort(sub2);
          full = Merge(sub1, sub2);
          full = Merge(full, sub3);
        }
      }
    }

    else {
      //Pos C < b < a
      if (pos_b < pos_a) {
        if (pos_b == 0) {
          full = Insert(full, c, 0);
        }
        else {
          vector<int> sub1;
          vector<int> sub2;
          Split_left(full, sub1, sub2, pos_b);
          sub1 = Insert(sub1, c, 0);
          sub1 = Median_sort(sub1);
          full = Merge(sub1, sub2);
        }
      }
      else {
        //Pos a < b < C
        if (pos_a == full.size() - 1) {
          full = Insert(full, c, full.size());
        }
        else {
          vector<int> sub1;
          vector<int> sub2;
          Split_right(full, sub1, sub2, pos_b);
          sub2 = Insert(sub2, c, 0);
          sub2 = Median_sort(sub2);
          sub2 = Reversing(sub2);
          full = Merge(sub1, sub2);
        }
      }
    }
  }
}

vector<int> Median_sort(const vector<int>& v) {
  if (v.size() == 3) {
    cout << v[0] << " " << v[1] << " " << v[2] << endl;
    vector<int> s(3);
    int median;
    cin >> median;
    if (median == v[0]) {
      s[0] = v[1];
      s[1] = v[0];
      s[2] = v[2];
    }
    else if (median == v[2]) {
      s[0] = v[0];
      s[1] = v[2];
      s[2] = v[1];
    }
    else {
      s = v;
    }
    return s;
  }
  else {
    vector<int> full;
    for (int i = 0; i < v.size() - 2; ++i) {
      vector<int> provisional(3);
      provisional[0] = v[i];
      provisional[1] = v[i + 1];
      provisional[2] = v[i + 2];
      provisional = Median_sort(provisional);
      Insert_vector(full, provisional);
    }
    return full;
  }
}

int main() {
  int n_cases, size, questions;
  cin >> n_cases >> size >> questions;
  for (int i = 1; i <= n_cases; ++i) {
    vector<int> v = Generator(size);
    v = Median_sort(v);
    Show(v);
    int ans;
    cin >> ans;
    if (ans == 0) {
      v = Median_sort(v);
      Show(v);
    }
  }
}
