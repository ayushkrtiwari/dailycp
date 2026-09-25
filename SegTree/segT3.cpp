// https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/C

#include<bits/stdc++.h>
using namespace std;
vector<long long int> v(1e5+5);
vector<pair<long long int,long long int>> segT(4e5+5);

void build(int ind,int low, int high)
{
    if(low==high)
    {
        segT[ind].first=v[low];
        segT[ind].second=(long long int)1;
        return;
    }
    int mid=low+(high-low)/2;
    build(2*ind+1, low, mid);
    build(2*ind+2, mid+1, high);
    auto &L=segT[2*ind+1];
    auto &R=segT[2*ind+2];
    // segT[ind].first=min(segT[2*ind+1].first,segT[2*ind+2].first);
    if(L.first<R.first)
    {
        segT[ind].first=L.first;
        segT[ind].second=L.second;
    }
    else if(L.first>R.first)
    {
        segT[ind].first=R.first;
        segT[ind].second=R.second;
    }
    else
    {
        segT[ind].second=L.second+R.second;
        segT[ind].first=L.first;
    }
}

void update(int indtoupd,int node,int low, int high, long long int updtamt)
{
    if(low==high)
    {
        segT[node].first=updtamt;
        segT[node].second=(long long int)1;
        return;
    }
    int mid=(low+high)>>1;
    if(indtoupd<=mid) update(indtoupd, 2*node+1, low, mid, updtamt);
    else update(indtoupd, 2*node+2, mid+1, high, updtamt);
    auto &L=segT[2*node+1];
    auto &R=segT[2*node+2];
    if(L.first<R.first)
    {
        segT[node].first=L.first;
        segT[node].second=L.second;
    }
    else if(L.first>R.first)
    {
        segT[node].first=R.first;
        segT[node].second=R.second;
    }
    else
    {
        segT[node].second=L.second+R.second;
        segT[node].first=L.first;
    }
}

pair<long long int,long long int> query(int node,int l,int r,int ql,int qr)
{
    if(qr<l or ql>r) return {LLONG_MAX,(long long int)0};
    if(ql<=l and qr>=r) return segT[node];
    int mid=l+(r-l)/2;
    auto left = query(2*node+1, l, mid, ql, qr);
    auto right = query(2*node+2, mid+1, r, ql, qr);
    if(left.first<right.first)
    return left;
    else if(left.first>right.first)
    return right;
    else
    return {right.first,right.second+left.second};
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    cin>>n>>m;
    // vector<long long> v(n),segT(4*n);
    for(int i=0;i<n;i++)
    cin>>v[i];
    build(0,0,n-1);
    while(m--)
    {
        int t;
        cin>>t;
        if(t-1)
        {
            int x,y;
            cin>>x>>y;
            y--;
            auto ans = query(0,0,n-1,x,y);
            cout<<ans.first<<" "<<ans.second<<"\n";
        }
        else
        {
            int x,y;
            cin>>x>>y;
            // x--;
            // v[x]=y;
            update(x,0,0,n-1,y);
        }
    }
}