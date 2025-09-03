// https://codeforces.com/contest/570/problem/D

// * : where i had mistaken
// using long long instead of int gives TLE
// not using fastio gives TLE

// empty vector, even times character, only one odd character are palindromes
// We need to get the query answer as : in subtree of node v(inclusive does not change solution, both are palindrome),
// take all nodes at depth(1-indexed) and check if they could form palindrome
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
    nodesdeph[depth[node]].emplace_back(tin[node]); // tin is stored in increasing order, hence binary search feasible
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
        if(h > mxdep or nodesdeph[h].empty()) // * empty vector is palindrome, 2nd condn is sufficient
        {
            cout<<"Yes\n";
            continue;
        }
        int start = lower_bound(nodesdeph[h].begin(), nodesdeph[h].end(), tin[v]) - nodesdeph[h].begin();
        int end = upper_bound(nodesdeph[h].begin(), nodesdeph[h].end(), tout[v] - 1) - nodesdeph[h].begin(); 
        // tout for any node a/dfseuler algorithm : tout > tin not tout >= tin, 
        // hence to find till last tin, we use upper bound on tout - 1
        // dbg();
        int sxrid = (start == 0 ? 0 : prefxr[h][start - 1]);
        int exrid = prefxr[h][end - 1];
        int xrrange = exrid ^ sxrid;
        if(start == end) cout<<"Yes\n"; // start > end is never possible since tin < tout, tin <= tout - 1
        else if(xrrange == 0 or ((xrrange & (xrrange - 1)) == 0)) cout<<"Yes\n"; // * brackets order matter
        else cout<<"No\n";
    }
}

// __________________________________________________________________________________________________________

// Arpa DSU by tree code :

#include <bits/stdc++.h>
#define pb push_back
#define X first
#define Y second
//#define int long long
using namespace std;
template <class T, class L> bool smax(T &x,L y){  return x < y ? (x = y, 1) : 0;  }
template <class T, class L> bool smin(T &x,L y){  return y < x ? (x = y, 1) : 0;  }
typedef pair<int, int> pii;

const int maxn = 5e5 + 17, z = 26;
int n, cntf[maxn], sz[maxn], h[maxn];
vector<int> g[maxn];
vector<pii> ass[maxn];
string s;
bool big[maxn], cnt[maxn][z], ans[maxn];
void getsz(int v){
    sz[v] = 1;
    for(auto u : g[v])
	h[u] = h[v] + 1, getsz(u), sz[v] += sz[u];
}
void add(int v, int x){
    cntf[ h[v] ] -= cnt[ h[v] ][ s[v] - 'a'];
    cnt[ h[v] ][ s[v] - 'a'] ^= 1;
    cntf[ h[v] ] += cnt[ h[v] ][ s[v] - 'a'];
    for(auto u : g[v])
	if(!big[u])
	    add(u, x);
}
void dfs(int v, bool keep){
    int mx = 0, b;
    for(auto u : g[v])
	if(smax(mx, sz[u]))
	    b = u;
    for(auto u : g[v])
	if(u != b)  dfs(u, 0);
    if(mx)  big[b] = 1, dfs(b, 1);
    add(v, 1);
    for(auto q : ass[v])
	ans[q.Y] = cntf[q.X] <= 1;
    if(mx)  big[b] = 0;
    if(!keep)  add(v, -1);
}
main(){
    ios::sync_with_stdio(0), cin.tie(0);
    int m;  cin >> n >> m;
    for(int i = 1, p; i < n; i++)
	cin >> p, g[p - 1].pb(i);
    getsz(0);
    cin >> s;
    for(int i = 0, v, h; i < m; i++)
	cin >> v >> h, ass[v - 1].pb({h - 1, i});
    dfs(0, 0);
    for(int i = 0; i < m; i++)
	cout << (ans[i] ? "Yes" : "No") << '\n';
    return 0;
}