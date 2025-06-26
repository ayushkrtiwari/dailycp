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
    // storing all subsequence of length 1 with parity 0, 1
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
        // we store this since sbsqncl2 will change while operations,
        // but we need old values
        
        // pairing: old    sbsqncl2  --> sbsqnce of length > 2
        //           01      11      -->       011
        //           00      00      -->       000
        //           10      01      -->       101
        //           11      10      -->       110
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