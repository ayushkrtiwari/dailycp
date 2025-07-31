// https://www.hackerrank.com/contests/5-days-of-game-theory/challenges/a-chessboard-game

// take grundy values of all coins and nim sum them, first wins if its non-zero else second.
// Just the precomputation part has tweak that you need to traverse board 
// as i + j == constant for calculating grundy values of each cell.
// This is to assure that you get the precalculated grundy when you access a cell.

#include <bits/stdc++.h>
using namespace std;
static constexpr int M = 15;

vector<vector<int>> grundy(M,vector<int>(M));

int findmex(set<int> &s)
{
    int cnt = 0;
    for(auto &x : s)
        if(cnt != x) return cnt;
        else cnt++;
    return cnt;
}

void precompute()
{
    function<bool(int, int)> valid = [&](int x, int y)
    {
        if(x >= 0 and x < 15 and y >= 0 and y < 15) return true;
        return false;
    };
    int mxsumij(28); // 2 * n - 2
    // int counter = 0;
    for(int counter = 0; counter <= mxsumij; counter++)
    {
        for(int i = min(14, counter), j = min(14, counter - i); valid(i, j); i--)
        {
            j = min(14, counter - i);
            if(i < 2 and j < 2) 
            {
                grundy[i][j] = 0;
                continue;
            }
            // we need mex of all grundy values of all next states of this cell
            set<int> mex;
            int dx[4] = {-2, -2, 1, -1};
            int dy[4] = {1, -1, -2, -2};
            for(int k = 0; k < 4; k++)
                if(valid(i + dx[k], j + dy[k])) 
                    mex.insert(grundy[i + dx[k]][j + dy[k]]);
            grundy[i][j] = findmex(mex);
            mex.clear();
        }
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    precompute();
    int t;
    cin>>t;
    while(t--)
    {
        int k;
        cin>>k;
        vector<pair<int,int>> cord(k);
        for(auto &x : cord) 
        {
            cin>>x.first>>x.second;
            x.first--, x.second--;
        }
        int xrr(0);
        for(auto &x : cord) xrr ^= grundy[x.first][x.second];
        if(xrr) cout<<"First\n";
        else cout<<"Second\n";
    }
    // for(auto &x : grundy)
    // {
    //     for(auto &y : x)
    //     {
    //         cout<<y<<" ";
    //     }
    //     cout<<"\n";
    // }
    return 0;
}
