// https://www.codechef.com/problems/GERALD07?tab=statement

#include<bits/stdc++.h>
using namespace std;
const int blocks = 4e2 + 50; // for m = 2e5, root m approx 450

struct Query
{
    int l,r,idx;
    inline pair<int,int> toPair() const
    {
        return make_pair(l/blocks, r);
    }
};

inline bool operator<(const Query &qa, const Query &qb)
{
    return qa.toPair() < qb.toPair();
}

struct DSUPersistence
{
    int _n;
    vector<int> parent, sz;
    stack<pair<int,int>> stk; 
    // prefer vector instead of stack for binary search implementation while full persistence, version finding
    int comps;
    DSUPersistence(int n): _n(n), parent(n), sz(n)
    {
        iota(parent.begin(), parent.end(), 0);
        fill(sz.begin(), sz.end(), 1);
        comps = _n;
    }
    int findparent(int x)
    {
        if(x == parent[x]) return x;
        return findparent(parent[x]); 
        // do not path compress since we merge and findparent, 
        // then at some point even after rollback we cant restore effectively
        // still if want pathcompression, then need to pass into stack the parents everytime or 
        // if you need to both compress paths and support fast undo, 
        // you typically switch to a fully persistent pointer‑based structure 
        // (e.g.\ fat‑node or node‑copying) or a more complex bookkeeping scheme.
        // For our offline Mo‑style + rollback approach, skipping path‑compression is by far the simplest and fastest route.
    }
    void reset()
    {
        // stk.clear();
        while(!stk.empty())
        stk.pop();
        comps = _n;
        iota(parent.begin(), parent.end(), 0);
        fill(sz.begin(), sz.end(), 1);
    }
    void merge(int x, int y)
    {
        int px = findparent(x);
        int py = findparent(y);
        if(px == py) return;
        if(sz[px] < sz[py]) swap(px, py);
        stk.push({py, sz[px]}); 
        // push small sized node and size of large component for rollback
        sz[px] += sz[py];
        parent[py] = px;
        comps--;
    }
    int snapshot()
    {
        return stk.size();
    }
    void rollback(int snap)
    {
        while(stk.size() > snap) // restore all changes till snapshot
        {
            auto [b, oldsz_a] = stk.top();
            stk.pop();
            sz[b] = 1; 
            // this is optional since sz[b] never changed since ultimate parents size changes
            sz[parent[b]] = oldsz_a;
            parent[b] = b;
            comps++;
        }
    }
};

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,m,q;
        cin>>n>>m>>q;
        vector<Query> query(q);
        vector<int> res(q);
        vector<pair<int,int>> edges(m);
        for(int i = 0; i < m; i++)
        {
            cin>>edges[i].first>>edges[i].second;
            edges[i].first--, edges[i].second--;
        }
        DSUPersistence dsu(n);
        vector<Query> large;
        for(int i = 0; i < q; i++)
        {
            cin>>query[i].l>>query[i].r;
            query[i].l--, query[i].r--;
            query[i].idx = i;
        }
        for(int i = 0; i < q; i++)
        {
            // for small queries of < root(m), we directly do operation over whole range
            if(query[i].r - query[i].l + 1 <= blocks)
            {
                int snap = dsu.snapshot();
                int save_comp = dsu.comps;
                for(int x = query[i].l; x <= query[i].r; x++)
                dsu.merge(edges[x].first, edges[x].second);
                res[i] = dsu.comps;
                dsu.rollback(snap);
                dsu.comps = save_comp;
            }
            else
            {
                large.push_back(query[i]);
            }
        }
        
        sort(large.begin(), large.end());
        // large queries are sorted in mo order
        
        dsu.reset();
        
        int currBlock = -1; // blocks are 0 indexed
        int currR = -1; // initialisation value doesn't matter since it will be updated
        for(auto &q : large)
        {
            int block = q.l/blocks;
            int block_end = min(m - 1, (block * blocks) + blocks - 1); // last block may be less than 'blocks' size
            if(currBlock != block)
            {
                dsu.reset();
                currBlock = block;
                currR = block_end + 1;
            }
            while(currR <= q.r)
            {
                dsu.merge(edges[currR].first, edges[currR].second);
                currR++;
            }
            int snap = dsu.snapshot();
            int comp_saved = dsu.comps;
            for(int i = min(q.r, block_end); i >= q.l; i--)
            {
                dsu.merge(edges[i].second, edges[i].first);
            }
            res[q.idx] = dsu.comps;
            dsu.rollback(snap);
            dsu.comps = comp_saved;
        }
        for(auto &r: res)
        cout<<r<<"\n";
    }
}

