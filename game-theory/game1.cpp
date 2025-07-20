// https://www.hackerrank.com/contests/5-days-of-game-theory/challenges/day-2-nim-game

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
        for(auto &x : s) cin>>x;
        int nim = 0;
        for(auto &x : s) nim ^= x;
        if(nim == 0) cout<<"Second\n";
        else cout<<"First\n";
    }
    return 0;
}