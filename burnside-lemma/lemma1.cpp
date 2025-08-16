// जय श्री राम  JAI SHREE RAM

// https://cses.fi/problemset/task/2210

// Burnside Lemma, Binary Exponentiation, Fermat Theorem, int128, Modular Arithmetic

// For concept of this problem, refer Resources

// Solution: 1 axis of rotation, symmetry rotation angles : 0, 90, 180, 270
// Evaluating each case for this problem of square : 
// angle 0 : n^2 groups
// angle 90, 270 : (n & 1) ? ceil((n^2) / 4) : (n^2)/4 groups
// angle 180 : (n & 1) ? ceil((n^2) / 2) : (n^2)/2 groups
// The result is summation of no of groups for all angles and divide it by no of symmetric angles (4)

// Lets say you want to do 2^x % MOD, but x is large, means you will also do (2^(x % MOD)) % MOD 
// But this is wrong, since the exponent should be modulo by (MOD - 1) not MOD
// Hence, the right power is (2^(x % (MOD - 1))) % MOD ; in this problem x = n^2, (n^2)/2, (n^2)/4

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
    // not done modulo here since I want the value of (n^2)/4 but 
    // if I do modulo and then /4 then I would get wrong value since both are not equivalent
    // hence int128 has been used for the purpose of not distorting real value of n^2
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