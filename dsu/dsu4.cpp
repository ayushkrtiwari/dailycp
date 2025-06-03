// https://www.hackerearth.com/practice/data-structures/disjoint-data-strutures/basics-of-disjoint-data-structures/practice-problems/algorithm/team-up-2-8dc5d882/

// Simple DSU question. 2 layer addition

// Keep from 1 to N, 2nd layer from N+1 to 2*N the parent

#include <bits/stdc++.h>
using namespace std;

int findparent(int a,vector<int> &parent)
{
	if(parent[a]==a) return a;
	return parent[a]=findparent(parent[a],parent);
}

void teammerge(int a,int b,vector<int> &parent,vector<int> &size,vector<int> &strength)
{
	int super_parent_a=findparent(a,parent);
	int super_parent_b=findparent(b,parent);
	if(super_parent_a==super_parent_b) return;
	if(size[super_parent_a]<size[super_parent_b])
	swap(super_parent_a,super_parent_b);
	size[super_parent_a]+=size[super_parent_b];
	strength[super_parent_a]+=strength[super_parent_b];
	parent[super_parent_b]=super_parent_a;
}

void individualmerge(int a,int b,vector<int>&parent,vector<int>&size,vector<int>&strength)
{
	int super_parent_a=findparent(a,parent);
	int super_parent_b=findparent(b,parent);
	if(super_parent_a==super_parent_b) return;
	size[super_parent_b]+=1;
	strength[super_parent_b]+=a;
	parent[a]=super_parent_b;
	size[super_parent_a]-=1;
	strength[super_parent_a]-=a;
}

int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,q;
		cin>>n>>q;
		vector<int> team(2*n+1);
		vector<int> size(2*n+1,1);
		vector<int> parent(2*n+1);
		vector<int> strength(2*n+1);
		for(int i=1;i<=n;i++)
		{
			parent[i+n]=i+n;
			parent[i]=i+n;
			strength[i]=i;
			strength[i+n]=i;
			size[i]=1;
			size[i+n]=1;
		}
		while(q--)
		{
			int qt;
			cin>>qt;
			if(qt==1)
			{
				int a,b;
				cin>>a>>b;
				if(findparent(a,parent)==findparent(b,parent)) continue;
				teammerge(a,b,parent,size,strength);
			}
			if(qt==2)
			{
				int a;
				cin>>a;
				int parenta=findparent(a,parent);
				cout<<size[parenta]<<" "<<strength[parenta]<<"\n";
			}
			if(qt==3)
			{
				int a,b;
				cin>>a>>b;
				individualmerge(a,b,parent,size,strength);
			}
		}
	}
}
