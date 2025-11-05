// https://codeforces.com/contest/1977/problem/C

#include<bits/stdc++.h>
using namespace std;
# define int long long int

int32_t main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        vector<int> a(n);
        for(auto&x:a)cin>>x;
        int M = *max_element(a.begin(), a.end());
        int l = 1;
        bool full = false;
        for(int i = 0; i < n; i++)
        {
            l = lcm(l, a[i]);
            if(l > M)
            {
                cout<<n<<"\n";
                full = true;
                break;
            }
        }
        if(!full)
        {
            int mxcnt = 0;
            vector<int> divisors;
            for(int i = 2; i * i <= M; i++)
            {
                if(M % i == 0)
                {
                    divisors.push_back(i);
                    if(i * i != M)
                    divisors.push_back(M / i);
                }
            }
            set<int> divset(a.begin(), a.end());
            for(auto &x: divisors)
            {
                if(divset.count(x)) continue;
                else
                {
                    int l = 1;
                    int cnt = 0;
                    for(int i = 0; i < n; i++)
                    if(x % a[i] == 0)
                    cnt++, l = lcm(l, a[i]);
                    if(l == x)
                    mxcnt = max(mxcnt, cnt);
                }
            }
            cout<<mxcnt<<"\n";
        }
    }
}