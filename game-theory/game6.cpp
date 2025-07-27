// https://www.hackerrank.com/contests/5-days-of-game-theory/challenges/nimble

// Coins at index 0 are to be ignored
// This is the similar version of nim game as previous, only twisted in form.

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        vector<int> s(n);
        for(auto &x:s) cin>>x;
        int nim = 0;
        for(int i = 1; i < n; i++)
        {
            if(s[i] & 1) nim ^= i;
        }
        if(nim) cout<<"First\n";
        else cout<<"Second\n";
    }
    return 0;
}