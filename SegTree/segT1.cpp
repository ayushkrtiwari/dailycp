// https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/A

#include<bits/stdc++.h>
using namespace std;
vector<long long int> v(1e5+5);
vector<long long int> segT(4e5+5);

void build(int ind,int low, int high)
{
    if(low==high)
    {
        segT[ind]=v[low];
        return;
    }
    int mid=low+(high-low)/2;
    build(2*ind+1, low, mid);
    build(2*ind+2, mid+1, high);
    segT[ind]=segT[2*ind+1]+segT[2*ind+2];
}

void update(int indtoupd, int node,int low, int high, long long int updtamt)
{
    if(low==high)
    {
        segT[node]=updtamt;
        return;
    }
    int mid=(low+high)>>1;
    if(indtoupd<=mid) update(indtoupd, 2*node+1, low, mid, updtamt);
    else update(indtoupd, 2*node+2, mid+1, high, updtamt);
    segT[node]=segT[2*node+1]+segT[2*node+2];
}

long long int query(int node,int l,int r,int ql,int qr)
{
    if(qr<l or ql>r) return /*(long long int)*/0;
    if(ql<=l and qr>=r) return segT[node];
    int mid=l+(r-l)/2;
    return query(2*node+1, l, mid, ql, qr) + query(2*node+2, mid+1, r, ql, qr);
}

int main()
{
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
            cout<<query(0,0,n-1,x,y)<<"\n";
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