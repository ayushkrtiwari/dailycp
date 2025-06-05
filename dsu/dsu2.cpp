// जय श्री राम

// https://www.hackerrank.com/challenges/merging-communities/problem

// Simple DSU

#include<bits/stdc++.h>
using namespace std;

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

int main()
{
    int n,q;
    cin>>n>>q;
    vector<int> community(n);
    iota(community.begin(),community.end(),0);
    vector<int> parent(n);
    iota(parent.begin(),parent.end(),0);
    vector<int> size(n,1);
    while(q--)
    {
        char s;
        cin>>s;
        if(s=='M')
        {
            int a,b;
            cin>>a>>b;
            merge(a,b,parent,size);
        }
        else
        {
            int a;
            cin>>a;
            cout<<size[findparent(a,parent)]<<"\n";
        }
    }
}
