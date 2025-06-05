// जय श्री राम                              JAI SHREE RAM

// https://www.hackerearth.com/practice/data-structures/disjoint-data-strutures/basics-of-disjoint-data-structures/practice-problems/algorithm/motu-and-patlu-2-d108529a/

// DSU, String Transitivity
// Map too will work (Q log Q), 2D array (676 * Q) or better optimized
// Miss point: If A can be changed to B without any cost, B to C without any cost, then A can be changed to C without any cost
// Thus, we are distributing them into class/groups

#include<bits/stdc++.h>
using namespace std;

int findparent(int x,vector<int> &parent)
{
	if(x==parent[x]) return x;
	return parent[x] = findparent(parent[x],parent);
}

void merge(int a,int b, vector<int> &parent, vector<int> &size)
{
	int parenta = findparent(a,parent);
	int parentb = findparent(b,parent);
	if(parenta==parentb) return;
	if(size[parenta]<size[parentb])
	swap(parenta,parentb);
	size[parenta]+=size[parentb];
	parent[parentb]=parenta;
}

int main() 
{
	int n;
	cin>>n;
	vector<int> parent(26);
	iota(parent.begin(),parent.end(),0);
	vector<int> size(26,1);
	string s;
	cin>>s;
	int q;
	cin>>q;
	vector<vector<int>> v(26,vector<int>(26,0));
	for(int i=0;i<26;i++)
	for(int j=0;j<26;j++)
	v[i][j]=0;

	for(int i=0;i<n/2;i++)
	if(s[i]!=s[n-i-1])
	v[s[i]-'a'][s[n-i-1]-'a']++;
	
	while(q--)
	{
		int qt;
		cin>>qt;
		qt--;
		if(qt)
		{
			int coinsrequired=0;
			for(int i=0;i<26;i++)
			for(int j=0;j<26;j++)
			if(findparent(i,parent)!=findparent(j,parent))
			coinsrequired+=v[i][j];
			cout<<coinsrequired<<"\n";
		}
		else
		{
			char a,b;
			cin>>a>>b;
			if(a!=b)
			{
				merge((int)(a-'a'),(int)(b-'a'),parent,size);
			}
		}
	}
}