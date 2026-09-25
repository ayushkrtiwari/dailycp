// https://codeforces.com/contest/1979/problem/C

#include<bits/stdc++.h>
using namespace std;
# define int long long

int32_t main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        vector<int> k(n);
        for(auto &x: k)
        cin>>x;
        int N = 0, D = 1;
        for(int i = 0; i < n; i++)
        {
            N = N * k[i] + D, D = D * k[i];
            int g = __gcd(N, D);
            N/=g, D/=g;
        }
        if(N / D >= 1) cout<<-1;
        else
        {
            int lcm = 1;
            for(int i = 0; i < n; i++)
            lcm = (lcm * k[i])/__gcd(lcm, k[i]);
            for(int i = 0; i < n; i++)
            cout<<lcm/k[i]<<" ";
        }
        cout<<"\n";
    }
}