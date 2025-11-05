// https://www.codechef.com/problems/MINMODSUB

#include <bits/stdc++.h>
using namespace std;
# define int long long
# define MAXM 400005
# define MOD 998244353
vector<int> fact(MAXM + 1, 1), invfact(MAXM + 1, 1);

void dbug()
{
     cout<<".";
}

int binpow(int base, int p)
{
    int res = 1;
    while(p)
    {
        if(p & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        p /= 2;
    }
    return res;
}

void precompute()
{
    int f = 1;
    for(int i = 2; i <= MAXM; i++)
    f = (f * i) % MOD, fact[i] = f;
    f = binpow(f, MOD - 2);
    // cout<<"fact: "<<f<<" ";
    for(int i = MAXM; i > 0; i--)
    invfact[i] = f, f = (f * i) % MOD;
}

int c(int n, int r)
{
    return (int)((((long long)fact[n] * invfact[n - r]) % MOD) * invfact[r] % MOD);
}

int32_t main() {
	// your code goes here
	precompute();
// 	for(int i = 0; i < 10; i++)
// 	cout<<fact[i]<<" ";
// 	cout<<"\n";
// 	for(int i = 0; i < 10; i++)
// 	cout<<invfact[i]<<" ";
// 	cout<<"\n";
    int t;
    cin>>t;
    while(t--)
    {
        int m;
        cin>>m;
        // int ans = 0;
        for(int n = 1; n <= m; n++)
        {
            int sum = 0;
            // d = 0 case will give multiple same array elements, 
            // not unique elements, hence multiplying 
            // n! with sum wont give all array combinations
            // d = 0 case is automatically covered in rest of d or idk
            for(int d = 1; d <= m / (n + 1); d++)
            {
                // d = 0 not possible since 
                if((n + 1) * d > m) continue;
                sum = (sum + c(m - (n + 1) * d + n, n)) % MOD;
            }
            // ans += sum;
            cout<<(fact[n] * sum) % MOD<<" ";
        }
        cout<<"\n";
    }
}

// GPT explaination : 

1. Objects and notation (clear)

Fix M and N.

For an array A = (A1, A2, ..., AN) with 0 ≤ Ai < M, define prefix sums modulo M:

P0 = 0
P1 = A1
P2 = (A1 + A2) mod M
...
PN = (A1 + A2 + ... + AN) mod M

So we have exactly N+1 points {P0, P1, ..., PN} on the circle of length M.

Sort these N+1 points clockwise starting from P0. (Because P0 = 0, we have a distinguished starting point.) Let the consecutive clockwise gaps (distances) be g1, g2, ..., gN+1, where g1 + g2 + ... + gN+1 = M. Here g1 is the clockwise distance from P0 to the next point, g2 is the next gap, and so on.

Important: the ordered tuple (g1, ..., gN+1) is obtained by sorting the prefix-sum points clockwise starting at P0. That ordering is fixed once P0 is fixed.

---

2. The bijection that gives the factor N!

Claim: Fix any ordered gap-tuple (g1, ..., gN+1) with sum M and each gi ≥ d. The number of arrays A that produce exactly this ordered gap-tuple (when you compute prefix sums and then sort them starting from P0) is exactly N!.

**Why (constructive bijection):**

From the fixed ordered gaps we can uniquely reconstruct the set of positions of the prefix sums on the circle:

q0 = 0
q1 = q0 + g1
q2 = q1 + g2
...
qN = qN−1 + gN

and qN+1 = M wraps to q0. So the sorted positions are {q0, q1, ..., qN} (all taken modulo M).

Now ask: how many arrays A produce exactly these prefix-sum positions (not just as a set, but so that after you sort them starting at P0 you recover the same ordered tuple (g1, ..., gN+1))?

An array A is determined by the order in which the prefix sums appear in the original index order P0, P1, ..., PN. We already know the set of points {q0, ..., qN} and we know P0 = q0. The remaining N prefix sums P1, ..., PN must be some ordering (permutation) of the other N positions {q1, ..., qN}.

Choose any permutation π of {1, 2, ..., N}. Define:

P1 := qπ(1)
P2 := qπ(2)
...
PN := qπ(N)

Then define the array by forward differences (taken modulo M):

A1 = (P1 − P0) mod M
A2 = (P2 − P1) mod M
...
AN = (PN − PN−1) mod M

This produces an array A whose prefix sums (in the original order) are exactly P0, P1, ..., PN. When you sort these prefix sums clockwise starting at P0 you recover q0, ..., qN, hence the same gaps (g1, ..., gN+1).

Different permutations π give different sequences P1, ..., PN, hence different arrays A. Two different permutations cannot produce the same ordered list P1, ..., PN. Therefore there are exactly N! arrays producing this gap-tuple.

Conversely, every array A that yields these gap values corresponds to some permutation of the N positions {q1, ..., qN}: simply read the prefix sums P1, ..., PN and map them to the indices of q-positions; this mapping is a permutation. Therefore the correspondence between permutations π and arrays producing the given ordered gaps is one-to-one. So there are exactly N! such arrays.

Hence each ordered gap-tuple corresponds to exactly N! arrays. So if the number of ordered gap-tuples with the desired property is C = binom(M − (N+1)d + N, N), the number of arrays with the property is N! × C. This is the reason for the multiplicative factor fact[n] in the code.

---

3. Small explicit example (concrete numbers)

Take M = 6, N = 2. Suppose the ordered gaps are (g1, g2, g3) = (2, 3, 1). Then the sorted positions are:

q0 = 0, q1 = 2, q2 = 5.

The permutations of the two nonzero positions {q1, q2} are:

Permutation π = (1, 2) yields prefix sequence P0 = 0, P1 = 2, P2 = 5.
Then:
A1 = 2 − 0 = 2
A2 = 5 − 2 = 3
So A = (2, 3).

Permutation π = (2, 1) yields prefix sequence P0 = 0, P1 = 5, P2 = 2.
Then (mod 6):
A1 = 5 − 0 = 5
A2 = (2 − 5) mod 6 = 3
So A = (5, 3).

Both arrays produce the same ordered gaps (2, 3, 1) when you sort their prefix sums clockwise starting at 0; they are distinct arrays. There are 2! = 2 arrays arising from this gap-tuple — exactly N!.
