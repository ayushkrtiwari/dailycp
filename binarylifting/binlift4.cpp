// जय श्री राम  JAI SHREE RAM

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
_________________________________________________________________________

// we know what the next node is when we jump from a node, now we want to know
// in kth node where will we reach, so we are doing binary lifting for k jumps.
// since above approach gives O(n*k) TLE, when n = 10^5, k = 10^5, and a[] = [s,s,s,s,s....]

#include <bits/stdc++.h>
using namespace std;
# define int long long

int32_t main() {
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
        
        int LOG = (int)log2(n) + 1;
        vector<vector<int>> binlift(n + 1, vector<int>(LOG, -1));
        for(int i = 0; i < n; i++)
        {
            binlift[i][0] = (upper_bound(prefix.begin(), prefix.end(), i > 0 ? prefix[i - 1] + s : s) - prefix.begin());
            if(binlift[i][0] > n)  binlift[i][0] = -1;
        }
        binlift[n][0] = n; // i missed this.it's important since we are doing node - i,
                        // which wants next node if we can take the element, so since we can
                        // take n - 1 say at a case, then we will be doing n - i not (n - 1) - i
        for(int j = 1; j < LOG; j++)
        for(int i = 0; i <= n; i++) // done for i == n too since if n jumps to n only according
                        // to above prefix binary search method and practically too, since
                        // when we are at n and we have k = 3, then the value of possible k 
                        // can be 0, 1, 2, 3 jumps and so we can do 0 jump on each binlift[n][j]
                        // since we want max of n - i and if we dont do such, we get -1 - i
                        // which will be wrong since even at no jump we are at max n, so we do
                        // assign n for each jump from n

                        // but the doubt is there, that for higher bits j(>0), 
                        // i will have actually reached n first by some other node only, 
                        // and at that point it would have done max(mx, n - i) so afterwards if it gets -1, 
                        // thus it wont affect since i have already the same answer in my mx
                        // so why do we do binlift[n][j] = n for all j > 0
        if(binlift[i][j - 1] != -1)
        binlift[i][j] = binlift[binlift[i][j - 1]][j - 1];
        
        int mx = 0;
        int x = (int)log2(k) + 1;
        for(int i = 0; i < n; i++)
        {
            int node = i;
            for(int j = 0; j < x; j++)
            if((k>>j) & 1)
            {
                if(binlift[node][j] == -1)
                break;
                else
                {
                    node = binlift[node][j];
                    mx = max(mx, node - i);
                }
            }
        }
        cout<<mx<<"\n";
        
        
        
        // int mx = 0;
        // int goodlength = 0;
        // int cnt = 0;
        // for(int i = 0; i < n; i++)
        // {
        //     int j = i;
        //     while(cnt < k and j < n and !(next[j] == j))
        //     {
        //         goodlength += next[j] - j;
        //         cnt++;
        //         j = next[j];
        //     }
        //     cnt = 0;
        //     mx = max(mx, goodlength);
        //     goodlength = 0;
        // }
        // cout<<mx<<"\n";
    }
}
