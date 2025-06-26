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
    
    // _________________________________________________________________________
    
    // Below is only for count of all subsequence of length 3, sum to be even
    
    // vector<vector<int>> sbsqncl3(4, vector<int>(2, 0));
    // sbsqncl1[a[0]]++;
    // sbsqncl2[0][a[1]] += sbsqncl1[0];
    // sbsqncl2[1][a[1]] += sbsqncl1[1];
    // // sbsqncl1[a[1]]++;
    // for(int i = 2; i < n; i++)
    // {
    //     // storing all subsequence of length 2 with parity {0,0},{0,1},{1,0},{1,1}
    //     // for(int i = 1; i < n; i++)
    //     // c2[0][a[i]] += c1[0]
    //     sbsqncl3[0][a[i]] = (sbsqncl3[0][a[i]] + sbsqncl2[0][0] % M) % M; // 00
    //     sbsqncl3[1][a[i]] = (sbsqncl3[1][a[i]] + sbsqncl2[0][1] % M) % M; // 01
    //     sbsqncl3[2][a[i]] = (sbsqncl3[2][a[i]] + sbsqncl2[1][0] % M) % M; // 10
    //     sbsqncl3[3][a[i]] = (sbsqncl3[3][a[i]] + sbsqncl2[1][1] % M) % M; // 11
    //     sbsqncl2[0][a[i]] = (sbsqncl2[0][a[i]] + sbsqncl1[0] % M) % M;
    //     sbsqncl2[1][a[i]] = (sbsqncl2[1][a[i]] + sbsqncl1[1] % M) % M;
    //     sbsqncl1[a[i - 1]] = (sbsqncl1[a[i - 1]] + 1) % M;
    // }
    // cout<<(sbsqncl3[0][0] + sbsqncl3[1][1] + sbsqncl3[2][1] + sbsqncl3[3][0]) % M <<"\n";
}
