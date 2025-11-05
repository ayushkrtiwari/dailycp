// https://codeforces.com/contest/2154/problem/C2

#include <bits/stdc++.h>
using namespace std;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};


int32_t main() 
{
	int t;
	cin>>t;
	for(int tt = 1; tt <= t; tt++)
	{
	    int n;
	    cin>>n;
	    vector<vector<int>> edges(n + 1);
	    vector<int> deg(n + 1, 0);
	    for(int i = 1; i < n; i++)
	    {
	        int x, y;
	        cin>>x>>y;
	        x--, y--;
	        edges[x].push_back(y);
	        edges[y].push_back(x);
	        deg[x]++, deg[y]++;
	    }
	    vector<int> depth(n + 1, 0);
	    vector<bool> vis(n + 1, false);
	    vector<int> parent(n + 1, -1);
	    auto calculate_depth = [&](auto&& self, int parent, int node, int dep) -> void
	    {
	        vis[node] = true;
	        depth[node] = parent == -1 ? 0 : dep;
	        for(auto &child : edges[node])
	        {
	           // depth[child] = depth[node] + 1;
	            if(!vis[child])
	            self(self, node, child, depth[node] + 1);
	        }
	    };
	    calculate_depth(calculate_depth, -1, 0, 0);
	    
	   // cout<<"depth : ";
	   // for(int i = 0; i < n; i++)
	   // cout<<depth[i]<<" ";
	   // cout<<"\n";
	    
	    vector<bool> viss(n + 1, false);
	    vector<bool> ispathnode(n + 1, false);
	    unordered_map<int, int, custom_hash> pathnode, notpathnode;
	    auto dfs = [&](auto& self, int node) -> bool
	    {
	        viss[node] = true;
	        if(node == n - 1)
	        return ispathnode[node] = true;
	        bool inpath = false;
	        for(auto &child : edges[node])
	        {
	            if(!viss[child])
	            inpath |= self(self, child);
	        }
	        return ispathnode[node] = inpath;
	    };
	    ispathnode[0] = dfs(dfs, 0);
	    for(int i = 0; i < n; i++)
	    if(ispathnode[i]) pathnode[i]++;
	    else notpathnode[i]++;
	    
	   // cout<<"pathnode: ";
	   // for(int i = 0; i < n; i++)
	   // if(ispathnode[i]) cout<<i + 1<<" ";
	   // cout<<"\n";
	    // if we are at odd depth, 
	    // remove wrong path leaf nodes with odd depth
	    // and vice versa
	    unordered_map<int, int, custom_hash> oddleaf, evenleaf;
	   // cout<<"leaf nodes except start and final: ";
	    for(int i = 0; i < n; i++)
	    {
	       // if(deg[i] == 1 and !ispathnode[i])
	       // we want all nodes except start and final
	        if(deg[i] == 1 and i != 0 /*and i != n - 1*/)
	        {
	           // cout<<i+1<<" ";
	            if(depth[i] % 2) oddleaf[i]++;
	            else evenleaf[i]++;
	        }
	    }
	   // cout<<"\n";
	    // when removing a leaf node, clear its adjacent edge list, 
	    // obviously it will of size 1, if n not 1
	    vector<pair<int, int>> res;
	    int noofpathnodes = pathnode.size();
	    int currdep = 0;
	    vector<bool> isvis(n + 1, false);
	    // the loop wont run only for n - noofpathnodes times 
	    // since, say node 1 has 3 child, then we need max(2 * odddepth + 1, 2 * evendepth - 1)
	    int odddepth, evendepth;
	    odddepth = evendepth = 0;
	   // cout<<"Nodes to be removed : ";
	    for(int i = 0; i < n; i++)
	    if(i != 0 and i != n - 1)
	    {
	       // cout<<i + 1<<" ";
    	    if(depth[i] % 2) odddepth++;
    	    else evendepth++;
	    }
	   // cout<<"\n";
	   // cout<<"oddleaf : ";
	   // for(auto &x : oddleaf)
	   // cout<<x.first+1<<" ";
	    
	   // cout<<"evenleaf : ";
	   // for(auto &x : evenleaf)
	   // cout<<x.first+1<<" ";
	   // cout<<"\n";
	   // for(int i = 0; i < max(2 * odddepth + 1, 2 * evendepth - 1)/*n - noofpathnodes*/; i++)
	    // we take account of removing nodes so that we can count if all 
	    // undesired nodes are removed and then break the loop
	    // we still wont be able to figure when to stop, since some {0, 1}
	    // are necessary, dont want hectic to add up later and ignore it now.
	    
	    // ohh shit, i have now understood that all nodes except starting
	    // and destination must be broken. Late but Gr8;
	   // unordered_map<int, int, custom_hash> removingnodes;
	    int nodesremoved = 0;
	    int nodestoberemoved = n - 1;
	    int icpy;
	    for(int i = 0; i < 3 * n - noofpathnodes - 1 and nodesremoved < nodestoberemoved; i++)
	    {
	       // if(ispathnode[i]) continue;
	        if(currdep % 2)
	        {
	            if(evenleaf.empty())
	            {
	               // cout<<",";
	                res.push_back({0, 0});
	                currdep++;
	                continue;
	            }
	           // cout<<"'";
	            int evenleafnode = (evenleaf.begin()) -> first;
	            res.push_back({2, evenleafnode});
	            evenleaf.erase(evenleaf.begin());
	            nodesremoved++;
	            for(auto &x : edges[evenleafnode])
	            {
	                deg[x]--;
	               // if(deg[x] == 1 and !ispathnode[x])
	                if(deg[x] == 1 and x != 0 /*and x != n - 1*/)
	                {
	                    if(depth[x] % 2) oddleaf[x]++;
	                    else evenleaf[x]++;
	                }
	            }
	        }
	        else
	        {
	            if(oddleaf.empty())
	            {
	               // cout<<".";
	                res.push_back({0, 0});
	                currdep++;
	                continue;
	            }
	           // cout<<"-";
	            int oddleafnode = (oddleaf.begin()) -> first;
	            res.push_back({2, oddleafnode});
	            oddleaf.erase(oddleaf.begin());
	            nodesremoved++;
	            for(auto &x : edges[oddleafnode])
	            {
	                // do we need to make another vis array here for updating deg consistently ??
	                // no since they would only be decreasing, if more updates would happen
	                // it would become <= 0, hence no problem since it wont be again 1
	                // also if one of the nodes got removed, it means it was already 1,
	                // then updating it in next node anyway will make it <= 0
	                deg[x]--;
	               // if(deg[x] == 1 and !ispathnode[x])
	                // we need to keep n - 1, refer sample tc 4 else we wont be able to cross
	                if(deg[x] == 1 and x != 0 /*and x != n - 1*/)
	                {
	                    if(depth[x] % 2) oddleaf[x]++;
	                    else evenleaf[x]++;
	                }
	            }
	        }
	        if(nodesremoved == nodestoberemoved and currdep % 2)
	        res.push_back({0, 1});
	        currdep++;
	    }
	    // res only contains type 2 operations, fill type 1 carefully
	    
	    // i dont know why we are getting 1, the first time only, before type 2
	    // i need to cout res for now 
	    // yes there is a {0, 0} at start in res, i dont know why
	    vector<pair<int, int>> outputres;
	    int ressize = res.size();
	    
	   // cout<<"res starts\n";
	   // for(auto &x : res)
	   // cout<<x.first<<" "<<x.second+1<<"\n";
	   // cout<<"res ends\n";
	    
	    int start = 0;
	   // for(start = 0; start < ressize; start++)
	   // if(res[start].first == 0) continue;
	   // else break;
	   
	    // dont put {1, 0} after last type 2 operation in outputres
	    int last2typeidx = ressize;
	    for(int i = ressize - 1; i >= 0; i--)
	    if(res[i].first == 2)
	    {
	        last2typeidx = i;
	        break;
	    }
	    
	    for(int i = start; i < ressize; i++)
	    {
	        pair<int, int> pr = res[i];
	        if(pr.first == 2)
	        {
	            outputres.push_back({2, pr.second});
	            if(i != last2typeidx)
	            outputres.push_back({1, 0});
	        }
	        else if(pr.first == 0)
	        {
	            outputres.push_back({1, 0});
	            continue;
	        }
	    }
	    
	   // for(int i = 1; i < noofpathnodes; i++)
	   // there is only 2 nodes : 0 and n - 1 left at last
	    outputres.push_back({1, 0});
	    
	   // cout<<"outputres begins\n";
	   // for(auto &x : outputres)
	   // cout<<x.first<<" "<<x.second+1<<"\n";
	   // cout<<"outputres ends \n";
	    
	   // cout<<"Case #"<<tt<<" :\n";
	    cout<<outputres.size() - 1<<"\n";
	    for(auto &x : outputres)
	    {
	        if(x.first == 1) cout<<1<<"\n";
	       // else if(x.first == 0) cout<<1<<"\n";
	        else if(x.second == n - 1) continue;
	        else cout<<2<<" "<<x.second + 1<<"\n";
	    }
	}
}

