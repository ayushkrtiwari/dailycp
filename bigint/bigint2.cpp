// https://codeforces.com/contest/17/problem/D

// Very Buzzy Question, Try till it gets accepted
// For using __int128 or __int128_t library, use G++20 or above compiler version
// Also do refer editorial for getting hint on this solution process


#include<bits/stdc++.h>
using namespace std;
using i128 = __int128_t;
using i64 = long long;
// i128 also works but is used for intermediate steps, thus use i64 with variables

i128 power10(i128 base, int mod) // keep it i64 or i128, but prioritize i128 for intermediate values only
{
    i64 x2 = (i128)base * base % mod;
    i64 x4 = (i128)x2 * x2 % mod;
    i64 x8 = (i128)x4 * x4 % mod;
    i64 res = (i128)x8 * x2 % mod;
    return res;
}

i64 power(i64 base, int exponent, int mod)
{
    i64 res = 1;
    while(exponent--)
    res = (i128)res * base % mod;
    return res;
}

int main()
{
    string a, b;
    i64 c;
    cin>>a>>b>>c;
    // ((a - 1) * (a ^ (b - 1))) % c
    int asize = a.size();
    i64 am = 0;
    for(int i = 0; i < asize; i++)
    am = (am * 10 + (a[i] - '0')) % c;
    
    // size_t i = b.size() - 1; 
    // size_t can't be negative but we need i to be reachable to the negative part too for breaking condition, hence int
    int i = b.size() - 1;
    while(i >= 0 and b[i] == '0')
    {
        b[i] = '9';
        i--;
    }
    if(i >= 0)
    {
        b[i] = b[i] - 1;
        if(i == 0 and b[i] == '0' and b.size() > 1)
        b.erase(0, 1);
    }
    // Now do for every digit Bi, A ^ ((10^i)*Bi)
    size_t bsz = b.size();
    i64 res = 1;
    int a10power = am;
    for(int i = bsz - 1; i >= 0; i--)
    {
        // cout<<b[i] - '0' <<"\n";
        res = (i128)res * power(a10power, (int)(b[i] - '0'), c) % c;
        a10power = power10(a10power, c);
        // cout<<res;
    }
    res = (i128)res * (am - 1 + c) % c;
    // cout<<am - 1<<"\n";
    if(res) cout<<res;
    else cout<<c;
}

// _____________________________________________________________

// GPT:

#include <bits/stdc++.h>
using namespace std;
using int64 = long long;
using i128  = __int128_t;

int64 modPowSmall(int64 base, int small_exp, int64 C) {
    int64 res = 1;
    while (small_exp--) {
        res = (i128)res * base % C;
    }
    return res;
}

int64 tenthPower(int64 x, int64 C) {
    int64 x2 = (i128)x * x % C;     
    int64 x4 = (i128)x2 * x2 % C;   
    int64 x8 = (i128)x4 * x4 % C;   
    return (i128)x8 * x2 % C;       
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string A, B;
    int64 C;
    cin >> A >> B >> C;

    int64 a_mod = 0;
    for (char d : A) {
        a_mod = ((i128)a_mod * 10 + (d - '0')) % C;
    }

    int64 u   = a_mod; 
    int64 ans = 1;      
    string Bm = B;
    int j = B.size() - 1;
    while(j >= 0 and Bm[j] == '0')
    {
        Bm[j] = '9';
        j--;
    }
    if(j >= 0)
    {
        Bm[j] -= 1;
        if(j == 0 and Bm[j] == '0' and Bm.size() > 1)
        Bm.erase(0, 1);
    }
    for (int i = (int)Bm.size() - 1; i >= 0; --i) {
        int digit = Bm[i] - '0';
        if (digit) {
            ans = (i128)ans * modPowSmall(u, digit, C) % C;
        }
        u = tenthPower(u, C);
    }

    int64 term   = (a_mod - 1 + C) % C;
    int64 result = (i128)ans * term % C;

    cout << (result == 0 ? C : result) << "\n";
    return 0;
}
