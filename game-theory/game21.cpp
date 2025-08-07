// https://cses.fi/problemset/task/2208

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
        vector<int> x(n);
        for(auto &e : x)
        cin>>e;
        bool firstwin = false;
        for(auto &e : x)
        if(e % 2)
        {
            firstwin = true;
            break;
        }
        cout<<(firstwin ? "first\n" : "second\n");
    }
}