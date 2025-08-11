// https://codeforces.com/group/DeilFl9Bhi/contest/329185/problem/C

#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int a, b, c;
        cin>>a>>b>>c;
        cout<<max(a, max(b, c))<<"\n";
    }
}