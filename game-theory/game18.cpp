// https://cses.fi/problemset/task/1098

// Grundy value of each pile : x % 4
// nim sum of grundy values of all piles gives first player as winner if nim != 0 else second

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
        for(auto &x : v)
        {
            cin>>x;
            x %= 4;
        }
        int nim = 0;
        for(auto &x : v)
        nim ^= x;
        if(nim) cout<<"first\n";
        else cout<<"second\n";
    }
}