// https://codeforces.com/contest/1974/problem/E

#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
	// your code goes here
    int t;
    cin>>t;
    while(t--)
    {
        int m;
        cin>>m;
        long long x;
        cin>>x;
        vector<long long> c(m),h(m);
        long long maxh = 0;
        for(int i=0;i<m;i++)
        {
            cin>>c[i]>>h[i];
            maxh += h[i];
        }
        vector<long long> dp(maxh+2,LLONG_MAX);
        dp[0] = 0;
        int curr = 0;
        for(int i=0;i<m;i++)
        {
            for(int j=curr;j>=0;j--)
            {
                if(dp[j]!=LLONG_MAX and dp[j] + c[i] <= i*x)
                dp[j+h[i]] = min(dp[j+h[i]],dp[j]+c[i]);
            }
            curr += h[i];
        }
        for(int i = maxh+1; i>=0 ;i--)
        if(dp[i]!=LLONG_MAX)
        {
            cout<<i<<"\n";
            break;
        }
    }
}
