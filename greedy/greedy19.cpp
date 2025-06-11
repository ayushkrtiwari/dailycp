// https://maang.in/problems/Diversify-the-Array-97?returnUrl=%5B%22%2Fplaylists%2FSummer-Camp-S2-Week-3-Greedy-4868%3FresourceUrl%3Dcs181-cp795-pl4868-rs11623%26returnUrl%3D%255B%2522%252Fcourses%252FICPSC-S2-181%253Ftab%253Dchapters%2522%255D%22%5D

// Trick: Decrease count of largest repeating element first

#include<bits/stdc++.h>
# define int long long
using namespace std;
int32_t main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,k;
        cin>>n>>k;
        vector<int> a(n);
        for(auto &x:a) cin>>x;
        sort(a.begin(),a.end());
        priority_queue<pair<int,int>> pq;
        map<int,int> mp;
        for(int i = 0; i < n; i++)
        mp[a[i]]++;
        for(auto [key,cnt]:mp)
        pq.push({cnt,key});
        // long long cnt = 0;
        while(!pq.empty())
        {
            auto p = pq.top();
            if(k > 0 and p.first > 1)
            {
                p.first--;
                k--;
                mp[p.second] = p.first;
                pq.push({mp[p.second], p.second});
            }
            pq.pop();
        }
        long long totalpairs = n*(n-1)/2;
        long long badcount = 0;
        for(auto [key,value]:mp)
        badcount += 1ll * (value * (value - 1)/2);
        cout<<totalpairs - badcount<<"\n";
    }
}