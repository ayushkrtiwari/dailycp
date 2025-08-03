// https://www.hackerrank.com/contests/5-days-of-game-theory/challenges/final-tower-breakers/problem

#include<bits/stdc++.h>
using namespace std;
# define int long long
static constexpr int inf = 1e18;
int32_t main()
{
    int t;
    cin>>t;
    vector<int> tc(t);
    int mx = 0;
    for(auto &x : tc)
    {
        cin>>x;
        mx = max(mx, x);
    }
// length of dp should be till the ans for all tc are found
    vector<int> dp;
    dp.emplace_back(1);
    for(int i = 1; ; i++)
    {
        int rooti = sqrt(i);
        int sum = 0;
        for(int j = 1; j <= rooti; j++)
        {
            sum += dp[i - j * j];
            if(sum >= mx)
            {
                sum = mx;
                break;
            }
        }
        dp.emplace_back(sum);
        if(sum >= mx) break;
    }
    for(auto &x : tc)
    {
        auto ans = lower_bound(dp.begin(), dp.end(), x) - dp.begin();
        cout<<ans<<"\n";
    }
    return 0;
}