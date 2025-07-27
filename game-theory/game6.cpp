// जय श्री राम  JAI SHREE RAM

// https://www.hackerrank.com/contests/5-days-of-game-theory/challenges/nimble

// Nimble Game, Unbounded Normal Nim Game

// Coins at index 0 are to be ignored
// This is the similar version of nim game as previous, only twisted in form.
// If there exists even coins at an index, then those coins are also to be ignored.
// This is due to the fact that if player moves a coin to any lower index, the opponent will copy it as winning move
// Now we only take care of positions where there are odd no of coins
// Now, we take the positions of the odd coin piles as stones count in multiple piles, this way we can apply nim sum.
// Bringing those coins from i to j(j < i) index is similar to bringing stones count from i to j.
// Hence, nim sum of positions of odd coins count index.

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