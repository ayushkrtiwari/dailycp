// https://codeforces.com/contest/600/problem/E

// small to large merge, heavy-light decomposition, dsu on tree

// when we get to a node, we find bigchild of that node
// then we do dfs on all small child without updating info
// then we do dfs on bigchild updating info
// then we do dfs on all small child updating info
// then we clear out info for all subtree nodes, including node itself, bigchild and all small childs

// Let say the light edges are dfs, thus they will merge to parent of size >= 2 * its size (due to 1 heavy node present)
// This 2 ^ (i - 1) min size for ith node. Hence n >= 2 ^ (i - 1) gives i <= log2(n) + 1. Take floor of log
// This means light nodes can be added upto at max log2(n) times.
// Now, we want to know how many times does light nodes contribute to complexity or say cnt
// So, we know that light edge can have only log2(n) parents/ancestors,
// hence only those log2(n) ancestors when have dfs, then only that node contributes to cnt
// So 1 light node contributes log2(n) times, hence n(say) nodes contribute n log n times.
// For heavy nodes, each nodes add only constant time, since they are added only once and contribute only once to cnt
// This way they have complexity of O(n) only.
// Hence complexity : O(n + n log n) ~ O(n log n)

#include <bits/stdc++.h>
using namespace std;
# define int long long
# define MAXN 100'005

int sz[MAXN], st[MAXN], ft[MAXN], euler[MAXN], cnt[MAXN], col[MAXN];
// int bigchild[MAXN];
vector<int> edges[MAXN];
int timer = 0;
int currmx = 0, currsum = -1;
int ans[MAXN];

void dfss(int node, int parent, int keep)
{
    // int mx = -1, bigchild = -1;
    // for(auto &child : edges[node])
    //     if(child != parent and sz[child] > sz[bigchild])
    //         bigchild = child;
    // if(bigchild != -1)
    //     for(auto &c : ucol[bigchild])
    //         ucol[node].insert(c);
    // for(auto &schild : edges[node])
    //     if(schild != parent and schild != bigchild)
    //         for(auto &c : ucol[schild])
    //             ucol[node].insert(c);
    // if(keep == 0)
    //     for(int tim = st[node]; tim < ft[node]; tim++)
    auto add_node = [&](int node)
    {
        int c = ++cnt[col[node]];
        if(c > currmx)
        currmx = c, currsum = col[node];
        else if(c == currmx)
        currsum += col[node];
    };
    int mx = -1, bigchild = -1;
    // finding bigchild of node
    for(auto &child : edges[node])
        if(child != parent and sz[child] > mx)
            mx = sz[child], bigchild = child;
    // doing dfs on all small childs without updating info
    for(auto &child : edges[node])
        if(child != parent and child != bigchild)
            dfss(child, node, 0);

    /**   mistake
    // if(bigchild != -1)
    //     for(auto &child : edges[bigchild])
    //         dfss(child, node, 1);
    */

    // doing dfs on bigchild updating info, node has atmost 1 bigchild
    if(bigchild != -1)
        dfss(bigchild, node, 1);

    /**   mistake
    for(auto &child : edges[node])
        if(child != parent and child != bigchild)
            add_node(child);
    */
    
    // doing dfs iteratively on all small childs updating info
    // can do it recursively too, but this is doing both dfs and updation together
    for(auto &child : edges[node])
    {
        if(child == parent or child == bigchild) continue;
        for(int tim = st[child]; tim < ft[child]; tim++)
            add_node(euler[tim]);
    }
    add_node(node);
    ans[node] = currsum;
    if(keep == 0)
    {
        /** mistake
        // for(auto &child : edges[node])
        // {
            // if(child == parent or child == bigchild) continue;
        */
        
        for(int tim = st[node]; tim < ft[node]; tim++)
            cnt[col[euler[tim]]] = 0;
            // here, all the subtree nodes including this node itself, bigchild and all smallchild has been cleared out.

        /** mistake
        // }
        // if(child != parent and child != bigchild)
        */
        
        currsum = -1, currmx = 0;
    }
}

void dfs(int node, int parent)
{
    sz[node] = 1;
    euler[timer] = node;
    st[node] = timer++;
    for(auto &nb : edges[node])
    {
        if(nb == parent) continue;
        dfs(nb, node);
        sz[node] += sz[nb];
    }
    ft[node] = timer;
}

int32_t main() {
	// your code goes here
    int n;
    cin>>n;
    // int col[n];
    for(int i = 0; i < n; i++) cin>>col[i];
    // vector<int> edges[n - 1];
    for(int i = 0; i < n - 1; i++)
    {
        int x, y;
        cin>>x>>y;
        x--, y--;
        edges[x].emplace_back(y);
        edges[y].emplace_back(x);
    }
    dfs(0, -1);
    dfss(0, -1, 1);
    for(int i = 0; i < n; i++)
    cout<<ans[i]<<" \n"[i == n - 1];
}
