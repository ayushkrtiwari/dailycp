// https://codeforces.com/group/DeilFl9Bhi/contest/329185/problem/H

#include<bits/stdc++.h>
using namespace std;

void solve()
{
    int n, m;
    cin>>n>>m;
    // vector<vector<char>> v(n, vector<char>(m));
    // for(auto &x : v)
    // for(auto &y : x)
    // cin>>y;
    // int rowdis, coldis;
    // vector<int> countrow(n, 0);
    
    // for(int i = 0; i < n; i++)
    // for(int j = 0; j < m; j++)
    // if(v[i][j] == '*') countrow[i]++;
    
    // for(int i = 0; i < n; i++)
    // {
    //     if(countrow[i] == 2)
    //     {
    //         for(int j = 0; j < m; j++)
    //         if(v[i][j] == '*')
    //         {
    //             for(int k = j + 1; k < m; k++)
    //             {
    //                 if(v[i][k] == '*')
    //                 {
    //                     rowdis = k - j;
    //                     break;
    //                 }
    //             }
    //         }
    //     }
    // }
    
    // vector<int> countcol(m, 0);
    
    // for(int i = 0; i < m; i++)
    // for(int j = 0; j < n; j++)
    // if(v[i][j] == '*') countcol[i]++;
    
    // vector<vector<char>> transpose(m, vector<char>(n));
    // for(int i = 0; i < m; i++)
    // for(int j = 0; j < n; j++)
    //     transpose[i][j] = v[j][i];

    // for(int i = 0; i < m; i++)
    // {
    //     if(countcol[i] == 2)
    //     {
    //         for(int j = 0; j < n; j++)
    //         if(v[i][j] == '*')
    //         {
    //             for(int k = j + 1; k < n; k++)
    //             {
    //                 if(v[i][k] == '*')
    //                 {
    //                     coldis = k - j;
    //                     break;
    //                 }
    //             }
    //         }
    //     }
    // }
    
    // for(int i = 0; i < n; i++)
    // {
        
    // }
    
    vector<pair<int,int>> xy(3);
    int cnt = 0;
    int x, y;
    
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            char ch;
            cin>>ch;
            if(ch == '*')
            xy[cnt++] = {i + 1, j + 1};
        }
    }
    
    if(xy[0].first == xy[1].first)
    {
        if(xy[0].second == xy[2].second)
        {
            x = xy[2].first;
            y = xy[1].second;
        }
        else
        {
            x = xy[2].first;
            y = xy[0].second;
        }
    }
    else if(xy[1].first == xy[2].first)
    {
        if(xy[0].second == xy[1].second)
        {
            x = xy[0].first;
            y = xy[2].second;
        }
        else
        {
            x = xy[0].first;
            y = xy[1].second;
        }
    }
    else if(xy[0].first == xy[2].first)
    {
        if(xy[0].second == xy[1].second)
        {
            x = xy[1].first;
            y = xy[2].second;
        }
        else
        {
            x = xy[1].first;
            y = xy[0].second;
        }
    }
    else if(xy[1].second == xy[0].second)
    {
        if(xy[0].first == xy[2].first)
        {
            x = xy[1].first;
            y = xy[2].second;
        }
        else
        {
            x = xy[0].first;
            y = xy[2].second;
        }
    }
    else if(xy[0].second == xy[2].second)
    {
        if(xy[0].first == xy[1].first)
        {
            x = xy[2].first;
            y = xy[1].second;
        }
        else
        {
            x = xy[0].first;
            y = xy[1].second;
        }
    }
    else if(xy[2].second == xy[1].second)
    {
        if(xy[0].first == xy[1].first)
        {
            x = xy[2].first;
            y = xy[0].second;
        }
        else
        {
            x = xy[1].first;
            y = xy[0].second;
        }
    }
    cout<<x<<" "<<y<<"\n";
}

int main()
{
    int t = 1;
    // cin>>t;
    while(t--)
    solve();
}