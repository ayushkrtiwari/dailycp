// https://codeforces.com/group/DeilFl9Bhi/contest/329185/problem/D

#include<bits/stdc++.h>
using namespace std;

// void solve()
// {
//     size_t n;
//     cin>>n;
//     vector<int> a(n);
//     for(auto &x : a)
//     cin>>x;
//     int x = 0;
//     for(auto z = --a.end(); z > a.begin(); z--)
//     {
//         int y = *z - a[x];
//         auto it = upper_bound(a.begin() + 1, a.end(), y);
//         if(it < z) 
//         {
//             cout<<a[x]<<" "<<*it<<" "<<*z<<"\n";
//             return;
//         }
//     }
//     cout<<-1<<"\n";
//     return;
// }

void solve()
{
    size_t n;
    cin>>n;
    vector<int> a(n);
    for(auto &x:a) cin>>x;
    if(a[0] + a[1] <= a[n - 1])
    cout<<"1 2 "<<n<<"\n";
    else
    cout<<"-1\n";
}

int main()
{
    int t;
    cin>>t;
    while(t--)
    solve();
}