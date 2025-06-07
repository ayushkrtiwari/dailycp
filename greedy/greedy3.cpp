// जय श्री राम                              JAI SHREE RAM

// https://codeforces.com/problemset/problem/545/C

#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    vector<pair<int,int>> xh(n);
    for(auto &x:xh)
    cin>>x.first>>x.second;
    vector<int> left;
    left.push_back(0);
    int cnt=0;
    if(n==1)
    {
        cnt = 1;
    }
    else
    {
        cnt = 1;
        for(int i=1;i<n-1;i++)
        {
            if(xh[i].first - xh[i].second > xh[i-1].first and xh[i].first - xh[i].second > left.back())
            {
                cnt++;
            }
            else if(xh[i].first + xh[i].second < xh[i+1].first)
            {
                left.push_back(xh[i].first + xh[i].second);
                cnt++;
            }
        }
        cnt++;
    }
    cout<<cnt<<"\n";
}