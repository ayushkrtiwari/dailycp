// https://www.hackerrank.com/contests/5-days-of-game-theory/challenges/powers-of-two-game

#include<bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    // Put this whenever I/O are in millions
    int t;
    cin>>t;
    while(t--)
    {
        int n; cin>>n;
        if(n % 8) cout<<"First\n";
        else cout<<"Second\n";
    }
    return 0;
}