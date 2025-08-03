// जय श्री राम  JAI SHREE RAM

// https://www.hackerrank.com/contests/5-days-of-game-theory/challenges/final-tower-breakers/problem

// DP, Sprague-Grundy, Game Theory

// Nice Question, DP more than actual game-theory
// Refer to editorial

// Few tricks : optimal approach is to break into 2 parts: d and H - d for pile of H
// Now f(H) = min(max(d^2 + f(h(d))), max((H - d)^2 + f(h(H - d))))
// here h(x) is height at position x after breaking into several parts
// max is done over all values of d, min is done for minimum of both values recursively.
// max is done by P2, min is done by P1.
// d will be in the range [1, root(H)] where H represents the height of pile to be broken.
// root(H) is the upper limit since > root(H) means P2 gets instantly more than (root(H))^2 coins or H coins
// but at any case there is a way that P1 can arrange that P2 gets atmost H coins.

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