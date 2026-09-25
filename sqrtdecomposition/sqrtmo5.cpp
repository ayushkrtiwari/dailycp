// https://codeforces.com/problemset/problem/617/E

#include<bits/stdc++.h>
using namespace std;
# define int long long

const int blocks = 7e2;
// using this reduced time from 2250ms to 2000ms
// definitely use global const for less time

// Using this hash function, solution wont be hacked
// but it increased time from 2000ms to 3000ms

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) 
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const 
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

struct Query
{
    int x, y, idx;
};

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t = 1;
    // cin>>t;
    while(t--)
    {
        int n,q,k;
        cin>>n>>q>>k;
        // int blocks = max(1LL, (int)(sqrt(n + .0)) + 1);
        vector<int> a(n);
        for(auto &x:a)
        cin>>x;
        
        unordered_map<int, int, custom_hash> mxor;

        mxor[0] = 1;
        // int xrr = 0;
        // int cntprefix = 0;
        vector<int> xorprefix(n + 1, 0);
        xorprefix[0] = 0;
        for(int i = 1; i <= n; i++)
        {
            xorprefix[i] = xorprefix[i - 1] ^ a[i - 1];
        }
        
        vector<Query> queries(q);
        for(int i = 0; i < q; i++)
        {
            cin>>queries[i].x>>queries[i].y;
            queries[i].x--;
            queries[i].idx = i;
        }
        
        auto mocmp = [&](Query &q1, Query &q2)
        {
            if(q1.x / blocks != q2.x / blocks) return q1.x < q2.x;
            return q1.x/blocks & 1 ? q1.y > q2.y : q1.y < q2.y;
        };
        
        sort(queries.begin(), queries.end(), mocmp);
        
        // int ans = 0;
        int mo_left = 0, mo_right = 0;
        // since we are to traverse on array 1 to n instead of 0 to n - 1
        // since we have 0 in map so mo_left = 0 wont bother
        
        int xorr = 0;
        // map<int,int> m;
        // m[0] = 0;
        int cnt = 0;
        vector<int> res(q);
        
        auto add = [&](int index)
        {
            int searchfor = xorprefix[index] ^ k;
            cnt += mxor[searchfor];  //
            mxor[xorprefix[index]]++;  //
            // if you reverse these then it wont affect much than one case:
            // if k == 0, this means your count will wrongly increase since 
            // you are taking l = x + 1 and r = x means not taking any element
            // that is your chosen subarray is empty and you get 0 so you will
            // count all 0 in the map. Thus extra contribution in answer.
        };
        
        auto rmove = [&](int index)
        {
            int searchfor = xorprefix[index] ^ k;
            mxor[xorprefix[index]]--; // when k == 0, then as we did not take
            // empty subarray, in the same way we subtract its own count since
            // it would decrement 1 extra
            cnt -= mxor[searchfor];
        };
        
        for(auto &qry: queries)
        {
            while(mo_left < qry.x) rmove(mo_left++);
            while(mo_right < qry.y) add(++mo_right);
            while(mo_left > qry.x) add(--mo_left);
            while(mo_right > qry.y) rmove(mo_right--);
            res[qry.idx] = cnt;
        }
        for(auto &r:res)
        cout<<r<<"\n";
    }
}