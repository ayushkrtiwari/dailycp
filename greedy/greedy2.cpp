// जय श्री राम                              JAI SHREE RAM

// https://codeforces.com/problemset/problem/22/D

// Greedy, Segment Endpoints
// Sort wrt segment endpoints then take the first endpoint and cancel out the lines and repeat this

#include <bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
    int n;
    cin>>n;
    vector<pair<int,int>> seg(n);
    for(auto &z: seg)
    {
        int x,y;
        cin>>x>>y;
        z.first=min(x,y);
        z.second=max(x,y);
    }
    sort(seg.begin(),seg.end(),[](const pair<int,int>&A, const pair<int,int>&B){return A.second<B.second;});
    int i=0;
    int cnt=0;
    vector<int> nails;
    while(i<n)
    {
        int take=seg[i].second;
        cnt++;
        nails.push_back(take);
        while(take<=seg[i].second and take>=seg[i].first)
        i++;
    }
    cout<<cnt<<"\n";
    for(auto i:nails)
    cout<<i<<"\n";
}