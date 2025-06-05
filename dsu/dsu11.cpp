// जय श्री राम

// https://atcoder.jp/contests/abc120/tasks/abc120_d

// Offline queries, Remove edges, Bridge Disconnection
// Mostly mathematics for no of disconnected pairs

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
    int n,m;
    cin>>n>>m;
    stack<pair<int,int>> edgestobreak;
    vector<int> parent(n);
    iota(parent.begin(),parent.end(),0);
    vector<int> size(n,1);
    int copym=m;
    while(copym--)
    {
        int a,b;
        cin>>a>>b;
        a--,b--;
        edgestobreak.push({a,b});
    }
    stack<int> res;
    int noofpairsd = n*(n-1)/2;
    res.push(noofpairsd);
    while(!edgestobreak.empty())
    {
        auto pair = edgestobreak.top();
        edgestobreak.pop();
        int parent1 = parent[findparent(pair.first,parent)];
        int parent2 = parent[findparent(pair.second,parent)];
        int parent1size = size[parent1];
        int parent2size = size[parent2];
        if(parent1 != parent2)
        noofpairsd = noofpairsd - parent1size*parent2size;
        merge(pair.first, pair.second, parent, size);
        res.push(noofpairsd);
    }
    res.pop();
    while(!res.empty())
    {
        cout<<res.top()<<" ";
        res.pop();
    }
}
