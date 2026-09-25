// Example contestant implementing binary search in C++
// This program reads judge responses from stdin and prints queries to stdout. Always flush.

#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int lo = 1, hi = 100;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        cout << "? " << mid << '\n' << flush;
        string r;
        if (! (cin >> r)) return 0;
        if (r == "<") hi = mid - 1;
        else if (r == ">") lo = mid + 1;
        else if (r == "=") {
            cout << "! " << mid << '\n' << flush;
            string verdict; // read final judge reply if any
            if (cin >> verdict) return 0;
            return 0;
        } else {
            return 0;
        }
    }
    return 0;
}