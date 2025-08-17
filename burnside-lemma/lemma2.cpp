// https://cses.fi/problemset/task/2209

// Jumping from a certain point for every number covers bead at specific positions, collectively called groups
// No of groups = gcd(jump, necklace_size)
// This comes from simple equation : x + A * jump - B * necklace_size, x is starting position

#include<bits/stdc++.h>
using namespace std;
# define int long long
static constexpr int MOD = 1e9 + 7;

int binpower(int base, int e)
{
    int res = 1;
    while(e > 0)
    {
        if(e & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        e >>= 1;
    }
    return res;
}

int32_t main()
{
    int n, m;
    cin>>n>>m;
    int sum = 0;
    int cnt = 0;
    int gcd;
    for(int i = 0; i < n; i++)
    {
        gcd = __gcd(i, n);
        cnt = (cnt + gcd) % MOD;
        sum = (sum + binpower(m, gcd)) % MOD;
    }
    sum = (sum * binpower(n, MOD - 2)) % MOD;
    cout<<sum<<"\n";
}