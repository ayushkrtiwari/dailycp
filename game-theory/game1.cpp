// जय श्री राम  JAI SHREE RAM

// https://www.hackerrank.com/contests/5-days-of-game-theory/challenges/day-2-nim-game

// Nim Game, Nim Sum, Sprague-Grundy Theorem, Game-Theory
// Refer resources section for elaboration

// Unbounded Normal Nim Game

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