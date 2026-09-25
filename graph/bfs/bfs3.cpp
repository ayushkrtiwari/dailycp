// https://codeforces.com/problemset/problem/29/E

// Near Pass. Same code TLEs on GCC20 or above compiler. sometimes TLE, sometimes 960 ms

#include<bits/stdc++.h>
using namespace std;
const int inf = 1e9;

vector<vector<int>> edges;

int main()
{
    int n,m;
    cin>>n>>m;
    edges.resize(n);
    vector<pair<int,int>> resa, resb;
    for(int i = 0; i < m; i++)
    {
        int x, y;
        cin>>x>>y;
        x--, y--;
        edges[x].emplace_back(y);
        edges[y].emplace_back(x);
    }
    deque<pair<int,int>> q;
    vector<vector<pair<int,int>>> parent(n, vector<pair<int,int>>(n));
    vector<vector<int>> dist(n, vector<int>(n, inf));
    q.push_back({n - 1, 0});
    dist[n - 1][0] = 0;
    while(!q.empty())
    {
        auto [a, b] = q.front();
        q.pop_front();
        if(a == 0 and b == n - 1) break;
        int d = dist[a][b];
        for(auto x: edges[a])
        for(auto y: edges[b])
        {
            if(x == y) continue;
            if(dist[x][y] == inf)
            {
                q.push_back({x, y});
                dist[x][y] = d + 1;
                parent[x][y] = {a, b};
            }
        }
    }
    if(dist[0][n - 1] == inf)
    cout<<-1<<"\n";
    else
    {
        cout<<dist[0][n - 1]<<"\n";
        vector<int> resa, resb;
        int alice = 0, bob = n - 1;
        resa.emplace_back(alice), resb.emplace_back(bob);
        for(int i = 0; i < dist[0][n - 1]; i++)
        {
            auto [_,__] = parent[alice][bob];
            alice = _;
            bob = __;
            resa.emplace_back(alice), resb.emplace_back(bob);
        }
        // reverse(resa.begin(), resa.end());
        // reverse(resb.begin(), resb.end());
        for(auto x: resa)
        cout<<x + 1<<" ";
        cout<<"\n";
        for(auto y: resb)
        cout<<y + 1<<" ";
    }
}

// ________________________________________________________________________________________

// What a conincidence, a blog on MLE with comments of below line I just read and asked Him
// will I ever encounter such a question which has such margin of time constraints
// Just his style of answering devotion
// C style arrays have better time complexity than C++

// #pragma GCC optimize("O3,unroll-loops,Ofast")
// #pragma GCC target("sse2,avx2")

#include<bits/stdc++.h>
using namespace std;
const int inf = 1e9;

vector<vector<int>> edges;
pair<int,int> parent[500][500];
int dist[500][500];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n,m;
    cin>>n>>m;
    edges.resize(n);
    vector<pair<int,int>> resa, resb;
    for(int i = 0; i < m; i++)
    {
        int x, y;
        cin>>x>>y;
        x--, y--;
        edges[x].emplace_back(y);
        edges[y].emplace_back(x);
    }
    queue<pair<int,int>> q;
    // vector<vector<pair<int,int>>> parent(n, vector<pair<int,int>>(n));
    // vector<vector<int>> dist(n, vector<int>(n, inf));

    for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
    dist[i][j] = inf;
    
    q.push({n - 1, 0});
    dist[n - 1][0] = 0;
    while(!q.empty())
    {
        auto [a, b] = q.front();
        q.pop();
        if(a == 0 and b == n - 1) break;
        int d = dist[a][b];
        for(auto x: edges[a])
        for(auto y: edges[b])
        {
            if(x == y) continue;
            if(dist[x][y] == inf)
            {
                q.push({x, y});
                dist[x][y] = d + 1;
                parent[x][y] = {a, b};
            }
        }
    }
    if(dist[0][n - 1] == inf)
    cout<<-1<<"\n";
    else
    {
        cout<<dist[0][n - 1]<<"\n";
        vector<int> resa, resb;
        int alice = 0, bob = n - 1;
        resa.emplace_back(alice), resb.emplace_back(bob);
        for(int i = 0; i < dist[0][n - 1]; i++)
        {
            auto [_,__] = parent[alice][bob];
            alice = _;
            bob = __;
            resa.emplace_back(alice), resb.emplace_back(bob);
        }
        // reverse(resa.begin(), resa.end());
        // reverse(resb.begin(), resb.end());
        for(auto x: resa)
        cout<<x + 1<<" ";
        cout<<"\n";
        for(auto y: resb)
        cout<<y + 1<<" ";
    }
}

