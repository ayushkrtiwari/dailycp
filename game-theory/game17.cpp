// https://cses.fi/problemset/task/1730

// nim sum of all piles gives first player as winner when nim sum != 0 else second

#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        vector<int> v(n);
        for(auto &x : v) cin>>x;
        int nim = 0;
        for(auto &x : v) nim ^= x;
        if(nim) cout<<"first\n";
        else cout<<"second\n";
    }
}