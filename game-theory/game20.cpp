// https://cses.fi/problemset/task/1729

// Just a bounded normal nim case, with exploring each possible transitions

#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n, k;
    cin>>n>>k;
    vector<int> p(k);
    for(auto &x : p) cin>>x;
    vector<int> winlose(n + 1, 0);
    for(int i = 1; i <= n; i++)
    {
        for(int step = 0; step < k; step++)
        {
            if(i - p[step] >= 0 and winlose[i - p[step]] == 0)
            {
                winlose[i] = 1;
                break;
            }
        }
    }
    for(int i = 1; i <= n; i++)
    if(winlose[i]) cout<<'W';
    else cout<<'L';
}