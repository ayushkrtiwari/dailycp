// जय श्री राम  JAI SHREE RAM

// https://www.hackerrank.com/contests/5-days-of-game-theory/challenges/deforestation/problem

// Green Hackenbush on General Rooted Graphs, Unbounded Nim Game

// For branches you take nim sum(xor) of all branches and replace them with one branch of that length
// For rest, just take the length of the branch as nim sum.

// Refer Resources section for concept

#include <bits/stdc++.h>
using namespace std;

int dfs(int node, vector<int> &grundy, vector<int>&vis, vector<vector<int>> &adj)
{
    vis[node] = 1;
    int sz = adj[node].size();
    if(sz == 0) return grundy[node] = 1;
    int xr = 0;
    for(auto it : adj[node])
    {
        if(!vis[it])
        {
            xr ^= dfs(it, grundy, vis, adj);
        }
    }
    return grundy[node] = 1 + xr;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        vector<vector<int>> adj(n);
        for(int i = 0; i < n - 1; i++)
        {
            int u, v;
            cin>>u>>v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<int> grundy(n, 0);
        vector<int> vis(n, 0);
        // I don't know why the commented lines logic fails on the cases
        // auto rootgrundy = [&](int node)
        // {
        //     int xrr = 0;
        //     for(auto it : adj[node])
        //     {
        //         if(!vis[it])
        //         {
        //             xrr ^= dfs(it, grundy, vis, adj);
        //         }
        //     }
        //     return xrr;
        // };
        int rootgrundy = dfs(0, grundy, vis, adj);
        if(rootgrundy - 1) cout<<"Alice\n";
        // if(rootgrundy(0)) cout<<"Alice\n";
        else cout<<"Bob\n";
    }
    return 0;
}
