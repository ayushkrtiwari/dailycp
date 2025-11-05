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
    int t = 1;
    // cin>>t;
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
        auto rootgrundy = [&](int node)
        {
            int xrr = 0;
            for(auto it : adj[node])
            {
                if(!vis[it])
                {
                    xrr ^= dfs(it, grundy, vis, adj);
                }
            }
            return xrr;
        };
        // int rootgrundy = dfs(0, grundy, vis, adj);
        // if(rootgrundy - 1) cout<<"Alice\n";
        if(rootgrundy(0)) cout<<"Alice\n";
        else cout<<"Bob\n";
    }
    return 0;
}
