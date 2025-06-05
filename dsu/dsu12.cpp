// जय श्री राम                              JAI SHREE RAM

// https://atcoder.jp/contests/abc214/tasks/abc214_d

// Amazing Maths + DSU
// Trick is that you sort by weight inc and do as formula:
// Result += weight * size[parentu] * size[parentv] 
// and merge next simultaneously

#include<bits/stdc++.h>
using namespace std;
# define int long long

int findparent(int x, vector<int> &parent)
{
    if(x==parent[x]) return x;
    return parent[x] = findparent(parent[x],parent);
}

void merge(int a, int b, vector<int> &parent, vector<int> &size)
{
    int parenta = findparent(a,parent);
    int parentb = findparent(b,parent);
    if(parenta == parentb) return;
    if(size[parenta]<size[parentb])
    swap(parenta,parentb);
    size[parenta]+=size[parentb];
    parent[parentb]=parenta;
}

int32_t main()
{
    int n;
    cin>>n;
    vector<int> parent(n);
    iota(parent.begin(),parent.end(),0);
    vector<int> size(n,1);
    vector<pair<int,pair<int,int>>> edge(n-1);
    for(int i=0;i<n-1;i++)
    cin>>edge[i].second.first>>edge[i].second.second>>edge[i].first;
    sort(edge.begin(),edge.end(),[](const pair<int,pair<int,int>>&A, const pair<int,pair<int,int>>&B)
    {
        return A.first<B.first;
    });
    long long res=0;
    for(int i=0;i<n-1;i++)
    {
        int parentu = findparent(edge[i].second.first-1,parent);
        int parentv = findparent(edge[i].second.second-1,parent);
        if(parentu!=parentv)
        res += 1LL* edge[i].first * size[parentu] * size[parentv];
        merge(parentu,parentv,parent,size);
    }
    cout<<res<<"\n";
}
