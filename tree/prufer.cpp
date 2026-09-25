// https://cses.fi/problemset/task/1134

// More about prufer code :
// Prufer code means prufer array corresponding to the tree
// If a node has degree D in graph, it will have D - 1 degree of freq in prufer code
// Leaves never appear on prufer code
// Every prufer code is unique, that is each tree has unique prufer, and each prufer has only one corresponding tree.
// Thus if you want to generate random tree, just take a random array permutation, and convert it to prufer tree.
// No of labelled N node tree = N ** (N - 2), Cayley's Formula
// N node tree <=> (N - 2) size prufer code

// Q. Given N nodes and for each node its degree count in tree, 
// how many different spanning trees can we build while maintaining the degree count of each node
// Soln. Create freq array and just permute the prufer code and generate tree for each prufer code.
// The mathematical formula cant be written here, hence refer the video linked in resources

// Q. Given k-component disconnected graph of n nodes and m edges. 
// Find out no of ways of connecting the graph using k - 1 edges
// Soln. Refer cp-algorithms prufer section for the idea.

#include <bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
    int n;
    cin>>n;
    vector<int> prufer(n - 2);
    vector<int> freq(n, 0);
    for(auto &x:prufer) 
    {
        cin>>x;
        x--; // converting to 0-indexed
        freq[x]++;
    }
    priority_queue<int, vector<int>, greater<int>> leaf; // min heap
    // can use set too
    for(int i = 0; i < n; i++)
    if(freq[i] == 0) leaf.emplace(i);
    
    vector<vector<int>> tree;
    tree.resize(n);
    
    function<void(int, int)> addedge = [&](int u, int v)
    {
        // u++, v++; // restoring nodes to 1-indexed
        tree[u].push_back(v);
        // tree[v].push_back(u);
    };
    
    // size_t used to avoid warning of different integer type comparison
    // since .size() returns integer type size_t
    size_t i = 0;
    // Do not use while(leaf.size() > 2), since this condition will fail
    // Remember: No of leaf = No of elements in prufer array.
    // When there are atleast two elements with freq == 0, but there are more elements in graph, then this fails
    // or say, initially leaf has n elements, then they directly are added with edges,
    // but we have still length of prufer array greater than n - 2 then it's wrong, 
    // since other elements will come later in leaf when their freq == 0 on usage.
    while(i < prufer.size())
    {
        int u = leaf.top();
        leaf.pop();
        int v = prufer[i];
        freq[v]--;
        if(freq[v] == 0) leaf.emplace(v);
        addedge(u, v);
        i++;
    }
    int u = leaf.top();
    leaf.pop();
    int v = leaf.top();
    leaf.pop();
    addedge(u, v);
    
    // function<void(int)> print = [&](int x)
    // {
    //     cout<<x + 1<<" ";
    // };
    
    for(int node = 0; node < n; node++)
    {
        for(auto &nbour: tree[node])
        cout<<node + 1<<" "<<nbour + 1<<"\n";
    }
}