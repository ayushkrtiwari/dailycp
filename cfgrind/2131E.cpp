// https://codeforces.com/problemset/problem/2131/E

// solution not verified

#include <bits/stdc++.h>
using namespace std;
# define int long long

int32_t main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	// your code goes here
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        vector<int> a(n), b(n);
        for(auto &x : a) cin>>x;
        for(auto &x : b) cin>>x;
        vector<vector<int>> pos;
        // vector<int> index(n);
        
        vector<int> cpya = a;
        sort(cpya.begin(), cpya.end());
        cpya.erase(unique(cpya.begin(), cpya.end()), cpya.end());
        int cpyass = cpya.size();
        pos.resize(cpyass + 1);
        
        vector<int> cmpval(n);
        for(int i = 0; i < n; i++)
        cmpval[i] = lower_bound(cpya.begin(), cpya.end(), a[i]) - cpya.begin();
        
        map<int, int> index;
        for(int i = 0; i < n; i++)
        index[a[i]] = i;
        
        for(int i = 0; i < n; i++)
        pos[cmpval[i]].push_back(i);
        
        bool possible = true;
        
        vector<int> reachidx(n, n);
        for(int i = 0; i < n; i++)
        {
            if(index.find(a[i] ^ b[i]) == index.end()) 
            {
                possible = false;
                break;
            }
            vector<int> &x = pos[cmpval[index[a[i] ^ b[i]]]];
            reachidx[i] = min(reachidx[i], static_cast<long long>(lower_bound(x.begin(), x.end(), i + 1) - x.begin()));
            if(reachidx[i] == n) 
            {
                possible = false;
                break;
                // cout<<"NO\n";
            }
        }
        
        for(int i = n - 2; i >= 0; i--)
        {
            reachidx[i] = max(reachidx[i], reachidx[i + 1]);
        }
        
        if(!possible)
        {
            cout<<"NO\n";
            continue;
        }
        
        for(int i = 0; i < n; i++)
        if(a[reachidx[i]] ^ a[i] != b[i])
        possible = false;
        
        if(possible) cout<<"YES\n";
        else cout<<"NO\n";
        
        // cout<<res<<"\n";
    }
}
