// https://www.hackerrank.com/contests/5-days-of-game-theory/challenges/tower-breakers

// Unbounded Normal Nim Game
// Trick: Follow Resources and editorials for understanding.
// Just it is that copy the opponent's move, thus nim sum or specific cases as always

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
        int n, m;
        cin>>n>>m;
        if(m == 1 or n % 2 == 0)
            cout<<"2\n";
        else
            cout<<"1\n";
    }
    return 0;
}