// Q. Generate a code for a given integer x which generates all array
//  of elements in range [1, x] and the sum of all elements should be x

#include <bits/stdc++.h>
using namespace std;

// rem = how much sum remains to reach x
// cur = the current partial composition
void dfs(int rem, vector<int>& cur) {
    if (rem == 0) {
        // we've hit the target sum, print this composition
        for (int i = 0; i < (int)cur.size(); i++) {
            cout << cur[i] << (i+1 == (int)cur.size() ? '\n' : ' ');
        }
        return;
    }
    // try every next part from 1 up to rem
    for (int v = 1; v <= rem; v++) {
        cur.push_back(v);
        dfs(rem - v, cur);
        cur.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x;
    cin >> x;

    vector<int> cur;
    dfs(x, cur);

    return 0;
}