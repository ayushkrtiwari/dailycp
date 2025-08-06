// https://cses.fi/problemset/task/1099

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
        vector<int> p(n);
        for(auto &x : p)
        {
            cin>>x;
            // x %= 2;
        }
        int nim = 0;
        for(int i = 1; i < n; i++)
        {
            if(i % 2)
            nim ^= p[i];
        }
        if(nim) cout<<"first\n";
        else cout<<"second\n";
    }
}