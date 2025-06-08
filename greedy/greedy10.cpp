// जय श्री राम  JAI SHREE RAM

// https://codeforces.com/problemset/problem/322/B

// Trick: Take red, green, blue boquet but more optimised solution is there:
// take 0 mixed boquet and then form the 3
// take 1 mixed boquet and then form the 3
// take 2 mixed boquet and then form the 3
// take max of the 3 cases
// other number of mixed boquet means you can instead form the individual boquets

#include<bits/stdc++.h>
using namespace std;
int main()
{
    long long r,g,b;
    cin>>r>>g>>b;
    long long cnt0 = 0,cnt1 = 0,cnt2 = 0;
    cnt0 += r/3 + g/3 + b/3;
    if(r-1 >= 0 and g-1 >= 0 and b-1 >= 0) cnt1 += (r-1)/3 + (g-1)/3 + (b-1)/3 + 1;
    if(r-2 >= 0 and g-2 >= 0 and b-2 >= 0) cnt2 += (r-2)/3 + (g-2)/3 + (b-2)/3 + 2;
    cout<<max(cnt0,max(cnt1,cnt2))<<"\n";
}