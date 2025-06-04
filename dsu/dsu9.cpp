// https://codeforces.com/problemset/problem/722/C

// Offline queries, Node version(other was edge)
// Trick: Need some extra boolean vector to mark the presence of node

#include<bits/stdc++.h>
using namespace std;
# define int long long

int findparent(int x,vector<int>&parent)
{
    if(x==parent[x]) return x;
    return parent[x]=findparent(parent[x],parent);
}

void merge(int a, int b, vector<int> &parent, vector<int> &size, vector<int> &sum, long long &mxsum)
{
    int parenta = findparent(a,parent);
    int parentb = findparent(b,parent);
    if(parenta==parentb) return;
    if(size[parenta]<size[parentb])
    {
        size[parentb]+=size[parenta];
        sum[parentb]+=sum[parenta];
        mxsum = max(mxsum,sum[parentb]);
        parent[parenta]=parentb;
    }
    else
    {
        size[parenta]+=size[parentb];
        sum[parenta]+=sum[parentb];
        mxsum = max(mxsum,sum[parenta]);
        parent[parentb]=parenta;
    }
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin>>n;
    bool ispresent[n]={false};
    vector<int> a(n);
    for(auto &x:a) cin>>x;
    vector<int> sum(n),size(n,1);
    vector<int> parent(n);
    iota(parent.begin(),parent.end(),0);
    for(int i=0;i<n;i++)
    sum[i]=a[i];
    int copyn=n;
    long long mxsum=0;
    stack<int> res;
    res.push(0);
    stack<int> st;
    while(copyn--)
    {
        int x;
        cin>>x;
        x--;
        st.push(x);
    }
    while(!st.empty())
    {
        int x = st.top();
        st.pop();
        ispresent[x] = true;
        mxsum = max(mxsum,a[x]);
        if(x>0 and ispresent[x-1]) 
        merge(x-1,x,parent,size,sum,mxsum);
        if(x<n-1 and ispresent[x+1]) 
        merge(x+1,x,parent,size,sum,mxsum);
        res.push(mxsum); 
    }
    res.pop();
    while(!res.empty())
    {
        cout<<res.top()<<"\n";
        res.pop();
    }
}

