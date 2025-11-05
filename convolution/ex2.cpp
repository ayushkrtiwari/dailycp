// Example 2: Number Theoretic Transform (NTT) for Modulo
// Sometimes you need convolution mod a prime (e.g. 10^9+7). 
// You can implement an NTT using a suitable root of unity modulo prime. 
// Here's a sketch (details like modpow, inv, etc. omitted for brevity):


// Tips & Pitfalls:

// Precision: FFT with double can introduce rounding errors for large coefficients. Use NTT in contests when exact modulo is required.

// Padding: Always pad to the next power of two ≥ n + m

// Bit reversal: Be careful in your implementation to get the in place reordering correct.

// Performance tuning: Precompute roots, do iterative loops carefully (avoid recursion), 
// and consider using long double if you need a bit more precision.

// With these building blocks you can tackle any convolution-based problem in O(NlogN) instead of O(N^2). Good luck!


// (Sketch—fill in modpow, modular inverse, bit‐reversal, etc.)
const int MOD = 998244353, G = 3;  // G is primitive root

void ntt(vector<int>& a, bool invert) {
    int n = a.size();
    // bit‐reverse shuffle...
    for (int len = 2; len <= n; len <<= 1) {
        int wlen = modpow(G, (MOD-1)/len, MOD);
        if (invert) wlen = modinv(wlen, MOD);
        for (int i = 0; i < n; i += len) {
            int w = 1;
            for (int j = 0; j < len/2; j++) {
                int u = a[i+j], v = (int)((1LL * a[i+j+len/2] * w) % MOD);
                a[i+j] = u+v < MOD ? u+v : u+v-MOD;
                a[i+j+len/2] = u-v >= 0 ? u-v : u-v+MOD;
                w = (int)((1LL * w * wlen) % MOD);
            }
        }
    }
    if (invert) {
        int inv_n = modinv(n, MOD);
        for (int & x : a) x = (int)((1LL * x * inv_n) % MOD);
    }
}

vector<int> multiply_mod(const vector<int>& A, const vector<int>& B) {
    int n = 1;
    while (n < (int)A.size() + (int)B.size()) 
        n <<= 1;
    vector<int> fa(A.begin(), A.end()), fb(B.begin(), B.end());
    fa.resize(n); fb.resize(n);

    ntt(fa, false);
    ntt(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] = (int)((1LL * fa[i] * fb[i]) % MOD);
    ntt(fa, true);

    return fa;  // length n, with each coefficient mod MOD
}
