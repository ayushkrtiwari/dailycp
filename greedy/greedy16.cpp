// https://www.codechef.com/problems/MARCAPS

// Derangement technique, Sorting

// Both arrays are same but maybe different in ordering in this version

#include<bits/stdc++.h>
using namespace std;
# define int long long

void solve()
{
    int n;
    cin>>n;
    vector<pair<long long,long long>> a(n);
    for(int i = 0; i < n; i++)
    {
        long long x;
        cin>>x;
        a[i] = {x, i};
    }
    
    sort(a.begin(), a.end());
    
    map<long long, long long> freq;
    for(auto x: a)
    freq[x.first]++;
    int mxf = 0;
    for(auto [key,value]: freq)
    mxf = max(mxf, value);
    if(2 * mxf > n)
    {
        cout<<"No\n";
        return;
    }
    vector<long long> res(n);
    for(int i = 0; i < n; i++)
    {
        res[a[i].second] = a[(((i - mxf) % n) + n ) % n].first;
    }
    
    cout<<"Yes\n";
    for(auto i: res)
    cout<<i<<" ";
    cout<<"\n";
    return;
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin>>t;
    while(t--)
    solve();
}