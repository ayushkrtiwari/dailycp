// https://judge.yosupo.jp/problem/convolution_mod

// Well I prefer this simple recursion method over bit reverse order manipulation
// First Implementation of NTT, so would add notes wherever I missed

#include <bits/stdc++.h>
using namespace std;
# define int long long
const int MOD = 998244353;
const int primitive_root = 3;

int modpow(int b, int e)
{
    if(e == 0) return 1;
    if(e % 2)
        return (1ll * b * modpow(b, e - 1)) % MOD;
    // return (modpow(modpow(b, e / 2), 2)) % MOD;  overflow issue
    int pwr = modpow(b, e >> 1);
    return (1ll * pwr * pwr) % MOD;
}

vector<int> NTT(vector<int> &a, int invert)
{
    int n = a.size();
    if(n == 1) return a;
    
    vector<int> a0, a1;
    for(int i = 0; i < n/2; i++)
    {
        a0.emplace_back(a[2 * i]);
        a1.emplace_back(a[2 * i + 1]);
    }
    vector<int> y0, y1;
    vector<int> y(n);
    y0 = NTT(a0, invert);
    y1 = NTT(a1, invert);
    int angle = (MOD - 1) / n;
    int wpow = (1ll * (invert ? modpow(primitive_root, MOD - 1 - angle): modpow(primitive_root, angle))) % MOD; 
    // notes regarding primitive root, generators and primes attached as NTT in resources
    int w = 1;
    for(int i = 0; i < n/2; i++)
    {
        y[i] = (y0[i] + w * y1[i]) % MOD;
        y[i + n/2] = (((y0[i] - w * y1[i]) % MOD) + MOD) % MOD;
        w = (1ll * w * wpow) % MOD;
    }
    return y;
}

int32_t main() {
	// your code goes here
    int n, m;
    cin>>n>>m;
    vector<int> a(n), b(m);
    for(auto &x: a) cin>>x;
    for(auto &y: b) cin>>y;
    int N = 1;
    while(N < n + m - 1) N <<= 1; // N >= n + m - 1
    a.resize(N), b.resize(N);
    // vector<int> c(n + m);
    auto d = NTT(a, false);
    auto e = NTT(b, false);
    auto multiply = [&]()
    {
        vector<int> c;
        int d_sz = d.size();
        for(int i = 0; i < d_sz; i++)
        c.emplace_back((1ll * d[i] * e[i]) % MOD);
        return c;
    };
    auto mres = multiply();
    auto f = NTT(mres, true);
    int ninv = modpow(N, MOD - 2); // do N inverse not n inverse
    for(auto &x: f) x = (x * 1ll * ninv) % MOD; // multiply ninv here instead of in NTT function
    f.resize(n + m - 1); // cut coefficients size to n + m - 1
    for(auto &x : f) cout<<x<<" ";
}