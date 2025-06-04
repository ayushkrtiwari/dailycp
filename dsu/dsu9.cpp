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

void merge(int a, int b, vector<int> &parent, vector<int> &size, vector<int> &sum)
{
    int parenta = findparent(a,parent);
    int parentb = findparent(b,parent);
    if(parenta==parentb) return;
    if(size[parenta]<size[parentb])
    {
        size[parentb]+=size[parenta];
        sum[parentb]+=sum[parenta];
        parent[parenta]=parentb;
    }
    else
    {
        size[parenta]+=size[parentb];
        sum[parenta]+=sum[parentb];
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
        if(x>0 and ispresent[x-1]) 
        merge(x-1,x,parent,size,sum);
        if(x<n-1 and ispresent[x+1]) 
        merge(x+1,x,parent,size,sum);
        mxsum = max(mxsum,sum[findparent(x,parent)]);
        res.push(mxsum); 
    }
    res.pop();
    while(!res.empty())
    {
        cout<<res.top()<<"\n";
        res.pop();
    }
}

// My code takes 124 ms, 600 KB

// GPT code takes 109 ms, 3300 KB

// GPT code: I dont know,   
// Same same but different

// If someone notices major difference,
// do inform me.
// I have tried 

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;
ll a[100005], s[100005], ans[100005];
int p[100005], parent[100005];
bool on[100005];

int findparent(int x)
{ 
    if(x==parent[x]) return x;
    return parent[x]=findparent(parent[x]);
}
void unite(int x,int y)
{
    x=findparent(x); y=findparent(y);
    if(x!=y)
    {
        parent[y]=x;
        s[x]+=s[y];
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n;
    for(int i=0;i<n;i++) cin>>a[i];
    for(int i=0;i<n;i++)
    {
        cin>>p[i];
        p[i]--;
    }
    for(int i=0;i<n;i++){
        parent[i]=i;
        s[i]=0;
        on[i]=false;
    }
    ll mx=0;
    for(int i=n-1;i>=0;i--){
        ans[i]=mx;
        int idx=p[i];
        on[idx]=true;
        parent[idx]=idx;
        s[idx]=a[idx];
        if(idx>0 && on[idx-1]) unite(idx,idx-1);
        if(idx+1<n && on[idx+1]) unite(idx,idx+1);
        mx=max(mx,s[findparent(idx)]);
    }
    for(int i=0;i<n;i++){
        cout<<ans[i]<<"\n";
    }
    return 0;
}
