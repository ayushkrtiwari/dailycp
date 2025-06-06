// // जय श्री राम                              JAI SHREE RAM

// https://www.hackerearth.com/practice/data-structures/disjoint-data-strutures/basics-of-disjoint-data-structures/practice-problems/algorithm/a-69-5718e916/




#include <bits/stdc++.h>
using namespace std;
# define int long long

int findparent(int a,vector<int> &parent)
{
	if(parent[a]!=a)
	{
		parent[a]=findparent(parent[a],parent);
	}
	return parent[a];
}

void merge(int a,int b,vector<int> &parent,vector<int> &size)
{
	int parenta=findparent(a,parent);
	int parentb=findparent(b,parent);
	if(size[parenta]<size[parentb])
	swap(parenta,parentb);
	parent[parentb]=parenta;
	size[parenta]+=size[parentb];
}

int dist(int i,int j,vector<pair<int,int>> &points)
{
	int xi=points[i].first;
	int yi=points[i].second;
	int xj=points[j].first;
	int yj=points[j].second;
	return ((xi-xj)*(xi-xj)+(yi-yj)*(yi-yj));
}

int32_t main() 
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin>>n;
	vector<pair<int,int>> points(n);
	for(auto &x:points)
	cin>>x.first>>x.second;
	vector<int> parent(n);
	vector<int> size(n,1);
	for(int i=0;i<n;i++)
	parent[i]=i;
	vector<pair<int,pair<int,int>>> pairdist;
	for(int i=0;i<n;i++)
	for(int j=i+1;j<n;j++)
	pairdist.push_back({dist(i,j,points),{i,j}});
	sort(pairdist.begin(),pairdist.end());
	int totaldist=0;
	for(auto i:pairdist)
	{
		if(findparent(i.second.first,parent)!=findparent(i.second.second,parent))
		{
			merge(i.second.first,i.second.second,parent,size);
			totaldist+=(i.first);
		}
	}
	cout<<totaldist<<"\n";
}
