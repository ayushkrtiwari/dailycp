

#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	vector<vector<long long>> startend(n,vector<long long>(3));
	vector<pair<long long, long long>> res;
	
	for(int i = 0; i < n; i++)
	{
	    long long x,y;
	    cin>>x>>y;
	    startend[i][0] = x;
	    startend[i][1] = y;
	    startend[i][2] = i;
	}
	
	sort(startend.begin(),startend.end());
	
	priority_queue<pair<long long,long long>, vector<pair<long long,long long>>, greater<pair<long long,long long>>> pq;
	
	long long cnt = 0, mxcnt = 1;
	
	for(int i = 0; i < n; i++)
	{
	    if(pq.empty())
	    {
	        pq.push({startend[i][1], 1});
	        cnt = 1;
	        res.push_back({cnt, startend[i][2]});
	       // cout<<".";
	    }
	    else
	    {
	        auto endtime_room = pq.top();
	        if(startend[i][0] <= endtime_room.first)
	        {
	            cnt = mxcnt + 1;
	            mxcnt = max(mxcnt, cnt);
	            res.push_back({cnt, startend[i][2]});
	            pq.push({startend[i][1], cnt});
	           // cout<<",";
	        }
	        else
	        {
	            pq.pop();
	            cnt = endtime_room.second;
	            res.push_back({cnt, startend[i][2]});
	            pq.push({startend[i][1], cnt});
	           // cout<<";";
	        }
	    }
	}
	sort(res.begin(),res.end(),[](const pair<long long, long long> &A, pair<long long, long long> &B){
	    return A.second < B.second;
	});
	cout<<mxcnt<<"\n";
	for(auto room: res)
	cout<<room.first<<" ";
}