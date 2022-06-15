#include <iostream>
#include <vector>
using namespace std;

int suma (const vector<int>& v) {
    int s = 0;
    for (int i = 0; i < v.size(); ++i) s += v[i];
    return s;
}

void dfs(const vector<vector<int>>& v, vector<int>& nodes, int node, int value) {
    nodes[node] = value;
    if (value == 1) value = 2;
    else value = 1;
    for (int i = 0; i < v[node].size(); ++i) {
        if (nodes[v[node][i]] == 0) dfs(v, nodes, v[node][i], value);
    }
}

int main() {
    int n;
    while (cin >> n) {
        vector<vector<int>> v(n);
        vector<int> nodes(n, 0);
        for (int i = 0; i < n - 1; ++i) {
            int x, y;
            cin >> x >> y;
            v[x].push_back(y);
            v[y].push_back(x);
        }
        dfs(v, nodes, 0, 1);
        int s1 = suma(nodes);
        nodes = vector<int>(n, 0);
        dfs(v, nodes, 0, 2);
        int s2 = suma(nodes);
        cout << s1 << " " << s2 << endl;
        /*if (s1 > s2) cout << s2 << endl;
        else cout << s1 << endl;*/
    }
}