// https://codeforces.com/problemset/problem/543/B

#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9;
vector<vector<int>> edges;
vector<vector<int>> dist;

void debug(int x)
{
    cout<<x<<"\n";
}

int main() {
	// your code goes here
    int n, m;
    cin>>n>>m;
    edges.resize(n);
    for(int i = 0; i < m; i++)
    {
        int x, y;
        cin>>x>>y;
        x--, y--;
        edges[x].push_back(y);
        edges[y].push_back(x);
    }
    int s0, t0, l0, s1, t1, l1;
    cin>>s0>>t0>>l0>>s1>>t1>>l1;
    s0--, t0--, s1--, t1--;
    dist.resize(n, vector<int>(n, inf));
    // 2d bfs DP without visited array
    for(int i = 0; i < n; i++)
    {
        queue<int> q;
        dist[i][i] = 0;
        q.push(i);
        while(!q.empty())
        {
            int x = q.front();
            q.pop();
            for(auto it: edges[x])
            {
                if(dist[i][it] == inf)
                {
                    dist[i][it] = dist[i][x] + 1;
                    q.push(it);
                }
            }
        }
    }
    int d = dist[s0][t0] <= l0 and dist[s1][t1] <= l1 ? dist[s0][t0] + dist[s1][t1] : inf;
    // debug(d);
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            int dis1 = dist[s0][i] + dist[i][j] + dist[j][t0];
            int dis2 = dist[s1][i] + dist[i][j] + dist[j][t1];
            int dis3 = dist[s1][j] + dist[j][i] + dist[i][t1];
            if(dis1 <= l0 and dis2 <= l1 and dis1 + dis2 - dist[i][j] < d)
            d = dis1 + dis2 - dist[i][j];
            if(dis1 <= l0 and dis3 <= l1 and dis1 + dis3 - dist[i][j] < d)
            d = dis1 + dis3 - dist[i][j];
        }
    }
    if(d == inf) cout<<-1<<"\n";
    else cout<<m - d;
}
// ____________________________________________________________________________________
// GPT code

// This code only considers to store dist array for 4 nodes s0, s1, t0, t1
// Hence, less space limit if we are given test cases and can't declare global 2D array 
// which takes RAM or global stack space much larger than memory heap stack of few MBs.

#include <bits/stdc++.h>
using namespace std;

static const int INF = 1e9;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> edges(n);
    for(int i = 0; i < m; i++){
        int x, y;
        cin >> x >> y;
        --x; --y;
        edges[x].push_back(y);
        edges[y].push_back(x);
    }

    int s0, t0, l0, s1, t1, l1;
    cin >> s0 >> t0 >> l0 >> s1 >> t1 >> l1;
    --s0; --t0; --s1; --t1;

    // BFS helper: returns dist[src][*]
    auto bfs_from = [&](int src){
        vector<int> d(n, INF);
        queue<int> q;
        d[src] = 0;
        q.push(src);
        while(!q.empty()){
            int u = q.front(); q.pop();
            for(int v: edges[u]){
                if(d[v] == INF){
                    d[v] = d[u] + 1;
                    q.push(v);
                }
            }
        }
        return d;
    };

    // Precompute distances from the four special nodes
    vector<int> D_s0 = bfs_from(s0);
    vector<int> D_t0 = bfs_from(t0);
    vector<int> D_s1 = bfs_from(s1);
    vector<int> D_t1 = bfs_from(t1);

    // Check baseline (no overlap)
    if (D_s0[t0] > l0 || D_s1[t1] > l1) {
        cout << -1 << "\n";
        return 0;
    }
    int best = D_s0[t0] + D_s1[t1];

    // Try overlapping via intermediate i→j
    for(int i = 0; i < n; ++i){
        // distances from i to all nodes
        vector<int> D_i = bfs_from(i);
        for(int j = 0; j < n; ++j){
            int dij = D_i[j];
            if (dij == INF) continue;

            // path0: s0 -> i -> j -> t0
            int p0 = D_s0[i] + dij + D_t0[j];
            // variant A: s1 -> i -> j -> t1
            int p1 = D_s1[i] + dij + D_t1[j];
            // variant B: s1 -> j -> i -> t1
            int p2 = D_s1[j] + dij + D_t1[i];

            if (p0 <= l0 && p1 <= l1)
                best = min(best, p0 + p1 - dij);
            if (p0 <= l0 && p2 <= l1)
                best = min(best, p0 + p2 - dij);
        }
    }

    cout << (m - best) << "\n";
    return 0;
}
