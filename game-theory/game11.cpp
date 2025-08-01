// https://www.hackerrank.com/contests/5-days-of-game-theory/challenges/digits-square-board/problem

#include <bits/stdc++.h>
using namespace std;

bool allprime(vector<vector<int>> &board, int sr, int sc, int tr, int tc)
{
    for(int i = sr; i <= tr; i++)
        for(int j = sc; j <= tc; j++)
            if(board[i][j] == 1 or board[i][j] == 4 or board[i][j] == 6 or board[i][j] == 8 or board[i][j] == 9) return 0;
            // since 1 is non-prime too
    return 1;
}

int findmex(set<int> &mex)
{
    int cnt = 0;
    for(auto &x : mex)
        if(x != cnt) return cnt;
        else cnt++;
    return cnt;
}

int precompute(int grundy[31][31][31][31], vector<vector<int>> &board, int sr, int sc, int tr, int tc)
{
    if(grundy[sr][sc][tr][tc] != -1) return grundy[sr][sc][tr][tc];
    if(allprime(board, sr, sc, tr, tc)) return grundy[sr][sc][tr][tc] = 0;
    if(sr == tr and sc == tc) return grundy[sr][sc][tr][tc] = 0; // this must be composite no but no further moves in single cell
    set<int> mex;
    for(int i = sr + 1; i <= tr; i++) mex.insert(precompute(grundy, board, sr, sc, i - 1, tc) ^ precompute(grundy, board, i, sc, tr, tc));
    for(int j = sc + 1; j <= tc; j++) mex.insert(precompute(grundy, board, sr, sc, tr, j - 1) ^ precompute(grundy, board, sr, j, tr, tc));
    return grundy[sr][sc][tr][tc] = findmex(mex);
}

int main() {
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        vector<vector<int>> board(n + 1, vector<int>(n + 1));
        // for(auto &r : board)
        //     for(auto &cell : r)
        //         cin>>cell;
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                cin>>board[i][j];
        int grundy[31][31][31][31];
        memset(grundy, -1, sizeof(grundy));
        precompute(grundy, board, 1, 1, n, n);
        // for(auto &r1 : grundy)
        //     for(auto &r2 : r1)
        //         for(auto &r3 : r2)
        //             for(auto &r4 : r3)
        //                 cout<<r4<<" ";
        if(grundy[1][1][n][n]) cout<<"First\n";
        else cout<<"Second\n";
    }
    return 0;
}

// ______________________________________________________________________________________________

// Editorial Code

#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<vector>
#include<cmath>

using namespace std;

const int M=60;

int a[M][M],gr[M][M][M][M];
int n,t;

int prime_check(int x, int y, int z,  int m)
{
    for (int i=x;i<=z;i++)
    for (int j=y;j<=m;j++)
    if (a[i][j]==1 || a[i][j]==4 || a[i][j]==6 || a[i][j]==8 || a[i][j]==9) return 0;

    return 1;
}

int grundy(int x, int y, int z,int m)
{
    int v[75];

    if (gr[x][y][z][m]!=-1) return gr[x][y][z][m];
    if (prime_check(x,y,z,m))
    {
        gr[x][y][z][m]=0;
        return 0;
    }

    for (int i=0;i<75;i++)
    v[i]=0;

    for (int i=x+1;i<=z;i++) v[grundy(x,y,i-1,m)^grundy(i,y,z,m)]=1;
    for (int i=y+1;i<=m;i++) v[grundy(x,y,z,i-1)^grundy(x,i,z,m)]=1;


    for (int i=0;i<75;i++)
        if (v[i]==0)
        {
            gr[x][y][z][m]=i;
            return gr[x][y][z][m];
        }
        return -1;
}

void solve()
{
    scanf("%d",&n);

    for (int i=1;i<=n;i++)
    for (int j=1;j<=n;j++)
    scanf("%d",&a[i][j]);


    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            for (int k=1;k<=n;k++)
            for (int l=1;l<=n;l++)
                gr[i][j][k][l]=-1;

    grundy(1,1,n,n);

    if (gr[1][1][n][n]!=0) printf("First\n"); else printf("Second\n");

    return;

}

int main()
{
    scanf("%d",&t);

    while(t--)
        solve();

    return 0;
}