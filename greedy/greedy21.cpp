// जय श्री राम  JAI SHREE RAM

// https://codeforces.com/problemset/problem/2052/F

// You can use DP.
// You can use greedy too.
// Just do vertical placement if both up and down are available.
// Else do horizontal placement.
// If any place still left after all placements, then no solution feasible
// If at any point there is 2 * 2 is to be filled, then multiple solution
// Else unique solution only

#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        vector<vector<char>> v(2,vector<char>(n));
        for(int i = 0; i < 2; i++)
        for(int j = 0; j < n; j++)
        cin>>v[i][j];
        bool ispossible = true;
        bool ismultiple = false;
        int i;
        for(i = 0; i < n - 1; i++)
        {
            if(v[0][i] == '.' and v[0][i] == v[1][i] and v[0][i + 1] == '.' and v[0][i + 1] == v[1][i + 1])
            ismultiple = true;
            if(v[0][i] == '.' and v[0][i] == v[1][i])
            v[0][i] = '#', v[1][i] = '#';
            if(v[0][i] == '.' and v[0][i + 1] == '.')
            v[0][i] = '#', v[0][i + 1] = '#';
            if(v[1][i] == '.' and v[1][i + 1] == '.')
            v[1][i] = '#', v[1][i + 1] = '#';
        }
        if(v[0][i] == v[1][i]) v[0][i] = '#', v[1][i] = '#';
        for(int i = 0; i < 2; i++)
        for(int j = 0; j < n; j++)
        if(v[i][j] == '.')
        {
            ispossible = false;
            break;
        }
        if(!ispossible)
        cout<<"None\n";
        else
        {
            if(ismultiple)
            cout<<"Multiple\n";
            else
            cout<<"Unique\n";
        }
    }
}