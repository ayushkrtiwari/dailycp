// https://codeforces.com/contest/221/problem/D

// _________________________METHOD 1: PREVIOUS, NEXT LOCATIONS______________________________

// Alternative: We can use pre and next array instead of coordinate compression

// Consider arrays pre[i] and nxt[i], which equal the last location of the element i
// and the next location of the element i,
// respectively (equal to some infinity if this element doesn't exist.) 
// We can use these arrays to quickly check whether or not some element occurs in an range.



#include<bits/stdc++.h>
using namespace std;

const int blocks = 7e2;

struct Query
{
    int x,y,idx;
    bool operator<(Query other) const
    {
        if(x/blocks != other.x/blocks) return x < other.x;
        return x/blocks & 1 ? y > other.y : y < other.y;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,m;
    cin>>n>>m;
    vector<int> a(n);
    for(auto &x: a) cin>>x;
    
    vector<int> comp = a;
    sort(comp.begin(),comp.end());
    comp.erase(unique(comp.begin(),comp.end()),comp.end());
    
    vector<int> a_idx(n);
    for(int i = 0; i < n; i++)
    a_idx[i] = lower_bound(comp.begin(),comp.end(),a[i]) - comp.begin();
    
    vector<Query> query(m);
    for(int i = 0; i < m; i++)
    {
        cin>>query[i].x>>query[i].y;
        query[i].x--, query[i].y--;
        query[i].idx = i;
    }
    
    // auto mo_cmp = [&] (const Query &qa, const Query &qb)
    // {
    //     if(qa.x/blocks != qb.x/blocks) return qa.x < qb.x;
    //     return qa.x/blocks & 1 ? qa.y > qb.y : qa.y < qb.y;
    // };
    
    int d = comp.size();
    vector<int> freq(d,0);
    int ans = 0;
    
    auto add = [&](int idx)
    {
        int v = comp[idx];
        if(freq[idx] == v)
        ans--;
        freq[idx]++;
        if(freq[idx] == v)
        ans++;
    };
    
    auto remov = [&](int idx)
    {
        int v = comp[idx];
        if(freq[idx] == v)
        ans--;
        freq[idx]--;
        if(freq[idx] == v)
        ans++;
    };
    
    sort(query.begin(),query.end());
    
    vector<int> res(m);
    
    int mo_left = 0, mo_right = -1;
    for(auto &q:query)
    {
        while(mo_left < q.x) remov(a_idx[mo_left++]);
        while(mo_left > q.x) add(a_idx[--mo_left]);
        while(mo_right < q.y) add(a_idx[++mo_right]);
        while(mo_right > q.y) remov(a_idx[mo_right--]);
        res[q.idx] = ans;
    }
    for(auto r: res)
    cout<<r<<"\n";
}