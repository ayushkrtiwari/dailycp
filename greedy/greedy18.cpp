// https://atcoder.jp/contests/abc137/tasks/abc137_d

// Exchange Argument, Sorting
// Trick: You need to take only jobs which has return time <= M

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