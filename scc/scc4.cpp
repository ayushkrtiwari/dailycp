// https://www.geeksforgeeks.org/problems/strongly-connected-component-tarjanss-algo-1587115621/1

// Tarjan's Algorithm

class Solution {
    int timer = 0;
  private:
    // to avoid function overhead, we can declare these heavy data structures in global scope as shown in next method
    void dfs(int node, vector<int> adj[], vector<bool> &onStack, stack<int> &st, vector<vector<int>> &sccgrp, vector<int> &low, vector<int> &tin)
    {
        tin[node] = low[node] = ++timer;
        onStack[node] = true;
        st.push(node);
        for(auto i: adj[node])
        {
            // if(i != node)
            // {
            //     if(!vis[i])
            //     {
            //         dfs(i, adj, vis, onStack, st, sccgrp, low);
            //     }
            //     if(low[i] < low[node] and onStack[i])
            //     sccgrp[low[i]].emplace_back(node);
            //     low[node] = min(low[node], low[i]);
            // }


            // tin[i] == 0 is sentinel for unvisited nodes
            if(tin[i] == 0)
            {
                dfs(i, adj, onStack, st, sccgrp, low, tin);
                low[node] = min(low[i], low[node]);
            }
            else if(onStack[i]) // if visiting root SCC node, since onStack, hence SCC root here
            // can also keep if rather than else if
            {
                // no more dfs, backtrack
                // set low as SCC root's node
                low[node] = min(tin[i], low[node]);
            }
            // _______________________________________________________

            // THIS ALSO WORKS:

            // if(tin[i] == 0)
            // {
            //     dfs(i, adj, onStack, st, sccgrp, low, tin);
            // }
            // if(onStack[i])
            // {
            //     low[node] = min(low[i], low[node]);
            // }
            // _______________________________________________________

            // THIS ALSO WORKS:

            // if(tin[i] == 0)
            // {
            //     dfs(i, adj, onStack, st, sccgrp, low, tin);
            //     low[node] = min(low[i], low[node]); 
            // }
            // if(onStack[i])
            // {
            //     low[node] = min(tin[i], low[node]);
            // }
            // __________________________________________________________
        }
        if(low[node] == tin[node]) // we are at scc root
        {
            vector<int> component;
            while(!st.empty())   // pop stack till scc root
            {
                int x = st.top();
                st.pop();
                onStack[x] = false;
                component.push_back(x);
                if(x == node) break;
            }
            sort(component.begin(), component.end());
            sccgrp.push_back(component);
            // delete[] component;
        }
    }
  public:
    // Function to return a list of lists of integers denoting the members
    // of strongly connected components in the given graph.
    vector<vector<int>> tarjans(int V, vector<int> adj[]) {
        // code here
        vector<bool> onStack(V, false);
        stack<int> st;
        vector<int> low(V, 0);
        vector<vector<int>> sccgrp;
        vector<int> tin(V, 0);
        timer = 0;
        while(!st.empty()) st.pop();
        for(int i = 0; i < V; i++)
        {
            if(tin[i] == 0)
            dfs(i, adj, onStack, st, sccgrp, low, tin);
            
            // ____________________________________________
            // WRONG:
            // for(auto node: adj[i])
            // {
            //     if(node != i)
            //     {
            //         dfs(node, adj, vis, onStack, st, sccgrp, low);
            //     }
            // }
        }
        sort(sccgrp.begin(), sccgrp.end(), [&](auto &v1, auto &v2)
        {
            // question asks not for node order in tin time, 
            // but sorted order fully with components in respective SCCs.
            // no row is empty due to algo implementation, implies
            // every node is unique, hence just comparing roots will be right
            // hence no comparison for size or no checks for duplicates or empty 
            return v1[0] < v2[0];
        });
        return sccgrp;
    }
};

____________________________________________________________________________________________

// GPT clean solution:

class Solution {
  private:
    int timeDFS;
    vector<int> disc, low;
    vector<bool> onStack;
    stack<int> st;
    vector<vector<int>> sccs;

    void dfs(int u, vector<int> adj[]) {
        disc[u] = low[u] = ++timeDFS;
        st.push(u);
        onStack[u] = true;

        for (int v : adj[u]) {
            if (disc[v] == 0) {
                // tree edge
                dfs(v, adj);
                low[u] = min(low[u], low[v]);
            }
            else if (onStack[v]) {
                // back edge
                low[u] = min(low[u], disc[v]);
            }
        }

        // if u is root of SCC
        if (low[u] == disc[u]) {
            vector<int> comp;
            while (true) {
                int v = st.top(); 
                st.pop();
                onStack[v] = false;
                comp.push_back(v);
                if (v == u) break;
            }
            sort(comp.begin(), comp.end());
            sccs.push_back(move(comp));
        }
    }

  public:
    vector<vector<int>> tarjans(int V, vector<int> adj[]) {
        timeDFS = 0;
        disc.assign(V, 0);
        low.assign(V, 0);
        onStack.assign(V, false);
        // clear stack and sccs
        // while (!st.empty()) st.pop();
        // sccs.clear();

        // run DFS from every unvisited node
        for (int i = 0; i < V; i++) {
            if (disc[i] == 0) {
                dfs(i, adj);
            }
        }

        return sccs;
    }
};
