// Example 1: Counting Pair Sums with FFT
// Suppose you have an array A of size n with values in [0,M]. 
// You want, for each s, the number of ordered pairs (i,j) such that A[i]+A[j]=s.

#include <bits/stdc++.h>
using namespace std;
using cd = complex<double>;
const double PI = acos(-1);

// FFT, IFFT/Interpolation implementation (in-place, iterative)
void fft(vector<cd> & a, bool invert) { // invert = 1 for FFT, invert = -1 for Interpolation
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j |= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len/2; j++) {
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u+v;
                a[i+j+len/2] = u-v;
                w *= wlen;
            }
        }
    }
    if (invert) {
        for (cd & x : a)
            x /= n;
    }
}

// Multiply two real polynomials (integer coefficients)
vector<long long> multiply(const vector<int>& A, const vector<int>& B) {
    int n = 1;
    while (n < (int)A.size() + (int)B.size()) 
        n <<= 1;
    vector<cd> fa(A.begin(), A.end()), fb(B.begin(), B.end());
    fa.resize(n); fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<long long> result(n);
    for (int i = 0; i < n; i++)
        result[i] = (long long)round(fa[i].real());
    return result;
}

int main(){
    int n;              // number of elements
    cin >> n;
    vector<int> A(n);
    for (int &x : A) cin >> x;
    // Count frequency of each value
    int M = *max_element(A.begin(), A.end());
    vector<int> freq(M+1);
    for (int x : A) freq[x]++;

    // Convolve freq with itself to get pair-sums count
    vector<long long> ways = multiply(freq, freq);

    // ways[s] is the number of ordered pairs (i,j) with A[i]+A[j] = s
    for (int s = 0; s < (int)ways.size(); s++){
        if (ways[s]) {
            cout << "Sum " << s << ": " << ways[s] << " ways\n";
        }
    }
    return 0;
}