// _______________________________________________________________________________________________________

// Better Code: 

// struct DSU {
//     int p[N], sz[N];
//     stack<pair<int, int>> st;
//     int op = 0;

//     DSU() {
//         iota(p, p + N, 0);
//         fill(sz, sz + N, 1);
//     }

//     void reset(int n) {
//         while (!st.empty())
//             st.pop();
//         iota(p, p + n + 1, 0);
//         fill(sz, sz + n + 1, 1);
//         op = 0;
//     }

//     void add_chk() {
//         st.push({-1, -1});
//     }

//     void rollback() {
//         while (st.top().Y != -1) {
//             int x = st.top().X, y = st.top().Y;
//             if (x > 0) p[x] = y;
//             else if (x < 0) sz[-x] = y;
//             else op = y;
//             st.pop();
//         }
//         st.pop();
//     }

//     int find_set(int v, bool flag) {
//         if (v == p[v])
//             return v;

//         if (flag) st.push({v, p[v]});
//         return p[v] = find_set(p[v], flag);
//     }

//     void union_sets(int u, int v, bool flag) {
//         u = find_set(u, flag), v = find_set(v, flag);

//         if (u == v)
//             return;

//         if (sz[u] < sz[v])
//             swap(u, v);

//         if (flag) {
//             st.push({-u, sz[u]});
//             st.push({v, p[v]});
//             st.push({0, op});
//         }

//         p[v] = u, sz[u] += sz[v], ++op;
//     }
// } dsu;

// vector<pair<int, point>> bk[N];
// point e[N];
// int ans[N];

// void solve() {
//     int n, m, q;
//     cin >> n >> m >> q;

//     for (int i = 0; i < m; ++i)
//         bk[i].clear();

//     for (int i = 0; i < m; ++i)
//         cin >> e[i].X >> e[i].Y;

//     dsu.reset(n + 5);

//     for (int i = 0; i < q; ++i) {
//         int l, r;
//         cin >> l >> r, --l, --r;

//         if (r - l <= B) {
//             dsu.add_chk();
//             for (int j = l; j <= r; ++j)
//                 dsu.union_sets(e[j].X, e[j].Y, true);

//             ans[i] = n - dsu.op;
//             dsu.rollback();
//         }
//         else
//             bk[l / B].pb({r, {-l, i}});
//     }

//     for (int b = 0; b < (m / B); ++b) {
//         sort(all(bk[b]));
//         dsu.reset(n + 5);

//         int ptr = (b + 1) * B;

//         for (auto w : bk[b]) {
//             int r = w.X, l = -w.Y.X, i = w.Y.Y;

//             while (ptr <= r)
//                 dsu.union_sets(e[ptr].X, e[ptr].Y, false), ++ptr;

//             dsu.add_chk();

//             for (int j = (b + 1) * B - 1; j >= l; --j)
//                 dsu.union_sets(e[j].X, e[j].Y, true);
//             ans[i] = n - dsu.op;

//             dsu.rollback();
//         }
//     }

//     for (int i = 0; i < q; ++i)
//         cout << ans[i] << '\n';
// }

// int32_t main() {
//     fast_io;

//     int T;
//     cin >> T;
//     while (T--)
//         solve();
// }