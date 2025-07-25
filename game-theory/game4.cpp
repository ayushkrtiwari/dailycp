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

// ________________________________________________________________________________________________________

// GPT : Brute Force

#include <bits/stdc++.h>
using namespace std;

int dp[16+1][16+1]; 

int solve(int x, int y) {
    if (x < 1 || y < 1 || x > 15 || y > 15)
       return 1;                

    if (dp[x][y] != 0)
       return dp[x][y] == 1;   

    static const int dx[4] = {  1, -1, -2, -2 };
    static const int dy[4] = { -2, -2,  1, -1 };

    bool all_moves_win = true;
    for (int k = 0; k < 4; k++) {
        int nx = x + dx[k], ny = y + dy[k];
        if (solve(nx, ny) == 0) {
            all_moves_win = false;
            break;
        }
    }
    dp[x][y] = all_moves_win ? 2 : 1;
    return dp[x][y] == 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

   // clear table: 0 = uncomputed
    memset(dp, 0, sizeof(dp));

    int T;
    cin >> T;
    while (T--) {
        int x, y;
        cin >> x >> y;
        bool firstWins = solve(x, y);
        cout << (firstWins ? "First\n" : "Second\n");
    }
    return 0;
}