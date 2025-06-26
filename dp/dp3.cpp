// https://codeforces.com/problemset/problem/1912/K


#include<bits/stdc++.h>
using namespace std;
# define M 998'244'353

int main()
{
    int n;
    cin>>n;
    vector<int> a(n);
    for(auto &x:a) cin>>x;
    for(auto &x:a) x = x % 2;
    vector<int> sbsqncl1(2, 0); 
    vector<vector<int>> sbsqncl2(2, vector<int>(2, 0));
    sbsqncl1[a[0]]++;
    sbsqncl2[0][a[1]] += sbsqncl1[0];
    sbsqncl2[1][a[1]] += sbsqncl1[1];
    sbsqncl1[a[1]]++;
    int ans = 0;
    for(int i = 2; i < n; i++)
    {
        auto old = sbsqncl2;
        for(int u = 0; u < 2; u++)
        {
            for(int v = 0; v < 2; v++)
            {
                if(u ^ v ^ a[i] == 0)
                {
                    ans = (ans + sbsqncl2[u][v]) % M;
                    sbsqncl2[v][a[i]] = (sbsqncl2[v][a[i]] + old[u][v]) % M;
                }
            }
        }
        sbsqncl2[0][a[i]] += sbsqncl1[0];
        sbsqncl2[1][a[i]] += sbsqncl1[1];
        sbsqncl1[a[i]]++;
    }
    cout<<ans<<"\n";
    
}