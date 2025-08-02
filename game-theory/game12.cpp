// https://www.hackerrank.com/contests/5-days-of-game-theory/challenges/fun-game

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
// # define int long long

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        vector<pair<int,int>> ab(n);
        for(auto &x : ab)
            cin>>x.first;
        for(auto &x : ab)
            cin>>x.second;
        auto cmp = [&](auto &x1, auto &x2)
        {
            return x1.first + x1.second > x2.first + x2.second;
        };
        sort(ab.begin(), ab.end(), cmp);
        int a(0), b(0);
        for(int i = 0; i < n; i++)
        {
            if(i & 1) b += ab[i].second;
            else a += ab[i].first;
        }
        // cout<<a<<" "<<b<<" ";
        if(a > b) cout<<"First\n";
        else if(a < b) cout<<"Second\n";
        else cout<<"Tie\n";
    }
    return 0;
}