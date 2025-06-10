// जय श्री राम  JAI SHREE RAM

// https://codeforces.com/contest/1978/problem/D

#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        long long n,c;
        cin>>n>>c;
        vector<long long> a(n);
        for(auto &x:a) cin>>x;
        long long curr = c;
        if(n==1) cout<<0;
        else
        {
            long long mx = *max_element(a.begin(),a.end());
            long long wind = 0;
            for(int i=0;i<n;i++)
            {
                if(a[i] > a[wind])
                wind = i;
            }
            if(a[0] + c >= mx)
            wind = 0, mx = a[0] + c;
            for(int i=0;i<n;i++)
            {
                curr += a[i];
                if(i == wind)
                cout<<0<<" ";
                else if(curr >= mx)
                cout<<i<<" ";
                else if(curr < mx)
                cout<<i+1<<" ";
            }
        }
        cout<<"\n";
    }
}