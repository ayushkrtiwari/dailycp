// https://www.hackerearth.com/challenges/competitive/april-circuits-20/algorithm/happy-segments-e290faa6/

#include<bits/stdc++.h>
using namespace std;

const int blocks = 7e2;

struct Query
{
	int x, y, idx;
};

auto mo_cmp = [](Query &qa, Query &qb)
{
	if(qa.x/blocks != qb.x/blocks) return qa.x < qb.x;
	return qa.x/blocks & 1 ? qa.y > qb.y : qa.y < qb.y;
};

int main()
{
	int n,m,q;
	cin>>n>>m;
	vector<int> a(n), h(m);
	for(auto &x: a) cin>>x;
	for(auto &x: h) cin>>x;
	cin>>q;
	vector<Query> query(q);
	for(int i = 0; i < q; i++)
	{
		cin>>query[i].x>>query[i].y;
		query[i].x--, query[i].y--;
		query[i].idx = i;
	}
	sort(query.begin(),query.end(),mo_cmp);
	vector<int> freq(m+1, 0);
	int happycnt = 0;
	int distinctinsubarrcnt = 0;
	auto add = [&](int idx)
	{
		int val = a[idx];
		val--;
		if(freq[val] == h[val]) happycnt--;
		if(freq[val] == 0) distinctinsubarrcnt++;
		freq[val]++;
		if(freq[val] == h[val]) happycnt++;
	};
	auto rmove = [&](int idx)
	{
		int val = a[idx];
		val--;
		if(freq[val] == h[val]) happycnt--;
		freq[val]--;
		if(freq[val] == 0) distinctinsubarrcnt--;
		if(freq[val] == h[val]) happycnt++;
	};
	int currL = 0, currR = -1;
	vector<int> res(q);
	for(auto &q: query)
	{
		while(currL < q.x) rmove(currL++);
		while(currL > q.x) add(--currL);
		while(currR < q.y) add(++currR);
		while(currR > q.y) rmove(currR--);
		res[q.idx] = (happycnt == distinctinsubarrcnt);
	}
	for(auto r: res)
	cout<<r<<"\n";
}