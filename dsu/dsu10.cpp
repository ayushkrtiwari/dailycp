// जय श्री राम

// https://codeforces.com/problemset/problem/371/D

// Simple DSU, keep track of endpoints
// Mostly implementation, DSU just for endpoint tracking in O(1), overall O(n) else becomes O(n^2) complexity

#include<bits/stdc++.h>
using namespace std;

int findparent(int x, vector<int> &parent)
{
    if(x==parent[x]) return x;
    return parent[x] = findparent(parent[x],parent);
}

void merge(int a, int b, vector<int> &parent, vector<int> &size, vector<int> &endcontainer)
{
    int parenta = findparent(a,parent);
    int parentb = findparent(b,parent);
    if(parenta == parentb) return;
    if(size[parenta]<size[parentb])
    swap(parenta,parentb);
    size[parenta]+=size[parentb];
    parent[parentb]=parenta;
    endcontainer[parenta] = max(endcontainer[parenta],endcontainer[parentb]);
}

int main()
{
    int n;
    cin>>n;
    vector<int> c(n);
    for(auto &x: c)
    cin>>x;
    vector<int> parent(n);
    iota(parent.begin(),parent.end(),0);
    vector<int> endcontainer(n);
    iota(endcontainer.begin(),endcontainer.end(),0);
    vector<int> filledwater(n,0);
    vector<int> size(n,1);
    int m;
    cin>>m;
    while(m--)
    {
        int qt;
        cin>>qt;
        qt--;
        if(qt)
        {
            int v;
            cin>>v;
            v--;
            cout<<filledwater[v]<<"\n";
        }
        else
        {
            int v,l;
            cin>>v>>l;
            v--;
            int endcnt = endcontainer[findparent(v,parent)];
            if(filledwater[endcnt] + l <= c[endcnt])
            filledwater[endcnt] += l;
            else
            {
                while(endcnt < n-1 and filledwater[endcnt] + l > c[endcnt])
                {
                    int put = c[endcnt] - filledwater[endcnt];
                    filledwater[endcnt] = c[endcnt];
                    l = l - put;
                    merge(endcnt,endcnt+1,parent,size,endcontainer);
                    endcnt = endcontainer[findparent(endcnt,parent)];
                }
                if(endcnt == n-1)
                {
                    if(filledwater[endcnt] + l > c[endcnt])
                    filledwater[endcnt] = c[endcnt];
                    else
                    filledwater[endcnt] += l;
                    continue;
                }
                filledwater[endcnt] += l;
            }
        }
    }
}
