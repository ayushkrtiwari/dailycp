// https://www.spoj.com/problems/HORRIBLE/

#include <bits/stdc++.h>
using namespace std;
# define int long long

struct segT
{
    vector<int> a, segTree, lazy;
    int n;
    segT(int _n = 0) : n(_n)
    {
        a.resize(n);
        lazy.assign(4 * n + 5, 0);
        segTree.assign(4 * n + 5, 0);
    }
    void build(int ind, int low, int high)
    {
        if(low == high) 
        {
            segTree[ind] = a[low];
            return;
        }
        int mid = low + (high - low) / 2;
        build(2 * ind + 1, low, mid);
        build(2 * ind + 2, mid + 1, high);
        segTree[ind] = segTree[2 * ind + 1] + segTree[2 * ind + 2];
    }
    int query(int node, int low, int high, int ql, int qr)
    {
        if(lazy[node] != 0)
        {
            segTree[node] += (high - low + 1) * lazy[node];
            if(low != high)
            {
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 2] += lazy[node];
            }
            lazy[node] = 0;
        }
        if(low > qr or high < ql) return 0;
        // if(low >= ql and high <= qr) return segTree[node] + lazy[node] * (high - low + 1);
        // lazy[node] is already 0
        if(low >= ql and high <= qr) return segTree[node];
        int mid = low + (high - low) / 2;
        int left = query(2 * node + 1, low, mid, ql, qr);
        int right = query(2 * node + 2, mid + 1, high, ql, qr);
        // return segTree[node] = left + right;
        // return segTree[node];
        return left + right;
    }
    void pointUpdate(int node, int low, int high, int l, int r, int val)
    {
        if(low > r or high < l) return;
        if(low == high)
        {
            segTree[node] += val;
            return;
        }
        int mid = low + (high - low) / 2;
        pointUpdate(2 * node + 1, low, mid, l, r, val);
        pointUpdate(2 * node + 2, mid + 1, high, l, r, val);
        segTree[node] = segTree[2 * node + 1] + segTree[2 * node + 2];
    }
    void rangeUpdate(int node, int low, int high, int l, int r, int val)
    {
        if(lazy[node] != 0)
        {
            segTree[node] += (high - low + 1) * lazy[node];
            if(low != high)
            {
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 2] += lazy[node];
            }
            lazy[node] = 0;
        }
        if(low >= l and high <= r)
        {
            // lazy[node] +=  val;
            // return;
            // segTree[node] += (high - low + 1) * (lazy[node] + val);
            segTree[node] += (high - low + 1) * val;
            if(low != high)
            {
                // lazy[2 * node + 1] += lazy[node];
                // lazy[2 * node + 2] += lazy[node]
                lazy[2 * node + 1] += val;
                lazy[2 * node + 2] += val;
            }
            return;
        }
        if(low > r or high < l) return;
        int mid = low + (high - low) / 2;
        rangeUpdate(2 * node + 1, low, mid, l, r, val);
        rangeUpdate(2 * node + 2, mid + 1, high, l, r, val);
        segTree[node] = segTree[2 * node + 1] + segTree[2 * node + 2];
    }
    void rangeUpdate(int l, int r, int val)
    {
        // rangeUpdate(0, 0, 4 * n - 1, l, r, val);
        // node expands till 4 * n - 1, not low, high, l, r.. these are array,segtree,lazy indices
        rangeUpdate(0, 0, n - 1, l, r, val);
    }
    int query(int l, int r)
    {
        // return query(0, 0, 4 * n - 1, l, r);
        return query(0, 0, n - 1, l, r);
    }
};

int32_t main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        segT s(n);
        // for(auto &x : s.a) cin>>x;
        // build(0, 0, n - 1);
        int c;
        cin>>c;
        while(c--)
        {
            int type;
            cin>>type;
            if(!type)
            {
                int p, q, val;
                cin>>p>>q>>val;
                p--, q--;
                s.rangeUpdate(p, q, val);
            }
            else
            {
                int p, q;
                cin>>p>>q;
                p--, q--;
                cout<<s.query(p, q)<<"\n";
                // cout<<"\n";
            }
        }
    }
}