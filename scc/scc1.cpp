// https://www.geeksforgeeks.org/problems/strongly-connected-components-kosarajus-algo/1

// Kosaraju Algorithm

#include<bits/stdc++.h>
using namespace std;

class Solution{
private:
    void dfs(int node, vector<int> adj[], stack<int> &st, vector<bool> &vis)
    {
        vis[node] = true;
        for(auto nd: adj[node])
        if(!vis[nd])
        dfs(nd, adj, st, vis);
        st.push(node);
    }
    void dfs2(int node, vector<vector<int>> &adjrev, vector<bool> &vis2)
    {
        vis2[node] = true;
        for(auto x: adjrev[node])
        if(!vis2[x])
        dfs2(x, adjrev, vis2);
    }
public:
    int kosaraju(int V, vector<int> adj[]){
        stack<int> st;
        vector<bool> vis(V, false);
        for(int i = 0; i < V; i++)
        {
            if(!vis[i])
            dfs(i, adj, st, vis);
        }
        // reversing graph
        vector<vector<int>> adjrev(V);
        for(int i = 0; i < V; i++)
        {
            for(auto node: adj[i])
            adjrev[node].emplace_back(i);
        }
        vector<bool> vis2(V, false);
        int scc = 0;
        while(!st.empty())
        {
            int x = st.top();
            st.pop();
            if(!vis2[x])
            {
                scc++;
                dfs2(x, adjrev, vis2);
            }
        }
        return scc;
    }
};

int main()
{
    Solution sol;
    int V = 5;
    vector<int> adj[5] = {{2,3},{0},{1},{4},{}};
    cout<<sol.kosaraju(V, adj)<<"\n";
}


// visited array is there in kosaraju while tin(discovery time) is in tarjan