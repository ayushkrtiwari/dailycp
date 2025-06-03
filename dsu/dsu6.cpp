// https://www.hackerearth.com/practice/data-structures/disjoint-data-strutures/basics-of-disjoint-data-structures/practice-problems/algorithm/killjee-and-cities-8a82b6fe/

// Simple DSU
// Keep track of connected components

#include<bits/stdc++.h>
using namespace std;

int findparent(int a,vector<int>&parent)
{
	if(parent[a]==a) return a;
	return parent[a]=findparent(parent[a],parent);
}

void merge(int a,int b,vector<int> &parent,vector<int> &size,int &n)
{
	int parenta=findparent(a,parent);
	int parentb=findparent(b,parent);
	if(parenta==parentb) return;
	n--;
	if(size[parenta]<size[parentb])
	swap(parenta,parentb);
	size[parenta]+=size[parentb];
	parent[parentb]=parenta;
}

int main() {
	int n;
	cin>>n;

	vector<int> citiesgroup(n);
	vector<int> parent(n);
	iota(parent.begin(),parent.end(),0);
	iota(citiesgroup.begin(),citiesgroup.end(),0);
	vector<int> size(n,1);

	int noofgroups=n-1;
	int m;
	cin>>m;
	int s;
	cin>>s;
	// cout<<noofgroups<<"\n";
	while(m--)
	{
		int a,b;
		cin>>a>>b;
		merge(a,b,parent,size,noofgroups);
	}
	int q;
	cin>>q;
	// int s;
	cin>>s;
	// cout<<noofgroups<<"\n";
	while(q--)
	{
		int a,b;
		cin>>a>>b;
		merge(a,b,parent,size,noofgroups);
		cout<<noofgroups<<" ";
	}
}