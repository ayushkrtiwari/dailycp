#include <bits/stdc++.h>
using namespace std;

/*
 Brute-force solution (BFS on bitmask states).
 - state: bitmask of positions that remain (1 = present)
 - transition: choose any non-empty submask of state such that
   the subsequence formed by those indices is non-decreasing (0...0 1...1).
   Next state = state ^ submask (we delete those indices).
 - BFS from initial_mask = (1<<n)-1 to any mask whose corresponding string is balanced.
 Warning: exponential. Use for small n (<=20) only.
*/

bool is_sorted_subsequence(int submask, const string &s) {
    int n = s.size();
    char last = 0; // 0 = not seen yet, otherwise '0' or '1'
    bool seen = false;
    for (int i = 0; i < n; ++i) {
        if ((submask >> i) & 1) {
            if (!seen) {
                last = s[i];
                seen = true;
            } else {
                if (s[i] < last) return false; // violates non-decreasing
                last = s[i];
            }
        }
    }
    return seen; // must be non-empty
}

// check if the string formed by positions with bit=1 in mask is balanced
bool mask_is_balanced(int mask, const string &s) {
    int bal = 0; // +1 for '0', -1 for '1'
    for (int i = 0; i < (int)s.size(); ++i) {
        if ((mask >> i) & 1) {
            if (s[i] == '0') ++bal;
            else --bal;
            if (bal < 0) return false; // at some prefix ones > zeros -> not balanced
        }
    }
    return bal == 0; // must end with equal zeros and ones
}

int brute_min_ops(const string &s) {
    int n = (int)s.size();
    if (n == 0) return 0;
    if (n > 20) {
        // guard: brute won't run for large n
        return -1; // caller should handle
    }
    int full = (1 << n) - 1;
    // quick check: already balanced?
    if (mask_is_balanced(full, s)) return 0;

    vector<int> dist(1 << n, -1);
    queue<int> q;
    dist[full] = 0;
    q.push(full);

    while (!q.empty()) {
        int mask = q.front(); q.pop();

        // enumerate non-empty submasks of mask
        for (int sub = mask; sub; sub = (sub - 1) & mask) {
            if (!is_sorted_subsequence(sub, s)) continue;
            int nxt = mask ^ sub;
            if (dist[nxt] == -1) {
                dist[nxt] = dist[mask] + 1;
                // if resulting string is balanced, we've found the minimal ops
                if (mask_is_balanced(nxt, s)) return dist[nxt];
                q.push(nxt);
            }
        }
    }
    return -1; // unreachable in theory
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T=1;
    // if (!(cin >> T)) return 0;
    while (T--) {
        int N; string S;
        cin >> N >> S;
        if ((int)S.size() != N) {
            cerr << "Warning: input length mismatch\n";
        }

        int ans = brute_min_ops(S);
        if (ans >= 0) {
            cout << ans << '\n';
        } else {
            cout << "BRUTE_TOO_LARGE\n";
        }
    }
    return 0;
}
