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
    vector<int> left; // stores left fall limit
    left.push_back(0); // so that left.back() does not give error also x,h>0
    // 1st tree always falls to left
    // no left and right bounded here
    int cnt=0;
    if(n==1)
    {
        cnt = 1; // when only tree, it can fall any side
    }
    else // try if left fall possible else if right fall possible else no fall
    {
        cnt = 1; // left tree always falls to left
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
        cnt++; // right tree can always fall to right
    }
    cout<<cnt<<"\n";
}