// https://www.hackerrank.com/contests/5-days-of-game-theory/challenges/day-2-poker-nim

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int t;
    cin>>t;
    while(t--)
    {
        int n,k;
        cin>>n>>k;
        vector<int> s(n);
        for(auto &x:s) cin>>x;
        int nim = 0;
        for(auto &x:s) nim ^= x;
        if(nim) cout<<"First\n";
        else cout<<"Second\n";
    }
    return 0;
}