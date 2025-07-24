// जय श्री राम  JAI SHREE RAM

// https://www.hackerrank.com/contests/5-days-of-game-theory/challenges/a-game-of-stones

// Bounded Normal Nim Game

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        if(n % 7 == 0 or n % 7 == 1) cout<<"Second\n";
        else cout<<"First\n";
    }
    return 0;
}