// __________________________________________________________________________________
// GPT's more optimization:

// Using raw C‑style arrays for your large dist and parent tables is a good micro‑optimization, 
// but most of the heavy‐lifting here is the BFS itself on the 𝑛^2
// product graph. A few more tweaks will squeeze out any remaining overhead:

// 1. Use a simple queue instead of deque. You only ever push back and pop front.

// 2. Store your adjacency lists in static arrays (a “forward star”), rather than vector<vector<int>>, 
// to eliminate the tiny bounds‐check / pointer indirection overhead.

// 3. Pack your state (𝑢,𝑣) into a single 32‑bit integer if you like, to avoid pair<int,int> overhead.

// A “maximally tuned” version. It uses:

// 1. A forward‐star representation for the graph.

// 2.Static int dist[500][500]; and pair<short,short> parent[500][500];

// 3. A plain queue<int> over packed states (u<<9)|v since 500 < 2^9.

#pragma GCC optimize("O3,unroll-loops,Ofast")
#pragma GCC target("sse2,avx2")

#include <bits/stdc++.h>
using namespace std;

// Max n=500
static const int MAXN = 500;
static const int INF  = 1e9;

// --- forward‐star adjacency ---
// Simple integer indexing rather than pointer chasing or virtual calls.

// to[ec]  = v;       // record that edge ec goes to v
// nxt[ec] = head[u]; // chain it on top of whatever used to be the first edge
// head[u] = ec;      // now the “first” edge out of u is ec
// ec++;              // bump to the next free slot


int head[MAXN], to[20000*2], nxt[20000*2], ec=0;
void add_edge(int u,int v){
    to[ec] = v; nxt[ec] = head[u]; head[u] = ec++;
}

// dist[u][v], packed state = (u<<9)|v
int dist_arr[MAXN][MAXN];
pair<short,short> parent_arr[MAXN][MAXN];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    // build adjacency
    for(int i=0;i<n;i++) head[i] = -1;
    for(int i=0,u,v;i<m;i++){
        cin >> u >> v;
        --u; --v;
        add_edge(u,v);
        add_edge(v,u);
    }

    // init dist to INF
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            dist_arr[i][j] = INF;

    queue<int> q;
    // start at (0, n-1)
    dist_arr[0][n-1] = 0;
    q.push((0<<9)|(n-1));

    // BFS on product graph
    while(!q.empty()){
        int packed = q.front(); q.pop();
        int u = packed >> 9;
        int v = packed & 511;
        int d = dist_arr[u][v];
        if(u==n-1 && v==0) break;

        // iterate neighbors of u
        for(int ei = head[u]; ei!=-1; ei = nxt[ei]){
            int u2 = to[ei];
            // iterate neighbors of v
            // for(int e = head[u]; e != -1; e = nxt[e]){
            //     int v = to[e];
            //     // now (u,v) is one of your edges
            // }

            for(int ej = head[v]; ej!=-1; ej = nxt[ej]){
                int v2 = to[ej];
                if(u2==v2) continue;          // can't meet at same crossroads
                if(dist_arr[u2][v2]==INF){
                    dist_arr[u2][v2] = d+1;
                    parent_arr[u2][v2] = {short(u), short(v)};
                    q.push((u2<<9)|v2);
                }
            }
        }
    }

    int k = dist_arr[n-1][0];
    if(k==INF){
        cout << -1 << "\n";
        return 0;
    }

    // reconstruct
    vector<int> bob(k+1), alex(k+1);
    int bu = n-1, av = 0;
    for(int step=k; step>=0; --step){
        bob[step] = bu; 
        alex[step] = av;
        if(step>0){
            auto [pu,pv] = parent_arr[bu][av];
            bu = pu; av = pv;
        }
    }

    // output (1‑based)
    cout<<k<<"\n";
    for(int x:bob)  cout<<(x+1)<<' ';
    cout<<"\n";
    for(int y:alex) cout<<(y+1)<<' ';
    cout<<"\n";
    return 0;
}
