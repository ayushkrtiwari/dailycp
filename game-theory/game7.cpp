// जय श्री राम  JAI SHREE RAM

// https://www.hackerrank.com/contests/5-days-of-game-theory/challenges/day-2-poker-nim

// Unbounded Normal Nim Game

// Addition of chips has no effect since winning strategy is to copy the other player's move whenever they perform addition.
// Hence addition does not affect our winning strategy and thus we can play it as normal nim game.

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
        int n,k;
        cin>>n>>k;
        vector<int> s(n);
        for(auto &x:s) cin>>x;
        int nim = 0;
        for(auto &x:s) nim ^= x;
        if(nim) cout<<"First\n";
        else cout<<"Second\n";
    }
    return 0;
}