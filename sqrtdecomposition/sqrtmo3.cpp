// https://codeforces.com/contest/86/problem/D

// MO's Algo

#include<bits/stdc++.h>
using namespace std;
# define int long long

const int blocks = 700;

struct Query
{
    int x,y,idx;
};

auto mo_cmp = [] (const Query &q1, const Query &q2)
{
    if(q1.x/blocks == q2.x/blocks)
    return q1.x/blocks & 1 ? q1.y < q2.y : q1.y > q2.y;
    return q1.x < q2.x;
};

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,t;
    cin>>n>>t;
    vector<int> a(n);
    for(auto &x:a) cin>>x;
    vector<Query> query(t);
    for(int i = 0; i < t; i++)
    {
        cin>>query[i].x>>query[i].y;
        query[i].x--, query[i].y--;
        query[i].idx = i;
    }
    sort(query.begin(),query.end(),mo_cmp);
    int mo_left = 0, mo_right = -1;
    vector<int> cnt(1000005,0);
    vector<int> ans(t,0);
    
    int curr = 0;
    
    auto add = [&](int v)
    {
        int &prev = cnt[v];
        curr += (2*prev++ + 1) * v;
    };
    // the formula comes from equating the equation further
    auto remov = [&](int v)
    {
        int &prev = cnt[v];
        curr -= (2*prev-- - 1) * v;
    };
    
    for(auto &q: query)
    {
        while(mo_left < q.x) remov(a[mo_left++]);
        while(mo_left > q.x) add(a[--mo_left]);
        while(mo_right < q.y) add(a[++mo_right]);
        while(mo_right > q.y) remov(a[mo_right--]);
        ans[q.idx] = curr;
    }
    for(auto r: ans)
    cout<<r<<"\n";
}