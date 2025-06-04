// https://www.hackerearth.com/practice/data-structures/disjoint-data-strutures/basics-of-disjoint-data-structures/practice-problems/algorithm/strengthen-their-bonding-6eeb0e01/

// Offline queries + Small to large merge

// Here merging takes place: on each merge size doubles at least, thus there can be at max log2(N) merges where N is max size

// Use set to maintain number of distinct colors

// Reverse the process: it is breaking process from forward while joining process from backward 
// hence store all queries and then process it backwards by merging using dsu.

// You will miss again: There may be some edges that never broke hence store those and merge before processing queries

#include<bits/stdc++.h>
using namespace std;

int findparent(int x,vector<int> &parent)
{
	if(x==parent[x]) return x;
	return parent[x]=findparent(parent[x],parent);
}

void merge(int a, int b, vector<int> &parent, vector<set<int>> &color)
{
	int parenta = findparent(a,parent);
	int parentb = findparent(b,parent);
	if(parenta==parentb) return;
	int parentacolorsize = color[parenta].size();
	int parentbcolorsize = color[parentb].size();
	if(parentacolorsize>parentbcolorsize)
	{
		for(auto colorb:color[parentb])
		color[parenta].insert(colorb);

		parent[parentb]=parenta;
	}
	else
	{
		for(auto colora:color[parenta])
		color[parentb].insert(colora);

		parent[parenta]=parentb;
	}
}

int main() 
{
	int n,m,q;
	cin>>n>>m>>q;
	vector<set<int>> color(n);
	vector<int> parent(n);
	iota(parent.begin(),parent.end(),0);
	vector<pair<int,int>> edges;
	for(int i=0;i<n;i++)
	{
		int x;
		cin>>x;
		color[i].insert(x);
	}
	while(m--)
	{
		int u,v;
		cin>>u>>v;
		u--,v--;
		edges.push_back({u,v});
		// merge(u,v,parent,color);
	}
	stack<pair<int,int>> query;
	set<pair<int,int>> edgestobreak;
	while(q--)
	{
		int qt;
		int xy;
		cin>>qt>>xy;
		if(qt==1)
		edgestobreak.insert(edges[xy-1]);
		query.push({qt,xy});  
	}
	set<pair<int,int>> edgeneverbroken;
	for(auto edge:edges)
	{
		if(edgestobreak.find(edge)==edgestobreak.end())
		edgeneverbroken.insert(edge);
	}
	for(auto edge:edgeneverbroken)
	{
		merge(edge.first,edge.second,parent,color);
	}
	vector<int> res;
	while(!query.empty())
	{
		auto e = query.top();
		query.pop();
		int type = e.first;
		if(type==1)
		{
			int edge = e.second;
			edge--;
			auto nodes = edges[edge];
			merge(nodes.first,nodes.second,parent,color);
		}
		if(type==2)
		{
			int node = e.second;
			node--;
			int parentnode = findparent(node,parent);
			res.push_back(color[parentnode].size());
		}
	}
	for(auto r=res.rbegin();r<res.rend();r++)
	cout<<*r<<"\n";
}