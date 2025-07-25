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

int dp[16+1][16+1];  // 1..15, 0 = uncomputed, 1 = First-win, 2 = Second-win

int solve(int x, int y) {
   // if out of bounds, current player has no move => they lose => the *other* player (First) wins
    if (x < 1 || y < 1 || x > 15 || y > 15)
       return 1;                  // encode First-win as 1

    if (dp[x][y] != 0)
       return dp[x][y] == 1;     // return true if First-win

    static const int dx[4] = {  1, -1, -2, -2 };
    static const int dy[4] = { -2, -2,  1, -1 };

   // state==true means "so far every move leads to a First-win"
    bool all_moves_win = true;
    for (int k = 0; k < 4; k++) {
        int nx = x + dx[k], ny = y + dy[k];
       // if any move goes to a *losing* state (solve(...) == 0), then current is winning
        if (solve(nx, ny) == 0) {
            all_moves_win = false;
            break;
        }
    }
   // if every move was winning for the next player => current loses => Second wins => encode 2
   // otherwise current wins => encode 1
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