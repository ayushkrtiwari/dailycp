#include <bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
    int t;
    cin>>t;
    for(int tt = 1; tt <= t; tt++)
    {
        int n, k;
        cin>>n>>k;
        vector<int> a(n);
        for(auto &x : a) cin>>x;
        int x, y, z;
        x = y = z = -1;
        bool xpre, ypre, zpre;
        xpre = ypre = zpre = false;
        vector<bool> present(n + 1, false);
        for(auto &x : a) present[x] = true;
        for(int i = 1; i <= n; i++)
        {
            if(present[i]) continue;
            if(!xpre)
            {
                x = i;
                xpre = true;
                continue;
            }
            if(!ypre)
            {
                y = i;
                ypre = true;
                continue;
            }
            if(!zpre)
            {
                z = i;
                zpre = true;
                continue;
            }
        }
        if(x == -1)
        {
            for(int i = 0; i < n; i++)
            if(a[i] != a[n - 1])
            {
                x = a[i];
                xpre = true;
                break;
            }
        }
        if(y == -1)
        {
            for(int i = 0; i < n; i++)
            // if(a[i] != x)  this would fail at input : 1 2 1 : x = 3, y = 1, z = 2, means extra palindrome
            if(a[i] != x and a[i] != a[n - 1])
            {
                y = a[i];
                ypre = true;
                break;
            }
        }
        if(z == -1)
        {
            for(int i = 0; i < n; i++)
            if(a[i] != x and a[i] != y)
            {
                z = a[i];
                zpre = true;
                break;
            }
        }
        vector<int> xyz = {x, y, z};
        int i = 0;
        while(k--)
        {
            cout<<xyz[i++ % 3]<<" ";
        }
        cout<<"\n";
    }
}
