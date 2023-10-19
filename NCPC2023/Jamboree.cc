#include <iostream>
#include <climits>
#include <queue>
using namespace std;

void print_q(priority_queue<int> q) {
    while (not q.empty())
    {
        cerr << q.top() << " ";
        q.pop();
    }
    cerr << endl;
}

int main() {
    int n_items;
    int n_scouts;
    cin >> n_items >> n_scouts;
    priority_queue<int> q;
    int item;
    for (int i = 0; i < n_items; ++i) {
        cin >> item;
        q.push(item);
    }
    priority_queue<int> assign;
    int maxmimum = 0;
    while (assign.size() < n_scouts and not q.empty())
    {
        item = q.top(); q.pop();
        maxmimum = max(item, maxmimum);
        assign.push(-item);
    }
    // cerr << "q" << endl;
    // print_q(q);
    // cerr << "asssigned" << endl;
    // print_q(assign);
    while (not q.empty())
    {
        int scout_carry = -assign.top(); assign.pop();
        item = q.top(); q.pop();
        // cerr << item << " " << scout_carry << endl;
        maxmimum = max(item+scout_carry, maxmimum);
    }
    cout << maxmimum << endl;
}