// _____________________________________________________________________
// we did everything, erasing from leaf node, only leaving at last nodes 1 and n
// then including n in removal list too so that we can cross that node to remove others too
// now we came to know that, we only need to remove other nodes starting from leaf node
// leaving pathnodes intact for now. Hence we will be implementing the additional code 
// for leaving pathnodes and then removing pathnodes, using the old code where we did not cross n

// _____________________________________________________________________

#include <bits/stdc++.h>
using namespace std;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};


int32_t main() 
{
	int t;
	cin>>t;
	for(int tt = 1; tt <= t; tt++)
	{
	    int n;
	    cin>>n;
	    vector<vector<int>> edges(n + 1);
	    vector<int> deg(n + 1, 0);
	    for(int i = 1; i < n; i++)
	    {
	        int x, y;
	        cin>>x>>y;
	        x--, y--;
	        edges[x].push_back(y);
	        edges[y].push_back(x);
	        deg[x]++, deg[y]++;
	    }
	    vector<int> depth(n + 1, 0);
	    vector<bool> vis(n + 1, false);
	    vector<int> parent(n + 1, -1);
	    auto calculate_depth = [&](auto&& self, int parent, int node, int dep) -> void
	    {
	        vis[node] = true;
	        depth[node] = parent == -1 ? 0 : dep;
	        for(auto &child : edges[node])
	        {
	           // depth[child] = depth[node] + 1;
	            if(!vis[child])
	            self(self, node, child, depth[node] + 1);
	        }
	    };
	    calculate_depth(calculate_depth, -1, 0, 0);
	    
	   // cout<<"depth : ";
	   // for(int i = 0; i < n; i++)
	   // cout<<depth[i]<<" ";
	   // cout<<"\n";
	    
	    vector<bool> viss(n + 1, false);
	    vector<bool> ispathnode(n + 1, false);
	    unordered_map<int, int, custom_hash> pathnode, notpathnode;
	    auto dfs = [&](auto& self, int node) -> bool
	    {
	        viss[node] = true;
	        if(node == n - 1)
	        return ispathnode[node] = true;
	        bool inpath = false;
	        for(auto &child : edges[node])
	        {
	            if(!viss[child])
	            inpath |= self(self, child);
	        }
	        return ispathnode[node] = inpath;
	    };
	    ispathnode[0] = dfs(dfs, 0);
	    for(int i = 0; i < n; i++)
	    if(ispathnode[i]) pathnode[i]++;
	    else notpathnode[i]++;
	    
	   // cout<<"pathnode: ";
	   // for(int i = 0; i < n; i++)
	   // if(ispathnode[i]) cout<<i + 1<<" ";
	   // cout<<"\n";
	    // if we are at odd depth, 
	    // remove wrong path leaf nodes with odd depth
	    // and vice versa
	    unordered_map<int, int, custom_hash> oddleaf, evenleaf;
	   // cout<<"leaf nodes except start and final: ";
	    for(int i = 0; i < n; i++)
	    {
	       // if(deg[i] == 1 and !ispathnode[i])
	       // we want all nodes except start and final
	        if(deg[i] == 1 and i != 0 and i != n - 1)
	        {
	           // cout<<i+1<<" ";
	            if(depth[i] % 2) oddleaf[i]++;
	            else evenleaf[i]++;
	        }
	    }
	   // cout<<"\n";
	    // when removing a leaf node, clear its adjacent edge list, 
	    // obviously it will of size 1, if n not 1
	    vector<pair<int, int>> res;
	    int noofpathnodes = pathnode.size();
	    int currdep = 0;
	    vector<bool> isvis(n + 1, false);
	    // the loop wont run only for n - noofpathnodes times 
	    // since, say node 1 has 3 child, then we need max(2 * odddepth + 1, 2 * evendepth - 1)
	    int odddepth, evendepth;
	    odddepth = evendepth = 0;
	   // cout<<"Nodes to be removed : ";
	    for(int i = 0; i < n; i++)
	    if(i != 0 and i != n - 1)
	    {
	       // cout<<i + 1<<" ";
    	    if(depth[i] % 2) odddepth++;
    	    else evendepth++;
	    }
	   // cout<<"\n";
	   // cout<<"oddleaf : ";
	   // for(auto &x : oddleaf)
	   // cout<<x.first+1<<" ";
	    
	   // cout<<"evenleaf : ";
	   // for(auto &x : evenleaf)
	   // cout<<x.first+1<<" ";
	   // cout<<"\n";
	   // for(int i = 0; i < max(2 * odddepth + 1, 2 * evendepth - 1)/*n - noofpathnodes*/; i++)
	    // we take account of removing nodes so that we can count if all 
	    // undesired nodes are removed and then break the loop
	    // we still wont be able to figure when to stop, since some {0, 1}
	    // are necessary, dont want hectic to add up later and ignore it now.
	    
	    // ohh shit, i have now understood that all nodes except starting
	    // and destination must be broken. Late but Gr8;
	   // unordered_map<int, int, custom_hash> removingnodes;
	    int nodesremoved = 0;
	    int nodestoberemoved = notpathnode.size();
	    int icpy;
	    for(int i = 0; i < 3 * n - noofpathnodes - 1 and nodesremoved < nodestoberemoved; i++)
	    {
	       // if(ispathnode[i]) continue;
	        if(currdep % 2)
	        {
	            if(evenleaf.empty())
	            {
	               // cout<<",";
	                res.push_back({0, 0});
	                currdep++;
	                continue;
	            }
	           // cout<<"'";
	            int evenleafnode = (evenleaf.begin()) -> first;
	            res.push_back({2, evenleafnode});
	            evenleaf.erase(evenleaf.begin());
	            nodesremoved++;
	            for(auto &x : edges[evenleafnode])
	            {
	                deg[x]--;
	               // if(deg[x] == 1 and !ispathnode[x])
	                if(deg[x] == 1 and x != 0 and x != n - 1)
	                {
	                    if(depth[x] % 2) oddleaf[x]++;
	                    else evenleaf[x]++;
	                }
	            }
	        }
	        else
	        {
	            if(oddleaf.empty())
	            {
	               // cout<<".";
	                res.push_back({0, 0});
	                currdep++;
	                continue;
	            }
	           // cout<<"-";
	            int oddleafnode = (oddleaf.begin()) -> first;
	            res.push_back({2, oddleafnode});
	            oddleaf.erase(oddleaf.begin());
	            nodesremoved++;
	            for(auto &x : edges[oddleafnode])
	            {
	                // do we need to make another vis array here for updating deg consistently ??
	                // no since they would only be decreasing, if more updates would happen
	                // it would become <= 0, hence no problem since it wont be again 1
	                // also if one of the nodes got removed, it means it was already 1,
	                // then updating it in next node anyway will make it <= 0
	                deg[x]--;
	               // if(deg[x] == 1 and !ispathnode[x])
	                if(deg[x] == 1 and x != 0 and x != n - 1)
	                {
	                    if(depth[x] % 2) oddleaf[x]++;
	                    else evenleaf[x]++;
	                }
	            }
	        }
	        if(nodesremoved == nodestoberemoved and currdep % 2)
	        res.push_back({0, 1});
	        currdep++;
	    }
	    // res only contains type 2 operations, fill type 1 carefully
	    
	    // i dont know why we are getting 1, the first time only, before type 2
	    // i need to cout res for now 
	    // yes there is a {0, 0} at start in res, i dont know why
	    vector<pair<int, int>> outputres;
	    int ressize = res.size();
	    
	   // cout<<"res starts\n";
	   // for(auto &x : res)
	   // cout<<x.first<<" "<<x.second+1<<"\n";
	   // cout<<"res ends\n";
	    
	    int start = 0;
	   // for(start = 0; start < ressize; start++)
	   // if(res[start].first == 0) continue;
	   // else break;
	   
	    // dont put {1, 0} after last type 2 operation in outputres
	    int last2typeidx = ressize;
	    for(int i = ressize - 1; i >= 0; i--)
	    if(res[i].first == 2)
	    {
	        last2typeidx = i;
	        break;
	    }
	    
	    for(int i = start; i < ressize; i++)
	    {
	        pair<int, int> pr = res[i];
	        if(pr.first == 2)
	        {
	            outputres.push_back({2, pr.second});
	            if(i != last2typeidx)
	            outputres.push_back({1, 0});
	        }
	        else if(pr.first == 0)
	        {
	            outputres.push_back({1, 0});
	            continue;
	        }
	    }
	    
	   // for(int i = 1; i < noofpathnodes; i++)
	   // there is only 2 nodes : 0 and n - 1 left at last
	   // outputres.push_back({1, 0});
	   
	   // now only pathnodes are left, 
	   // hence step one by one and delete previous, starting from 0
	   function<void(int, int)> dfspath = [&](int node, int parent)
	   {
	       if(node == n - 1)
	       return;
	       for(auto &child : edges[node])
	       {
	           if(child == parent) continue;
	           if(pathnode[child] > 0)
	           {
	               outputres.push_back({1, 0});
	               outputres.push_back({2, node});
	               dfspath(child, node);
	           }
	       }
	   };
	   dfspath(0, -1);
	   outputres.push_back({1, 0});
	   // cout<<"outputres begins\n";
	   // for(auto &x : outputres)
	   // cout<<x.first<<" "<<x.second+1<<"\n";
	   // cout<<"outputres ends \n";
	    
	   // cout<<"Case #"<<tt<<" :\n";
	    cout<<outputres.size()<<"\n";
	    for(auto &x : outputres)
	    {
	        if(x.first == 1) cout<<1<<"\n";
	       // else if(x.first == 0) cout<<1<<"\n";
	        else cout<<2<<" "<<x.second + 1<<"\n";
	    }
	}
}