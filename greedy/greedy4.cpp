#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	vector<pair<int,int>> movie(n);
	for(auto &x:movie)
	cin>>x.first>>x.second;
	sort(movie.begin(),movie.end(),[](const pair<int,int>&A, const pair<int,int>&B){return A.second<B.second;});
	int cnt = 0;
	int last = 0;
	int i=0;
	while(i<n)
	{
		if(movie[i].first>=last)
		{
			cnt++;
			last = movie[i].second;
		}
		i++;
	}
	cout<<cnt<<"\n";
}
