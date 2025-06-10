// जय श्री राम  JAI SHREE RAM

// https://atcoder.jp/contests/abc137/tasks/abc137_d

// Exchange Argument, Sorting
// Trick: You need to take only jobs which has return time <= M
// Create a 2D vector where ith row stores work which must be completed by (M - A)th day
// Now use priority queue and travel backwards and store till that day all the rewards and pick the max reward of them all
// Forward Traversal creates a gap, since say, if you can pick a work on 3rd day, then you can also pick it at 1st,2nd days
// but you are not able to push it into priority queue before 3rd day and thus if (1,5),(2,5),(3,10),(3,10): M = 3
// Forward Traversal will give result as 20 while Backward Traversal gives 25

#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,m;
    cin>>n>>m;
    vector<pair<int,int>> AR(n);
    for(auto &x:AR)
    cin>>x.first>>x.second;
    vector<vector<int>> deadlineday(m);
    for(auto x: AR)
    if (m >= x.first)
    deadlineday[m - x.first].push_back(x.second);
    priority_queue<int> pq;
    long long totalreward = 0;
    for(int i = m - 1; i >= 0; i--)
    {
        for(auto rew:deadlineday[i])
        pq.push(rew);
        if(!pq.empty())
        {
        totalreward += pq.top();
        pq.pop();
        }
    }
    cout<<totalreward<<"\n";
}