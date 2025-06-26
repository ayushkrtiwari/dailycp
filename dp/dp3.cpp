// जय श्री राम  JAI SHREE RAM

// https://codeforces.com/problemset/problem/1912/K

// Topic: DP, subsequence, inclusion-exclusion

/**
 * The function calculates the count of subsequences of length greater than 2 with 3 continuous
 * elements of even sum in a given array.
 */
// Here, you need to get count of all subsequences of length > 2 with 3 continuous
// elements of even sum. 
// So, when at i, we calculate subsequence of length 1 with 0 and 1 parity
// and with it we calculate subsequence of length 2 with 00, 01, 10, 11 parity
// and with this we calculate subsequence of length > 2 with 000, 001, 010,..., 111 parity
// The v,a[i] parity in subsqncl2 at i states that we have such v,a[i] which contains all
// subsequences already occurred till now with the condition u ^ v ^ a[i] == 0.
// For the > 2, when we are at i, we calculate that if we have v,a[i] parity, then how many
// u,v parity has been till now satisfying u^v^a[i] == 0. This way, we have all such 
// subsequence satisfying > 2 parity of such kind. We calculate it by storing the answer
// with sums of all parities satisfying the condition, and then we update them with the 
// new i by checking if present v, a[i] has occurrences of u, v such that u ^ v ^ a[i] == 0
// Now we update all the subsequences after these operations by a[i] and with sbsqncl1

// For more clearance, when we get a[i] we know the 2 previous subsequence values hence we 
// add those values to ans that is sbsqncl2[u][v] since if we know value of a[i] 
// then we are sure that we need to sum up those values of u, v 
// which have come up as to satisfy the conditions,
// not sbsqncl2[v][a[i]] which we still have not calculated.

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


// FOR EASY UNDERSTANDING OF FINDING OF LENGTH > 2

// #include <bits/stdc++.h>
// using namespace std;
// #define M 998'244'353

// int main(){
//     int n;
//     cin >> n;
//     vector<int> a(n);
//     for(auto &x : a) cin >> x;
//     for(auto &x : a) x %= 2;

//     vector<int> sbsqncl1(2, 0);
//     vector<vector<int>> sbsqncl2(2, vector<int>(2, 0));

//     // seed the length-1 and length-2 tables with the first two elements
//     sbsqncl1[a[0]]++;
//     sbsqncl2[0][a[1]] += sbsqncl1[0];
//     sbsqncl2[1][a[1]] += sbsqncl1[1];
//     sbsqncl1[a[1]]++;
//     long long ans = 0;

//     for(int i = 2; i < n; i++){
//         int b = a[i];

//         // save old pairs of length>=2
//         auto old = sbsqncl2;

//         // 1) extend all old length>=2 subseqs (u,v)-> +b if u^v^b==0
//         //    count them in ans, and re-insert into sbsqncl2[v][b]
//         if ((0 ^ 0 ^ b) == 0) {
//             ans = (ans + sbsqncl2[0][0]) % M;
//             sbsqncl2[0][b] = (sbsqncl2[0][b] + old[0][0]) % M;
//         }
//         if ((0 ^ 1 ^ b) == 0) {
//             ans = (ans + sbsqncl2[0][1]) % M;
//             sbsqncl2[1][b] = (sbsqncl2[1][b] + old[0][1]) % M;
//         }
//         if ((1 ^ 0 ^ b) == 0) {
//             ans = (ans + sbsqncl2[1][0]) % M;
//             sbsqncl2[0][b] = (sbsqncl2[0][b] + old[1][0]) % M;
//         }
//         if ((1 ^ 1 ^ b) == 0) {
//             ans = (ans + sbsqncl2[1][1]) % M;
//             sbsqncl2[1][b] = (sbsqncl2[1][b] + old[1][1]) % M;
//         }

//         // 2) extend all length-1 subseqs to length-2
//         sbsqncl2[0][b] = (sbsqncl2[0][b] + sbsqncl1[0]) % M;
//         sbsqncl2[1][b] = (sbsqncl2[1][b] + sbsqncl1[1]) % M;

//         // 3) record a new length-1 subseq ending in a[i-1]
//         sbsqncl1[a[i]] = (sbsqncl1[a[i]] + 1) % M;
//     }

//     cout << ans << "\n";
//     return 0;
// }
