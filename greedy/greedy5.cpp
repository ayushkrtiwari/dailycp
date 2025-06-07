// https://codeforces.com/problemset/problem/2034/B

#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,m,k;
        cin>>n>>m>>k;
        string s;
        cin>>s;
        int cnt = 0;
        for(int i=0;i<n;i++)
        {
            // cout<<i<<":";
            bool isconsecutive0 = false;
            if(s[i]=='0')
            {
                isconsecutive0 = true;
                int steps;
                for(steps=0;steps<m;steps++)
                {
                    if(i+steps>=n or s[i+steps]=='1')
                    {
                        isconsecutive0 = false;
                        break;
                    }
                }
                i=i+steps-1;
            }
            int steps;
            // cout<<i<<"..";
            if(i<n and isconsecutive0 and s[i]=='0')
            {
                cnt++;
                for(steps=0;steps<k and i+steps<n;steps++)
                {
                    s[i+steps] = '1';
                }
                i = i + steps - 1 ;
            }
            // cout<<i<<". ";
        }
        cout<<cnt<<"\n";
    }
}