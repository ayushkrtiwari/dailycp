// https://codeforces.com/contest/2111/problem/E

// Exchange argument
// Trick: Only do for: (x,y): (b,a),(c,b),(c,a)
// Just the thing you miss is: you can do b->c->a
// Also that while doing c->b->a count this operation only if (c,b) comes before(b,a). Similarly for b->c->a

#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,q;
        cin>>n>>q;
        string s;
        cin>>s;
        int cntba=0,cntbc=0,cntca=0,cntcb=0,cntbca=0,cntcba=0;
        while(q--)
        {
            char x,y;
            cin>>x>>y;
            if(x=='b' and y=='a')
            {
                cntba++;
                if(cntcb>cntcba)
                cntcba++;
            }
            else if(x=='b' and y=='c') cntbc++;
            else if(x=='c' and y=='a')
            {
                cntca++;
                if(cntbc>cntbca)
                cntbca++;
            }
            else if(x=='c' and y=='b') cntcb++;
        }
        // cout<<cntba<<" "<<cntbc<<" "<<cntca<<" "<<cntcb<<" "<<cntbca<<" "<<cntcba<<"\n";
        for(int i=0;i<n;i++)
        {
            if(s[i]=='b')
            {
                if(cntba)
                {
                    s[i]='a';
                    cntba--;
                }
                else if(cntca and cntbc and cntbca) // FYI, both cntca and cntbc can be 0 without cntbca being 0
                {
                    s[i]='a';
                    cntbca--;
                    cntca--;
                    cntbc--;
                }
            }
            else if(s[i]=='c')
            {
                if(cntca)
                {
                    s[i]='a';
                    cntca--;
                }
                else if(cntcb and cntba and cntcba) // FYI, both cntcb and cntba can be 0 without cntcba being 0
                {
                    s[i]='a';
                    cntcb--,cntba--;
                    cntcba--;
                }
                else if(cntcb)
                {
                    s[i]='b';
                    cntcb--;
                }
            }
        }
        for(auto ch:s)
        cout<<ch;
        cout<<"\n";
    }
}