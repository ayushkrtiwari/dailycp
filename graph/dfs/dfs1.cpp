// https://codeforces.com/problemset/problem/500/B


// This is wrong approach. Here, I misunderstood the question.
// What I thought from pretty equation was that we have to to bring smallest elements to smallest position 
// till there is a path and if for any indices the path isn't there then break out
// But what actually was question saying in short is: make lexicographically smallest string for each connected component

#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    vector<int> p(n), pos(n);
    vector<vector<int>> edges(n, vector<int>(n));
    for(int i = 0; i < n; i++) 
    {
        cin>>p[i];
        p[i]--;
        pos[p[i]] = i;
    }
    vector<vector<int>> a(n, vector<int>(n));
    for(int i = 0; i < n; i++)
    {
        string s;
        cin>>s;
        for(int j = 0; j < n; j++)
        {
            a[i][j] = s[j] - '0';
            if(a[i][j])
            {
                edges[i].push_back(j);
                edges[j].push_back(i);
            }
        }
    }   
    
    vector<bool> vis;
    stack<int> st;
    
    function<void(int, int)> doswap = [&](int ind1, int ind2)
    {
        int val1 = p[ind1], val2 = p[ind2];
        swap(p[ind1], p[ind2]);
        swap(pos[val1], pos[val2]);
    };
    
    function<bool(int, int)> dfs = [&](int ind, int tofind)
    {
        if(st.empty()) st.push(ind);
        vis[ind] = true;
        int x = st.top();
        st.pop();
        if(x == tofind)
        return true;
        for(int nbour: edges[ind])
        if(!vis[nbour])
        return dfs(nbour, tofind);
        return false;
    };
    
    for(int i = 0; i < n; i++)
    {
        if(p[i] == i) continue;
        if(a[i][pos[i]])
        {
            doswap(i, pos[i]);
        }
        else
        {
            while(!st.empty()) st.pop();
            vis.resize(n, false);
            if(dfs(i, pos[i]))
            doswap(i, pos[i]);
            else
            break;
        }
    }
    for(auto x : p)
    cout<<x + 1<<" ";
}

// ___________________________________________________________________________________________

// My 2nd Solution using DSU and dfs

#include <bits/stdc++.h>
using namespace std;
# define MAXN 302
vector<int> parent;
vector<int> sz;

int findparent(int x)
{
    if(x == parent[x]) return x;
    return parent[x] = findparent(parent[x]);
}

void merge(int u, int v)
{
    int pu = findparent(u);
    int pv = findparent(v);
    if(sz[pu] < sz[pv])
    swap(pu, pv);
    sz[pu] += sz[pv];
    parent[pv] = pu;
}

int main() {
	// your code goes here
    int n;
    cin>>n;
    vector<int> p(n);
    for(auto &x: p)
    {
        cin>>x;
        x--;
    }
    parent.resize(n);
    iota(parent.begin(), parent.end(), 0);
    sz.resize(n);
    fill(sz.begin(), sz.end(), 1);
    vector<vector<int>> a(n, vector<int>(n));
    vector<vector<int>> edges(n);
    for(int i = 0; i < n; i++)
    {
        string s;
        cin>>s;
        for(int j = 0; j < n; j++)
        {
            a[i][j] = s[j] - '0';
            if(a[i][j])
            {
                edges[i].push_back(j);
                edges[j].push_back(i);
            }
        }
    }
    // for(int i = 0; i < n; i++)
    // sort(edges[i].begin(), edges[i].end());
    
    vector<bool> vis(n, false);
    stack<int> st;
    
    function<void(int)> dfs = [&](int i)
    {
        vis[i] = true;
        int x = st.top();
        st.pop();
        for(auto edge : edges[x])
        if(!vis[edge])
        {
            st.push(edge);
            merge(i, edge);
            dfs(edge);
        }
    };
    
    for(int i = 0; i < n; i++)
    if(!vis[i])
    st.push(i),dfs(i);
    
    vector<vector<int>> components(n);
    // components contains vector of indices of same connected components
    for(int i = 0; i < n; i++)
    components[parent[i]].push_back(i);
    
    for(int i = 0; i < n; i++)
    sort(components[i].begin(), components[i].end());
    
    vector<bool> vis2(n, false);
    vector<int> res(n);
    for(int i = 0; i < n; i++)
    {
        if(vis2[i]) continue;
        if(components[i].empty()) continue;
        // compgrp is vector of component values (sorted later)
        vector<int> compgrp;
        for(auto comp : components[i])
        {
            vis2[comp] = true;
            compgrp.push_back(p[comp]);
        }
        sort(compgrp.begin(), compgrp.end());
        int ind = 0;
        
        for(auto values : compgrp)
        p[components[i][ind++]] = values;
    }
    
    for(auto x : p) cout<< x + 1 << " ";
}

// ________________________________________________________________________________________

// GPT's precise dfs solution:

#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> p(n);
    for(int i = 0; i < n; i++){
        cin >> p[i];
        --p[i];
    }

    // build adjacency list
    vector<vector<int>> adj(n);
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        for(int j = 0; j < n; j++){
            if(s[j] == '1'){
                adj[i].push_back(j);
            }
        }
    }

    vector<bool> vis(n, false);

    // for each unvisited position, gather its component
    for(int i = 0; i < n; i++){
        if(vis[i]) continue;

        // DFS stack
        vector<int> comp;
        stack<int> st;
        st.push(i);
        vis[i] = true;

        while(!st.empty()){
            int u = st.top(); st.pop();
            comp.push_back(u);
            for(int v: adj[u]){
                if(!vis[v]){
                    vis[v] = true;
                    st.push(v);
                }
            }
        }

        // sort positions and their values separately
        sort(comp.begin(), comp.end());
        vector<int> vals;
        for(int u: comp){
            vals.push_back(p[u]);
        }
        sort(vals.begin(), vals.end());

        // reassign the smallest values to the smallest indices
        for(int k = 0; k < (int)comp.size(); k++){
            p[ comp[k] ] = vals[k];
        }
    }

    // output in 1‑based
    for(int x: p) cout << (x+1) << ' ';
    cout << "\n";
    return 0;
}
