// https://codeforces.com/contest/570/problem/D

#include<bits/stdc++.h>
using namespace std;
// # define int long long
static constexpr int MXN = 5e5 + 5;

void dbg()
{
    cout<<".";
}

int sz[MXN], euler[MXN], tin[MXN], tout[MXN], alp[MXN], depth[MXN];
int timer = 0;
vector<int> edges[MXN], nodesdeph[MXN], prefxr[MXN];
int xr = 0, mxdep = 0;

void dfseuler(int node, int parent)
{
    depth[node] = (parent == -1 ? 0 : depth[parent]) + 1;
    mxdep = max(mxdep, depth[node]);
    sz[node] = 1;
    euler[timer] = node;
    tin[node] = timer++;
    nodesdeph[depth[node]].emplace_back(tin[node]); 
    for(auto &nb : edges[node])
        if(nb != parent)
        {
            dfseuler(nb, node);
            sz[node] += sz[nb];
        }
    tout[node] = timer;
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n, m;
    cin>>n>>m;
    for(int i = 1; i < n; i++)
    {
        int p;
        cin>>p;
        p--;
        edges[p].emplace_back(i);
        edges[i].emplace_back(p);
    }
    // dbg();
    string s;
    cin>>s;
    // dbg();
    int ssz = s.size();
    for(int i = 0; i < ssz; i++)
    {
        char c;
        // cin>>c;
        c = s[i];
        alp[i] = (int)(c - 'a');
    }
    // dbg();
    dfseuler(0, -1);
    // int rsz = nodesdeph.size();
    int rsz = mxdep;
    // for(auto &rowndph : nodesdeph)
    for(int i = 1; i <= rsz; i++)
    {
        int xr = 0;
        int csz = nodesdeph[i].size();
        prefxr[i].resize(csz); // *
        for(int j = 0; j < csz; j++)
        {
            xr = xr  ^ (1 << alp[euler[nodesdeph[i][j]]]); // * missed storing parity in bits
            prefxr[i][j] = xr;
        }
    }
    // dbg();
    while(m--)
    {
        int v, h;
        // dbg();
        cin>>v>>h;
        v--;
        // dbg();
        if(h > mxdep or nodesdeph[h].empty())
        {
            cout<<"Yes\n";
            continue;
        }
        int start = lower_bound(nodesdeph[h].begin(), nodesdeph[h].end(), tin[v]) - nodesdeph[h].begin();
        int end = upper_bound(nodesdeph[h].begin(), nodesdeph[h].end(), tout[v] - 1) - nodesdeph[h].begin(); 
        int sxrid = (start == 0 ? 0 : prefxr[h][start - 1]);
        int exrid = prefxr[h][end - 1];
        int xrrange = exrid ^ sxrid;
        if(start == end) cout<<"Yes\n"; 
        else if(xrrange == 0 or ((xrrange & (xrrange - 1)) == 0)) cout<<"Yes\n"; // * brackets order matter
        else cout<<"No\n";
    }
}