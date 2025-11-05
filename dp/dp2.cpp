// https://codeforces.com/contest/1987/problem/D

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")

#include<bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        vector<int> a(n);
        for(auto&x:a)
        cin>>x;
        vector<int> cnt(5005, 0);
        for(auto &x:a)
        cnt[x]++;
        vector<int> freq;
        for(auto&x:cnt)
        if(x>0)freq.push_back(x);
        n = freq.size();
        vector<int> dp(n + 1, 1e9);
        dp[0] = 0;
        for(int i = 1; i <= n; i++)
        {
            vector<int> newdp = dp;
            for(int j = 1; j <= n; j++)
            {
                int x = dp[j - 1] + freq[i - 1];
                newdp[j] = (x <= i - j) ? min(newdp[j], x) : newdp[j] ;
            }
            dp = newdp;
        }
        
        int cakebyalice = 0;
        int i = n;
        while(dp[i] >= 1e9) 
        cakebyalice = max(cakebyalice, n - --i);
        cout<<cakebyalice<<"\n";
    }
}