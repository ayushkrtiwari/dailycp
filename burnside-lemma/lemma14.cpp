// https://codeforces.com/gym/101873/attachments/download/7413/20172018-acmicpc-german-collegiate-programming-contest-gcpc-2017-en.pdf
// https://basecamp.eolymp.com/en/problems/11615

// Solution : 
// c ^ (gcd(i, m) * (n * n))    for all i from 0 to m - 1
// store this sum for all values of i in a variable and divide it by m
// This is the final solution. 

#include <bits/stdc++.h>
using namespace std;
static constexpr int MOD = 1e9 + 7;
# define int long long

int binexp(int b, int e)
{
    int res = 1;
    while(e > 0)
    {
        if(e & 1) res = (res * b) % MOD;
        b = (b * b) % MOD;
        e >>= 1;
    }
    return res;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, c;
    cin>>n>>m>>c;
    int sum = 0;
    for(int i = 0; i < m; i++)
    {
        int g = (__gcd(i, m) * n * n) % MOD;
        int binpow = binexp(c, g);
        sum = (sum + binpow) % MOD;
    }
    sum = (sum * binexp(m, MOD - 2)) % MOD;
    cout<<sum;
}
