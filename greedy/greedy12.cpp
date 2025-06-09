// https://atcoder.jp/contests/abc080/tasks/abc080_d

#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,C;
    cin>>n>>C;
    vector<int> s(n),t(n),c(n);
    for(int i=0;i<n;i++)
    cin>>s[i]>>t[i]>>c[i];
    vector<vector<int>> v(C,vector<int>(100005,0));
    for(int i=0;i<n;i++)
    {
        v[c[i]-1][s[i]]++;
        v[c[i]-1][t[i]+1]--;
    }
    for(int i=0;i<C;i++)
    {
        int cnt = 0;
        for(int j=0;j<100005;j++)
        {
            cnt += v[i][j];
            if(cnt>0)
            v[i][j] = 1;
            else
            v[i][j] = 0;
        }
    }
    long long sum = 0, mx = 0;
    for(int i=0;i<100005;i++)
    {
        sum = 0;
        for(int j=0;j<C;j++)
        {
            sum += v[j][i];
        }
        mx = max(mx,sum);
    }
    cout<<mx<<"\n";
}