// https://codeforces.com/problemset/problem/2089/A


#include<bits/stdc++.h>
using namespace std;
const int M = 1e5 + 5;
vector<int> spf(M);

void spff()
{
    spf[0] = 1;
    spf[1] = 0;
    for(int i = 2; i < M; i++)
    spf[i] = i;
    for(int i = 2; i < M; i++)
    {
        if(spf[i] == i)
        {
            for(int j = 2*i; j < M ; j += i)
            {
                if(spf[j] == j)
                {
                    spf[j] = i;
                }
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    spff();
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        int p;
        // Bertlande's theorem
        for(int i = n/2; i <= n; i++)
        if(spf[i] == i)
        {
            p = i;
            break;
        }
        int mxused = p, mnused = p;
        cout<<p<<" ";
        for(int i = 1; i <= n; i++)
        {
            if(p - i < 1 or p + i > n)
            break;
            cout<<p - i<<" ";
            cout<<p + i<<" ";
            mnused = p - i;
            mxused = p + i;
        }
        while(mnused > 1)
        {
            mnused--;
            cout<<mnused<<" ";
        }
        while(mxused < n)
        {
            mxused++;
            cout<<mxused<<" ";
        }
        cout<<"\n";
    }
}