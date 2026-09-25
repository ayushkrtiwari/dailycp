// https://codeforces.com/contest/1854/problem/A1

// https://codeforces.com/contest/1854/problem/A2

// Trick: Do not double till value above 20, but till it becomes absolute max of all

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
        vector<int> a(n);
        for(auto &x:a) cin>>x;
        int cntn = 0, cntp = 0;
        for(auto &x:a)
        if(x > 0) cntp++;
        else if(x < 0) cntn++;
        // vector<int> res;
        if(cntn == 0 and cntp == 0)
        cout<<0<<"\n";
        else if(cntn == 0)
        {
            cout<<n - 1<<"\n";
            for(int i = 0; i < n - 1; i++)
            cout<<i + 2<<" "<<i + 1<<"\n";
        }
        else if(cntp == 0)
        {
            cout<<n - 1<<"\n";
            for(int i = n - 1; i > 0; i--)
            cout<<i<<" "<<i + 1<<"\n";
        }
        else
        {
            int p, q;
            p = 0, q = 0;
            int maxp = 0, posp = -1, maxn = 0, posn = -1;
            for(int i = 0; i < n; i++)
            {
                if(a[i] < maxn) maxn = a[i], posn = i;
                if(a[i] > maxp) maxp = a[i], posp = i;
            }
            while(maxp < abs(a[posn]))
            {
                p++;
                maxp *= 2;
            }
            while(abs(maxn) < a[posp])
            {
                q++;
                maxn *= 2;
            }
            int totalp = p + cntn + n - 1; // doing all positive
            int totaln = q + cntp + n - 1; // doing all negative
            if(totalp < totaln)
            {
                cout<<totalp<<"\n";
                while(p--)
                cout<<posp + 1<<" "<<posp + 1<<"\n";
                for(int i = 0; i < n; i++)
                if(a[i] < 0)
                cout<<i + 1<<" "<<posp + 1<<"\n";
                for(int i = 0; i < n - 1; i++)
                cout<<i + 2<<" "<<i + 1<<"\n";
            }
            else
            {
                cout<<totaln<<"\n";
                while(q--)
                cout<<posn + 1<<" "<<posn + 1<<"\n";
                for(int i = 0; i < n; i++)
                if(a[i] > 0)
                cout<<i + 1<<" "<<posn + 1<<"\n";
                for(int i = n - 1; i > 0; i--)
                cout<<i<<" "<<i + 1<<"\n";
            }
        }
    }
}