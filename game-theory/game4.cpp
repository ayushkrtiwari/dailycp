// https://www.hackerrank.com/contests/5-days-of-game-theory/challenges/day-1-a-chessboard-game/problem

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
        int x, y;
        cin>>x>>y;
        x %= 4, y %= 4;
        if((x % 4 == 1 or x % 4 == 2) and (y % 4 == 1 or y % 4 == 2))
            cout<<"Second\n";
        else cout<<"First\n";
        // if(((x - 1)/2 + (y - 1)/2) % 2) cout<<"First\n";
        // else cout<<"Second\n";
    }
    return 0;
}
