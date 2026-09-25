// ====== 1. Offline Dynamic Connectivity via Segment Tree + Rollback DSU ======
// Supports adding/removing edges offline, answering connectivity queries at points in time.

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct RollbackDSU {
    vector<int> p, sz;
    vector<pair<int,int>> stk;
    int comps;
    RollbackDSU(int n=0): p(n+1), sz(n+1,1), comps(n) {
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        while(p[x]!=x) x=p[x]; return x;
    }
    void unite(int a,int b) {
        a=find(a); b=find(b);
        if(a==b) { stk.emplace_back(-1,-1); return; }
        if(sz[a]<sz[b]) swap(a,b);
        stk.emplace_back(b, sz[a]);
        p[b]=a; sz[a]+=sz[b]; comps--;
    }
    int snapshot(){ return stk.size(); }
    void rollback(int snap) {
        while((int)stk.size()>snap) {
            auto [b, old_sza] = stk.back(); stk.pop_back();
            if(b==-1) continue;
            int a = p[b]; sz[a]=old_sza; p[b]=b; comps++;
        }
    }
};

// Segment tree over time [1..T], store for each node the edges active in that interval.
const int MAXQ = 200000;
vector<pair<int,int>> seg[4*MAXQ];

void seg_add(int idx,int l,int r,int ql,int qr,pair<int,int> edge){
    if(ql>r||qr<l) return;
    if(ql<=l && r<=qr) {
        seg[idx].push_back(edge);
        return;
    }
    int m=(l+r)>>1;
    seg_add(idx<<1, l, m, ql, qr, edge);
    seg_add(idx<<1|1, m+1, r, ql, qr, edge);
}

vector<int> answer;
vector<pair<int,int>> queries; // store queries at time t: either (-1, query_id) for ask

void dfs(int idx,int l,int r, RollbackDSU &dsu) {
    int snap = dsu.snapshot();
    for(auto &e: seg[idx]) dsu.unite(e.first,e.second);
    if(l==r) {
        if(queries[l].first==-1) {
            int id = queries[l].second;
            answer[id] = dsu.comps;
        }
    } else {
        int m=(l+r)>>1;
        dfs(idx<<1, l, m, dsu);
        dfs(idx<<1|1, m+1, r, dsu);
    }
    dsu.rollback(snap);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M_events, Q;
    // Input parsing omitted: build `seg` by mapping edge intervals, fill `queries` and `answer`
    // Then:
    RollbackDSU dsu(N);
    dfs(1,1,M_events, dsu);
    // print `answer`
    return 0;
}


// ====== 2. Nuts and Bolts of the Rollback Stack ======
// Standalone minimal Rollback DSU implementation with explicit stack operations.

struct RBDSU {
    vector<int> p, sz;
    vector<tuple<int,int,int>> stk;  // (b_root, a_root, old_sz)
    int comps;
    RBDSU(int n): p(n+1), sz(n+1,1), comps(n) {
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        while(p[x]!=x) x=p[x]; return x;
    }
    void unite(int x,int y) {
        int a=find(x), b=find(y);
        if(a==b) { stk.emplace_back(-1,-1,-1); return; }
        if(sz[a]<sz[b]) swap(a,b);
        stk.emplace_back(b, a, sz[a]);
        p[b]=a; sz[a]+=sz[b]; comps--;
    }
    int snapshot(){ return stk.size(); }
    void rollback(int snap) {
        while((int)stk.size()>snap) {
            auto [b, a, old_sz] = stk.back(); stk.pop_back();
            if(b==-1) continue;
            p[b]=b; sz[a]=old_sz; comps++;
        }
    }
};


// ====== 3. Sketch of a Fully Persistent DSU ======
// Uses node-copying: each version stores a root pointer to a persistent segment tree or
// treap that represents parent/size arrays.  Here is a conceptual outline.

// Pseudocode only—real implementation is lengthy.

struct Node {
    int val;
    Node *l,*r;
    Node(int v): val(v), l(nullptr), r(nullptr) {}
};

// Build initial tree of size N, all parent[i]=i or sz[i]=1
Node* build(int tl,int tr, bool isSize) {
    if(tl==tr) return new Node(isSize?1:tl);
    int tm=(tl+tr)/2;
    Node* root=new Node(0);
    root->l = build(tl,tm,isSize);
    root->r = build(tm+1,tr,isSize);
    return root;
}

// Point update: returns new root with position pos updated to new_val
Node* update(Node* v,int tl,int tr,int pos,int new_val){
    Node* nv = new Node(0);
    if(tl==tr) { nv->val=new_val; return nv; }
    int tm=(tl+tr)/2;
    if(pos<=tm) {
        nv->l = update(v->l, tl,tm,pos,new_val);
        nv->r = v->r;
    } else {
        nv->l = v->l;
        nv->r = update(v->r, tm+1,tr,pos,new_val);
    }
    return nv;
}

int query(Node* v,int tl,int tr,int pos){
    if(tl==tr) return v->val;
    int tm=(tl+tr)/2;
    if(pos<=tm) return query(v->l, tl,tm,pos);
    else return query(v->r, tm+1,tr,pos);
}

struct PersistentDSU {
    int N;
    vector<pair<Node*,Node*>> versions; // {parentRoot, sizeRoot}
    PersistentDSU(int n):N(n) {
        Node* p0 = build(1,N,false);
        Node* s0 = build(1,N,true);
        versions.emplace_back(p0,s0);
    }
    int find(int ver,int x){
        int px = query(versions[ver].first,1,N,x);
        if(px==x) return x;
        return find(ver, px);
    }
    int unite(int ver,int a,int b){
        int ra=find(ver,a), rb=find(ver,b);
        if(ra==rb) { versions.push_back(versions[ver]); return versions.size()-1; }
        auto [proot, sroot] = versions[ver];
        int sa = query(sroot,1,N,ra);
        int sb = query(sroot,1,N,rb);
        if(sa < sb) swap(ra,rb), swap(sa,sb);
        // update parent[rb]=ra and size[ra]+=sb
        Node* newP = update(proot,1,N,rb,ra);
        Node* newS = update(sroot,1,N,ra,sa+sb);
        versions.emplace_back(newP,newS);
        return versions.size()-1;
    }
};

// Usage:
// PersistentDSU dsu(N);
// int v1 = dsu.unite(0, u, v);   // creates version 1
// int v2 = dsu.unite(v1, x, y);  // creates version 2
// int root = dsu.find(v2, z);
