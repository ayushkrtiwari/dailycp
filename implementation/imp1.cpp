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

// ____________________________________________________________________________________________

// A/GPT : 'Knuth Algorithm H'
// this implementation will not give permutation of the possible arrays

#include <bits/stdc++.h>
using namespace std;

// Print the current composition of length k in array a[0..k-1].
void print_comp(const vector<int>& a, int k) {
    for (int i = 0; i < k; i++) {
        cout << a[i] << (i+1<k ? ' ' : '\n');
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x;
    cin >> x;

    // a[0..k-1] holds the current composition, sum = x
    vector<int> a(x);
    int k = 1;
    a[0] = x;

    // Iterate over all compositions
    while (true) {
        print_comp(a, k);

        // Step H2: if last part > 1, decrease it and append a 1
        if (a[k-1] > 1) {
            a[k-1]--;
            a[k++] = 1;
            continue;
        }

        // Otherwise a[k-1] == 1. Scan backwards for the first part > 1
        int j = k-2;  // look at a[j]
        while (j >= 0 && a[j] == 1) j--;

        // If none found, we’re done
        if (j < 0) break;

        // Found a[j] > 1, so decrement it and redistribute the sum of the 1's+1
        int rem = (k - j);   // total to re‑compose
        a[j]--;
        k = j + 1;

        // Fill as many copies of a[j] as we can
        while (rem > a[j]) {
            a[k++] = a[j];
            rem -= a[j];
        }
        // Remainder
        a[k++] = rem;
    }

    return 0;
}
