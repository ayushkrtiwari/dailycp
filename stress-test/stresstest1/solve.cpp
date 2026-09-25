#include<bits/stdc++.h>
using namespace std;
# define int long long int

int32_t main()
{
    int t = 1;
    // cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        vector<int> a(n);
        for(auto&x:a)cin>>x;
        int M = *max_element(a.begin(), a.end());
        int lcm = 1;
        for(int i = 0; i < n; i++)
        lcm = (lcm * a[i]) / __gcd(lcm, a[i]);
        if(M != lcm)
        cout<<n<<"\n";
        else
        {
            int mxcnt = 0;
            vector<int> divisors;
            for(int i = 1; i * i <= M; i++)
            {
                if(M % i == 0)
                {
                    divisors.push_back(i);
                    if(i * i != M)
                    divisors.push_back(M / i);
                }
            }
            for(auto &x: divisors)
            {
                if(find(a.begin(), a.end(), x) == a.end())
                {
                    int lcm = 1;
                    int cnt = 0;
                    for(int i = 0; i < n; i++)
                    if(x % a[i] == 0)
                    cnt++, lcm = (lcm / __gcd(lcm, a[i])) * a[i];
                    if(lcm == x)
                    mxcnt = max(mxcnt, cnt);
                }
            }
            cout<<mxcnt<<"\n";
        }
    }
}