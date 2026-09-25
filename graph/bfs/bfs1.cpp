// https://atcoder.jp/contests/abc168/tasks/abc168_d

#include<bits/stdc++.h>
using namespace std;
const int inf = 1e9;
int main()
{
    int n, m;
    cin>>n>>m;
    vector<vector<int>> edges(n);
    for(int i = 0; i < m; i++)
    {
        int x, y;
        cin>>x>>y;
        edges[--x].emplace_back(--y);
        edges[y].emplace_back(x);
    }
    queue<int> q;
    q.push(0);
    vector<int> parent(n);
    vector<int> dist(n, inf);
    dist[0] = 0;
    while(!q.empty())
    {
        int x = q.front();
        q.pop();
        int d = dist[x];
        for(auto nbour: edges[x])
        {
            if(dist[nbour] != inf) continue;
            dist[nbour] = d + 1;
            parent[nbour] = x;
            q.push(nbour);
        }
    }
    cout<<"Yes\n";
    for(int i = 1; i < n; i++)
    cout<<parent[i] + 1<<"\n";
}