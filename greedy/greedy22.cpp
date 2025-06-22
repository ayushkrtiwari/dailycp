// https://codeforces.com/problemset/problem/2052/A

#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    vector<int> c(n);
    for(auto &x: c)
    cin>>x;
    vector<pair<int,int>> res;
    
    // 5 1 2 4 3
    
    for(int i = 0; i < n; i++) // if traversing forward, swap elements backward so you dont encounter them again
    {
        while(i > 0 and c[i - 1] < c[i]) // swap elements if they are in wrong order else break out. This will bring them in correct order(desc)
        {
            res.push_back({c[i - 1], c[i]});
            swap(c[i - 1], c[i]);
            i--;
        }
    }
    
    // 5 4 3 2 1
    
    for(int i = n - 1; i >= 0; i--)
    {
        while(i < n - 1 and c[i + 1] < c[i])
        {
            res.push_back({c[i], c[i + 1]});
            swap(c[i], c[i + 1]);
            i++;
        }
    }
    
    // 1 2 3 4 5
    
    cout<<res.size()<<"\n";
    
    for(auto r = res.rbegin(); r < res.rend(); r++)
    cout<<r->first<<" "<<r->second<<"\n";
}