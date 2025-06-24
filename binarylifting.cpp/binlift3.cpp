// https://www.codechef.com/problems/LGSEG?tab=statement



#include <bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
    int t;
    cin>>t;
    while(t--)
    {
        int n,k,s;
        cin>>n>>k>>s;
        vector<int> a(n);
        for(auto &x:a) cin>>x;
        vector<int> prefix(n);
        prefix[0] = a[0];
        for(int i = 1; i < n; i++)
        prefix[i] = prefix[i - 1] + a[i];
        vector<int> next(n);
        for(int i = 0; i < n; i++)
        {
            next[i] = (upper_bound(prefix.begin(), prefix.end(), i > 0 ? prefix[i - 1] + s : s) - prefix.begin());
            if(next[i] > n) next[i] = n;
        }
        // [next[i - 1] to next[i] - 1]
        int mx = 0;
        int goodlength = 0;
        int cnt = 0; // max value be k then break
        for(int i = 0; i < n; i++)
        {
            int j = i;
            while(cnt < k and j < n and !(next[j] == j))
            {
                goodlength += next[j] - j;
                cnt++;
                // lastj = j;
                j = next[j];
                // cout<<".";
            }
            cnt = 0;
            // cout<<next[j]<<" "<<i<<"\n";
            // mx = max(mx, (next[j] > n ? n + 1 : j) - i);
            mx = max(mx, goodlength);
            goodlength = 0;
            // cout<<"\n";
        }
        // for(auto &x: next) cout<<x<<" ";
        // cout<<"\n";
        cout<<mx<<"\n";
    }
}
