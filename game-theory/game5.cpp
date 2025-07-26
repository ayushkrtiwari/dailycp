// https://www.hackerrank.com/contests/5-days-of-game-theory/challenges/misere-nim/problem

// Misère Nim is exactly like the standard Nim game, except for one critical difference. 
// If the size of every pile is 1, then we need to treat it as a special case where we count the number of piles. 
// If the count is even, then the first player will win; if the count is odd, then the first player will lose.

// If the size of every pile is not 1, then you can use XOR sum to determine who will win the game.

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
        bool areallone = true;
        for(auto &x:s) if(x != 1) areallone = false;
        if(areallone)
        {
            if(n % 2) cout<<"Second\n";
            else cout<<"First\n";
            continue;
        }
        int nim = 0;
        for(auto &x : s) nim ^= x;
        if(nim) cout<<"First\n";
        else cout<<"Second\n";
    }
    return 0;
}
