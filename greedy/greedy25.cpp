// https://codeforces.com/contest/1889/problem/B

// Topic: Exchange Argument, Sorting on unique property
// Trick: Separation of Variables fyi, where you split the equation into 2 parts, 
// the 2 being independent of each other, so that only either the LHS or RHS is dependent on i
// while the other part is independent of it
// Formalize/simplify the statement.
// Don't be afraid to do a little algebra. Those are essential skills.

#include<bits/stdc++.h>
using namespace std;
# define int long long int

int32_t main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,c;
        cin>>n>>c;

        // INITIAL WRONG APPROACH OF TAKING edges(1,i) but sorted by a[i]/i

        // vector<pair<int,int>> a(n);
        // for(int i = 0; i < n; i++)
        // {
        //     cin>>a[i].first;
        //     a[i].second = i + 1;
        // }
        // auto cmp = [&](auto &pa, auto &pb)
        // {
        //     if(pa.first * pb.second == pb.first * pa.second) return pa.second < pb.second;
        //     return pa.first * pb.second < pb.first * pa.second;
        // };
        // sort(a.begin(), a.end(), cmp);
        // bool possible = true;
        // int sum = a[0].first;
        // for(int i = 1; i < n; i++)
        // {
        //     if(sum < 1LL * a[i - 1].second * a[i].second * c)
        //     {
        //         possible = false;
        //         break;
        //     }
        //     else
        //     sum += a[i].first;
        // }
        
        // RIGHT APPROACH
        
        vector<int> a(n);
        for(auto &x:a)
        cin>>x;
        bool possible = true;
        int sum = a[0];
        vector<int> d(n);
        for(int i = 1; i < n; i++)
        d[i] = (i + 1) * c - a[i];
        vector<pair<pair<int,int>,int>> pr(n);
        for(int i = 1; i < n; i++)
        {
            pr[i].first.first = a[i];
            pr[i].first.second = d[i];
            pr[i].second = i + 1;
        }
        
        // You can choose any of the sorting methods below:
        
        // METHOD 1:

        // sort(pr.begin() + 1, pr.end(), [](auto &qa, auto &qb)
        // {
        //     if(qa.first.second == qb.first.second) return qa.first.first > qb.first.first;
        //     return qa.first.second < qb.first.second;
        // });
        
        // METHOD 2:

        sort(pr.begin() + 1, pr.end(), [c](auto &qa, auto &qb)
        {
            if(qa.second * c - qa.first.first == qb.second * c - qb.first.first) 
            return qa.first.first > qb.first.first;
            // The equality above is optional
            return qa.second * c - qa.first.first < qb.second * c - qb.first.first;
        });

        // cout<<a[0]<<","<<c-a[0]<<","<<1<<" ";
        // for(int i = 1; i < n; i++) cout<<pr[i].first.first<<","<<pr[i].first.second<<","<<pr[i].second<<" ";
        
        for(int i = 1; i < n; i++)
        {
            sum += pr[i].first.first;
            if(sum < pr[i].second * c)
            {
                possible = false;
                break;
            }
        }
        
        if(possible)
        cout<<"YES\n";
        else
        cout<<"NO\n";
    }
}