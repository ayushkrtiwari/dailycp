// https://codeforces.com/problemset/problem/322/B

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