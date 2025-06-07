// https://atcoder.jp/contests/abc131/tasks/abc131_d

#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    vector<pair<int,int>> ab(n);
    for(int i=0;i<n;i++)
    {
        cin>>ab[i].first>>ab[i].second;
    }
    sort(ab.begin(),ab.end(),[](const pair<int,int>&A,const pair<int,int>&B)
    {
        return A.second<B.second;
    });
    bool possible = true;
    int time=0;
    for(auto i:ab)
    {
        time+=i.first;
        if(time>i.second)
        {
        possible=false;
        break;
        }
    }
    if(possible)
    cout<<"Yes\n";
    else
    cout<<"No\n";
}