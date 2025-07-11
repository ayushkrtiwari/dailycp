// जय श्री राम  JAI SHREE RAM

// https://www.spoj.com/problems/DQUERY/

// MO Algorithm, Distinct Elements in Range Query
// This is easy version for elements upto 1e5
// Hard Version with n upto 1e9 requires coordinate compression
// Alternative method for hard version is using next and previous occurence vector for each indices

#include<bits/stdc++.h>
using namespace std;

const int blocks = 7e2;

struct Query
{
	int x, y, idx;
};

// 0-indexed blocks
// Even blocks have forward traversal, odd have backward
auto mo_cmp = [](Query &qa, Query &qb)
{
	if(qa.x/blocks != qb.x/blocks) return qa.x < qb.x;
	return qa.x/blocks & 1 ? qa.y > qb.y : qa.y < qb.y;
};

int main()
{
	int n,q;
	cin>>n;
	vector<int> a(n);
	for(auto &x: a) cin>>x;
	cin>>q;
	vector<Query> query(q);
	for(int i = 0; i < q; i++)
	{
		cin>>query[i].x>>query[i].y;
		query[i].x--, query[i].y--;
		query[i].idx = i;
	}
	sort(query.begin(),query.end(),mo_cmp);
	vector<int> freq(1000005, 0);
	int distinctinsubarrcnt = 0;
	auto add = [&](int idx)
	{
		if(freq[a[idx] - 1] == 0) distinctinsubarrcnt++;
		freq[a[idx] - 1]++;
	};
	auto rmove = [&](int idx)
	{
		freq[a[idx] - 1]--;
		if(freq[a[idx] - 1] == 0) distinctinsubarrcnt--;
	};
	int currL = 0, currR = -1;
	vector<int> res(q);

	// Generally, remove and add takes O(log N) or O(1) in MO
	// answer takes O(1)
	for(auto &q: query)
	{
		while(currL < q.x) rmove(currL++);
		while(currL > q.x) add(--currL);
		while(currR < q.y) add(++currR);
		while(currR > q.y) rmove(currR--);
		res[q.idx] = distinctinsubarrcnt;
	}
	for(auto r: res)
	cout<<r<<"\n";
}