// https://www.hackerrank.com/contests/5-days-of-game-theory/challenges/fun-game

// Greedy, Game Theory

// Simple Greedy Approach, as take a scenario, (A1, B1) (A2, B2)
// If P1 takes A1, then P2 takes B2, or if P1 takes A2, P2 takes B1
// For P1 to win, it needs to have the winning move. 
// Let's say winning move was P1 taking A1 : (A1 - B2) > (A2 - B1) => (A1 + B1) > (A2 + B2)
// This means we need to sort pairs in form of Ai + Bi and pick up greedily pairs with higher Ai + Bi

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