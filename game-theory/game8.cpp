// https://www.hackerrank.com/contests/5-days-of-game-theory/challenges/tower-breakers-2/problem

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
# define MAXN 1e6 + 3
vector<int> spf(MAXN);

void spff()
{
    spf[0] = 1, spf[1] = 0;
    for(int i = 2; i < MAXN; i++)
        spf[i] = i;
    for(int i = 2; i < MAXN; i++)
    {
        if(spf[i] == i)
        {
            for(int j = 2 * i; j < MAXN; j += i)
            {
                if(spf[j] == j)
                    spf[j] = i; 
            }
        }
    }
}

bool isprime(int x)
{
    if(x == spf[x]) return true;
    return false;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    spff();
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        vector<int> h(n);
        for(auto &x: h) cin>>x;
        for(auto &x : h)
        {
            if(x == 1) x = 0;
            else if(isprime(x)) x = 1;
            else x = 2;
        }
        int nim = 0;
        for(auto &x:h) nim ^= x;
        if(nim) cout<<"1\n";
        else cout<<"2\n";
    }
    return 0;
}


// _________________________________________________________________________________

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
// # define MAXN 1e6 + 3
static constexpr int MAXN = 100'00'03;
vector<int> spf(MAXN);

void spff()
{
    spf[0] = 1, spf[1] = 0;
    for(int i = 2; i < MAXN; i++)
        spf[i] = i;
    for(int i = 2; i < MAXN; i++)
    {
        if(spf[i] == i)
        {
            for(int j = 2 * i; j < MAXN; j += i)
            {
                if(spf[j] == j)
                    spf[j] = i; 
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    spff();
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        vector<int> h(n);
        for(auto &x: h) cin>>x;
        vector<int> cnt(n, 0);
        for(int i = 0; i < n; i++)
        {
            int x = h[i];
            while(x != 1)
            {
                cnt[i]++;
                x /= spf[x];
            }
        }
        int nim = 0;
        for(auto c : cnt)
            nim ^= c;
        if(nim) cout<<"1\n";
        else cout<<"2\n";
    }
    return 0;
}

// ____________________________________________________________________________________________________________________

// GPT gave grundy template for this, and then we need to perform nim sum after finding grundy of each height term.

unordered_map<int,int> G;

int grundy(int h) {
    if (h == 1) return 0;
    if (auto it = G.find(h); it != G.end())
    return it->second;
    unordered_set<int> s;
    for (int d = 1; d*d <= h; ++d) {
    if (h % d == 0) {
        if (d < h)      s.insert(grundy(d));
        if (h/d < h)    s.insert(grundy(h/d));
    }
    }
    int g = 0;
    while (s.count(g)) ++g;
    return G[h] = g;
}

// C++17 or above special “if with initializer” syntax. 
// You can both declare/initialize a variable and test it in the same if statement:

// if ( auto it = G.find(h);  // initializer: declare `it` and call `G.find(h)`
//      it != G.end()         // condition: only enter the body if `it` is valid
//    )
// {
//     // here `it` is in scope and guaranteed != G.end()
//     return it->second;
// }