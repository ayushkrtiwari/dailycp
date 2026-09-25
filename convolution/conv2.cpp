// https://www.spoj.com/problems/MUL/en/

// bigint uses karatsuba multiplication and takes 0.05 ms while fft did in 0.06, difference also in chunks of 9 and 3
// NTT takes much larger time amount

// GPT:

#include <bits/stdc++.h>
using namespace std;

using cd = complex<double>;
const double PI = acos(-1);

// iterative in-place Cooley–Tukey FFT
void fft(vector<cd> & a, bool invert) {
    int n = a.size();
    // bit-reverse permutation
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j |= bit;
        if (i < j) swap(a[i], a[j]);
    }
    // layers
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : +1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len/2; j++) {
                cd u = a[i+j];
                cd v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert) {
        for (cd & x : a) x /= n;
    }
}

// multiply two big integers given as vectors of base-1000 digits
vector<long long> multiply_fft(const vector<int> &a, const vector<int> &b) {
    int n = 1;
    while (n < (int)a.size() + (int)b.size()) 
        n <<= 1;
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<long long> result(n);
    long long carry = 0;
    for (int i = 0; i < n; i++) {
        long long t = (long long)round(fa[i].real()) + carry;
        result[i] = t % 1000;
        carry = t / 1000;
    }
    // append remaining carry
    while (carry) {
        result.push_back(carry % 1000);
        carry /= 1000;
    }
    // trim leading zeros
    while (result.size() > 1 && result.back() == 0)
        result.pop_back();
    return result;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        string sa, sb;
        cin >> sa >> sb;
        // handle zero cases
        if (sa == "0" || sb == "0") {
            cout << "0\n";
            continue;
        }
        // pack into base-1000 little-endian
        vector<int> a, b;
        for (int i = (int)sa.size(); i > 0; i -= 3) {
            int x = 0;
            int start = max(0, i-3);
            for (int j = start; j < i; j++)
                x = x*10 + (sa[j]-'0');
            a.push_back(x);
        }
        for (int i = (int)sb.size(); i > 0; i -= 3) {
            int x = 0;
            int start = max(0, i-3);
            for (int j = start; j < i; j++)
                x = x*10 + (sb[j]-'0');
            b.push_back(x);
        }
        auto c = multiply_fft(a, b);
        // print most significant chunk without leading zeros
        int i = c.size()-1;
        cout << c[i];
        // print remaining chunks padded to 3 digits
        for (i = i-1; i >= 0; i--) {
            cout << setw(3) << setfill('0') << c[i];
        }
        cout << "\n";
    }
    return 0;
}
