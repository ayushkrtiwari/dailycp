// https://codeforces.com/contest/2154/problem/C1

#include <bits/stdc++.h>
using namespace std;
# define int long long
const int MAXN = 200005;
vector<int> spf(MAXN);

void spff() 
{
    spf.assign(MAXN + 1, 0);
    spf[0] = 0, spf[1] = 1;
    // if (MAXN >= 1) 
    // spf[1] = 1;
    for (int i = 2; i <= MAXN; ++i) {
        if (spf[i] == 0) 
        {
            for (int j = i; j <= MAXN; j += i) 
            {
                if (spf[j] == 0) 
                spf[j] = i;
            }
        }
    }
}

bool prime(int x)
{
    if(x == spf[x])
    return true;
    return false;
}

int32_t main() {
	int t;
	cin>>t;
	spff();
	while(t--)
	{
	    int n;
	    cin>>n;
	    vector<int> a(n), b(n);
	    for(auto &x : a) cin>>x;
	    for(auto &x : b) cin>>x;
	    unordered_map<int, int> ump;
	    int cnt2 = 0;
	    bool is1poss = false, is0poss = false;
	    auto canbedivided = [&](int x) -> bool
	    {
	        for(auto &s : ump)
	        if(x % s.first == 0) return true;
	        return false;
	    };
	    for(auto &x : a) 
	    {
	        if(x % 2 == 0)cnt2++;
	        if(canbedivided(x)) is0poss = true;
	        if(canbedivided(x + 1)) is1poss = true;
	        while(x != 1)
	        {
	            ump[spf[x]]++;
	            x /= spf[x];
	        }
	    }
	    if(is0poss or cnt2 >= 2) 
	    cout<<0<<"\n";
	    else if(cnt2 == 1 or is1poss)
	    cout<<1<<"\n";
	    else if(cnt2 == 0)
	    cout<<2<<"\n";
	   // else cout<<"hello\n";
	   // else if(cnt2 == 1) cout<<1<<"\n";
	   // else cout<<0<<"\n";
	}
}

// above failing test input : 
// 1
// 2
// 43 11
// 1 1

// ____________________________________________________________________________________________

#include <bits/stdc++.h>
using namespace std;
# define int long long
const int MAXN = 200005;
vector<int> spf(MAXN);

void spff() 
{
    spf.assign(MAXN + 1, 0);
    spf[0] = 0, spf[1] = 1;
    // if (MAXN >= 1) 
    // spf[1] = 1;
    for (int i = 2; i <= MAXN; ++i) {
        if (spf[i] == 0) 
        {
            for (int j = i; j <= MAXN; j += i) 
            {
                if (spf[j] == 0) 
                spf[j] = i;
            }
        }
    }
}

bool prime(int x)
{
    if(x == spf[x])
    return true;
    return false;
}

int32_t main() {
	int t;
	cin>>t;
	spff();
	while(t--)
	{
	    int n;
	    cin>>n;
	    vector<int> a(n), b(n);
	    for(auto &x : a) cin>>x;
	    for(auto &x : b) cin>>x;
	    unordered_map<int, int> ump;
	   // int cnt2 = 0;
	    bool is1poss = false, is0poss = false;
	   // auto canbedivided = [&](int x) -> bool
	   // {
	   //     for(auto &s : ump)
	   //     if(x % s.first == 0) return true;
	   //     return false;
	   // };
	    for(auto &xorg : a) 
	    {
	       // if(x % 2 == 0)cnt2++;
	       // if(canbedivided(x)) is0poss = true;
	       // if(canbedivided(x + 1)) is1poss = true;
	        int x = xorg;
	        while(x != 1)
	        {
	            int f = spf[x];
	            ump[f]++;
	            while(x % f == 0)
	            x /= f;
	        }
	    }
	    for(auto &x : ump) if(x.second > 1) is0poss = true;
	    for(auto &x : a)
	    {
	        // for all x + 1 check if their factors are already there in ump
			// we dont make separately many new ump for checking x + 1 each
			// of which excludes prime factors of x, since any prime factor
			// > 1 dividing x wont divide x + 1, btw i understood it later, 
			// here i used this concept without thinking this just by intuition
			// just dont ask anything about it
	        int nmb = x + 1;
	        while(nmb != 1)
	        {
	            if(ump[spf[nmb]] == 1)
	            is1poss = true;
	            nmb /= spf[nmb];
	        }
	    }
	    if(is0poss /* or cnt2 >= 2*/) 
	    cout<<0<<"\n";
	    else if(/*cnt2 == 1 or*/ is1poss)
	    cout<<1<<"\n";
	    else /*if(cnt2 == 0)*/
	    cout<<2<<"\n";
	   // else cout<<"hello\n";
	   // else if(cnt2 == 1) cout<<1<<"\n";
	   // else cout<<0<<"\n";
	}
}