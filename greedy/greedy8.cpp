// https://codeforces.com/contest/1203/problem/F1

// Trick: Divide into two vectors, one having positive rating change, other having negative rating change
// Rest all given below

#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    int r;
    cin>>r;
    vector<pair<int,int>> ab(n);
    for(auto &x:ab) cin>>x.first>>x.second;
    vector<pair<int,int>> positive,negative;
    for(auto &x: ab)
    if(x.second<0) negative.push_back(x);
    else positive.push_back(x);
    sort(positive.begin(),positive.end(),[](const pair<int,int>&a, const pair<int,int> &b)
    {
        return a.first<b.first;
        // since r will always increase due to all positive a2 and b2 in positive vector
        // hence we only need to check for lower cutoff values first to offer so that
        // we can get max value of r after doing all operations with less cutoffs
    });
    sort(negative.begin(),negative.end(),[](const pair<int,int>&a, const pair<int,int> &b)
    {
        return a.first+a.second > b.first+b.second; 
        // for 1->2, r will have atleast value a1, thus a1 - a2 will be its next value
        // for 2->1, r will have atleast value b1, thus b1 - b2 will be its next value
        // whether it passes cutoff, we will check this by iterating later
        // so we check in which order we can have greater value of r after doing the 
        // operation. Thus, the equation: a1 - a2 > b1 - b2 but since both a2 and b2
        // are already negative, we should use +, hence a1 + a2 > b1 + b2
    });
    int ps = positive.size();
    int ns = negative.size();
    
    bool ispossible = true;
    for(int i=0;i<ps;i++)
    if(r>=positive[i].first) r+=positive[i].second;
    else
    {
        ispossible = false;
        break;
    }
    if(ispossible)
    for(int i=0;i<ns;i++)
    if(r>=negative[i].first) 
    {
        r+=negative[i].second;
        if(r<0)
        {
            ispossible = false;
            break;
        }
    }
    else
    {
        ispossible = false;
        break;
    }
    // for(auto i:negative)cout<<i.first<<" "<<i.second<<"\n";
    if(ispossible)
    cout<<"YES\n";
    else
    cout<<"NO\n";
}