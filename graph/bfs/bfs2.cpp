// https://atcoder.jp/contests/abc197/tasks/abc197_f

#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9;

int main() {
	// your code goes here
	int n, m;
    cin>>n>>m;
    vector<vector<pair<int,char>>> edges(n);
    for(int i = 0; i < m; i++)
    {
        int x, y;
        char c;
        cin>>x>>y>>c;
        x--, y--;
        edges[x].push_back({y, c});
        edges[y].push_back({x, c});
    }
    queue<pair<int,int>> q;
    q.push({0, n - 1});
    vector<vector<int>> dist(n, vector<int>(n, inf));
    dist[0][n - 1] = 0;
    while(!q.empty())
    {
        auto [u, v] = q.front();
        q.pop();
        for(auto uu: edges[u])
        {
            for(auto vv: edges[v])
            {
                if(dist[uu.first][vv.first] != inf) continue;
                if(uu.second != vv.second) continue;
                dist[uu.first][vv.first] = dist[u][v] + 1;
                q.push({uu.first, vv.first});
            }
        }
    }
    int ans = inf;
    for(int i = 0; i < n; i++)
    {
        // edges
        for(auto [j, _] : edges[i])
        {
            if(dist[i][j] == inf) continue;
            ans = min(ans, 2 * dist[i][j] + 1);
        }
    }
    for(int i = 0; i < n; i++)
    {
        // nodes
        if(dist[i][i] == inf) continue;
        ans = min(ans, 2 * dist[i][i]);
    }
    cout<<(ans == inf ? -1 : ans)<<"\n";
}
