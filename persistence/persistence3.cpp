// https://judge.yosupo.jp/problem/persistent_unionfind

#include<bits/stdc++.h>
using namespace std;

struct Query
{
    int t, k, u, v, idx;
};

struct DSURollback
{
    int _n;
    vector<int> parent, sz;
    vector<pair<int,int>> st;
    DSURollback(int n): _n(n), parent(n), sz(n)
    {
        iota(parent.begin(), parent.end(), 0);
        fill(sz.begin(), sz.end(), 1);
    }
    int find(int x)
    {
        if(x == parent[x]) return x;
        return find(parent[x]);
    }
    void merge(int u, int v)
    {
        int pu = find(u);
        int pv = find(v);
        if(pu == pv) return;
        if(sz[pu] < sz[pv])
        swap(pu, pv);
        st.push_back({pv, sz[pu]});
        parent[pv] = pu;
        sz[pu] += sz[pv];
    }
    int snapshot()
    {
        return st.size();
    }

    void rollback(int snap)
    {
        while(st.size() > snap)
        {
            auto [b, oldsz_a] = st.back();
            st.pop_back();
            sz[parent[b]] = oldsz_a;
            parent[b] = b;
        }
    }
};

int main()
{
    int n, q;
    cin>>n>>q;
    vector<Query> query(q);
    DSURollback dsu(n);
    vector<int> t(q), k(q), u(q), v(q);
    for(int i = 0; i < q; i++)
    {
        cin>>query[i].t>>query[i].k>>query[i].u>>query[i].v;
        // query[i].u--, query[i].v--;
        t[i] = query[i].t;
        k[i] = query[i].k;
        u[i] = query[i].u;
        v[i] = query[i].v;
        query[i].idx = i;
    }
    vector<vector<int>> children(q + 1);  // also for node Q for -1 version
    // push into children, make version tree, root node Q for -1 version
    for(auto &qry: query)
    {
        if(qry.k == -1) children[q].push_back(qry.idx);
        else children[qry.k].push_back(qry.idx);
    }
    vector<int> res(q);
    function<void(int)> dfs = [&](int node)
    {
        int snap = dsu.snapshot();
        if(node < q)
        {
            if(t[node] == 0)
            {
                dsu.merge(u[node], v[node]);
            }
            else
            res[node] = (dsu.find(u[node]) == dsu.find(v[node]));
        }
        // if(t[node] == 1 and k[node] == -1) res[node] = 0;
        for(int child: children[node])
        dfs(child);
        dsu.rollback(snap);
    };
    
    dfs(q);

    for(int i = 0; i < q; i++)
    if(t[i] == 1) cout<<res[i]<<"\n";
}
// ________________________________________________________________________________________________

// GPT:

// #include <bits/stdc++.h>
// using namespace std;

// // rollbackable DSU
// struct RollbackDSU {
//     vector<int> p, sz;
//     vector<pair<int,int>> stk;
//     RollbackDSU(int n=0): p(n), sz(n,1) {
//         iota(p.begin(), p.end(), 0);
//     }
//     int find(int x) const {
//         while (p[x] != x) x = p[x];
//         return x;
//     }
//     // returns true if they were in different sets
//     bool unite(int a, int b) {
//         a = find(a);
//         b = find(b);
//         if (a == b) return false;
//         if (sz[a] < sz[b]) swap(a,b);
//         // record (child_root, old_size_of_parent)
//         stk.emplace_back(b, sz[a]);
//         p[b] = a;
//         sz[a] += sz[b];
//         return true;
//     }
//     int snapshot() const {
//         return stk.size();
//     }
//     void rollback(int snap) {
//         while ((int)stk.size() > snap) {
//             auto [b, old_sza] = stk.back();
//             stk.pop_back();
//             int a = p[b];     // current parent
//             p[b] = b;         // detach
//             sz[a] = old_sza;  // restore size
//         }
//     }
// };

// int main(){
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);

//     int N, Q;
//     cin >> N >> Q;

//     // read queries and build the version‐tree
//     // we treat versions as nodes 0..Q-1, and an artificial root Q
//     vector<vector<int>> children(Q+1);
//     vector<int> type(Q), k(Q), u(Q), v(Q);
//     for(int i = 0; i < Q; i++){
//         cin >> type[i] >> k[i] >> u[i] >> v[i];
//         if (k[i] == -1) 
//             children[Q].push_back(i);
//         else
//             children[k[i]].push_back(i);
//     }

//     vector<int> answer(Q, -1);
//     RollbackDSU dsu(N);

//     // DFS over the version‐tree
//     function<void(int)> dfs = [&](int node){
//         int snap = dsu.snapshot();

//         if (type[node] == 0) {
//             // add edge (u[node], v[node])
//             dsu.unite(u[node], v[node]);
//         } else {
//             // connectivity query
//             answer[node] = (dsu.find(u[node]) == dsu.find(v[node]));
//         }

//         // recurse to children (future versions built on this one)
//         for (int c : children[node]) {
//             dfs(c);
//         }

//         // undo this node’s union (if any)
//         dsu.rollback(snap);
//     };

//     // start from artificial root Q
//     dfs(Q);

//     // print answers for all type‐1 queries in input order
//     for(int i = 0; i < Q; i++){
//         if (type[i] == 1) 
//             cout << answer[i] << "\n";
//     }
//     return 0;
// }
