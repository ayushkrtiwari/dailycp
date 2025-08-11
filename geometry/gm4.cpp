// https://codeforces.com/problemset/problem/712/C

#include<bits/stdc++.h>
using namespace std;
int main()
{
    int x, y;
    cin>>x>>y;
    int a[3] = {y, y, y};
    int ans = 0;
    while(a[0] != x or a[1] != x or a[2] != x)
    {
        sort(a, a + 3);
        a[0] = min(x, a[1] + a[2] - 1);
        ans++;
        // cout<<a[0]<<" "<<a[1]<<" "<<a[2]<<"\n";
    }
    cout<<ans<<"\n";
}