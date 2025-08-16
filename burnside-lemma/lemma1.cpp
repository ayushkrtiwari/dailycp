// https://cses.fi/problemset/task/2210

#include<bits/stdc++.h>
using namespace std;
# define int long long
static constexpr int MOD = 1e9 + 7;

// int binpower(int base, int expt)
// {
//     if(expt == 0) return 1ll;
//     if(expt & 1) return (base * binpower(base, expt - 1)) % MOD;
//     // int sq = (base * base) % MOD;
//     int sq = binpower(base, expt/2);
//     return (sq * sq) % MOD;
// }

int binpower(int base, int expt)
{
    int res = 1;
    while(expt > 0)
    {
        if(expt & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        expt >>= 1;
    }
    return res;
}

int32_t main()
{
    int n;
    cin>>n;
    __int128 nsq = (n * n);
    __int128 nsqby2 = nsq / 2;
    __int128 nsqby4 = nsq / 4;
    int pow2n2 = binpower(2, nsq);
    int pow2n2by2 = (n & 1 ? binpower(2, (int)((nsqby2 + 1) % (MOD - 1))) : binpower(2, (int)(nsqby2 % (MOD - 1))));
    int pow2n2by4 = (n & 1 ? binpower(2, (int)((nsqby4 + 1) % (MOD - 1))) : binpower(2, (int)(nsqby4 % (MOD - 1))));
    int sum = (pow2n2 + pow2n2by2 + pow2n2by4 * 2) % MOD;
    int ans = (sum * binpower(4, MOD - 2)) % MOD;
    // cout<<binpower(2, 0)<<"\n";
    cout<<ans<<"\n";
}