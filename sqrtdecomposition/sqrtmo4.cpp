// https://codeforces.com/contest/2014/problem/H

// Topic: MO Range Query Algo, Coordinate Compression
// Simply accessing and updating the vector and clearing the freq(max_element(a)) after each test case gave TLE on TC 93
// Hence, coordinate compression

#include<bits/stdc++.h>
using namespace std;
# define int long long

const int blocks = 7e2; 
// this actually doesn't matter,particularly in this question, this got 514ms while other type got 515ms
// but its said that for most questions, this is better, since globally declared const variable gets its inverse value
// its much cheaper than all divisions done in other type, since compiler gets its inverse multiplication value in compile time only
// and since multiplication is much much cheaper than division, this reduces time complexity.

struct Query
{
    int x, y, idx;
};

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin>>t;
    while(t--)
    {
        int n,q;
        cin>>n>>q;
        // int blocks = max(1LL, (int)(sqrt(n + .0)) + 1);
        vector<int> a(n);
        for(auto &x:a)
        cin>>x;
        
        vector<int> comp = a;
        sort(comp.begin(), comp.end());
        comp.erase(unique(comp.begin(), comp.end()),comp.end());
        
        int d = comp.size();
        
        vector<int> a_idx(n);
        for(int i = 0; i < n; i++)
        a_idx[i] = lower_bound(comp.begin(), comp.end(), a[i]) - comp.begin();
        
        // int mx = *max_element(a.begin(), a.end());
        
        vector<Query> queries(q);
        for(int i = 0; i < q; i++)
        {
            cin>>queries[i].x>>queries[i].y;
            queries[i].x--, queries[i].y--;
            queries[i].idx = i;
        }
        
        auto mocmp = [&](Query &q1, Query &q2)
        {
            if(q1.x / blocks != q2.x / blocks) return q1.x < q2.x;
            return q1.x/blocks & 1 ? q1.y > q2.y : q1.y < q2.y;
        };
        
        sort(queries.begin(), queries.end(), mocmp);
        
        vector<int> freq(d, 0);
        int oddcnts = 0, evencnts = 0;
        int ans = 0;
        int mo_left = 0, mo_right = -1;
        
        vector<int> res(q);
        
        auto process = [&](int type, int index)
        {
            if(freq[index] % 2)
            oddcnts -= 1;
            else
            oddcnts += 1;
            if(oddcnts) ans = 1;
            else ans = 0;
            freq[index] += type;
        };
        
        for(auto &qry: queries)
        {
            while(mo_left < qry.x) process(-1, a_idx[mo_left++]);
            while(mo_right < qry.y) process(1, a_idx[++mo_right]);
            while(mo_left > qry.x) process(1, a_idx[--mo_left]);
            while(mo_right > qry.y) process(-1, a_idx[mo_right--]);
            res[qry.idx] = ans;
        }
        for(auto &r:res)
        if(r) cout<<"NO\n";
        else cout<<"YES\n";
    }
}