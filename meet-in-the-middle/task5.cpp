// https://www.codechef.com/problems/INSQ15_C

#include <bits/stdc++.h>
using namespace std;
# define MAXN 100'00'01
# define int long long

vector<int> spf(MAXN);

void spff()
{
    for(int i = 0; i < MAXN; i++)
    spf[i] = i;
    for(int i = 2; i < MAXN; i++)
    {
        if(spf[i] == i)
        {
            for(int j = 2 * i; j < MAXN; j += i)
            {
                if(spf[j] == j)
                spf[j] = i;
            }
        }
    }
}

int niceness(int x)
{
    int p = 1;
    set<int> s;
    while(spf[x] > 1)
    {
        s.insert(spf[x]);
        x /= spf[x];
    }
    for(auto &v: s)
    p *= v;
    return p;
}

vector<vector<int>> subset_sum(int k, vector<int> &v)
{
    vector<vector<int>> sums;
    int sz = v.size();
    int len = min(k, sz) + 1;
    sums.resize(len);
    int total = 1 << sz;
    // sums[0].emplace_back(0);
    for(int mask = 0; mask < total; mask++)
    {
        // count no of 1 bits in mask
        int s = __builtin_popcount(mask);
        if(s > k) continue;
        int sum = 0;
        for(int i = 0; i < sz; i++)
        if(mask & (1 << i))
        sum += v[i];
        sums[s].emplace_back(sum);
    }
    return sums;
}

int32_t main() {
	// your code goes here
    spff();
    int n, k, a, b;
    cin>>n>>k>>a>>b;
    vector<int> v(n);
    for(auto &x: v)
    cin>>x;
    
    int mid = (n + 1)/2;
    vector<int> v1;
    vector<int> v2;
    for(int i = 0; i < mid; i++)
    v1.emplace_back(niceness(v[i]));
    for(int i = mid; i < n; i++)
    v2.emplace_back(niceness(v[i]));
    
    vector<vector<int>> sumset1 = subset_sum(k, v1);
    vector<vector<int>> sumset2 = subset_sum(k, v2);
    
    int set1sz = sumset1.size();
    int set2sz = sumset2.size();
    
    for(int i = 0; i < set2sz; i++)
    sort(sumset2[i].begin(), sumset2[i].end());
    
    int cnt = 0;
    for(int i = 0; i < set1sz; i++)
    {
        for(auto x : sumset1[i])
        {
            for(int j = 0; j <= min(k - i, set2sz - 1); j++)
            {
                auto start = lower_bound(sumset2[j].begin(), sumset2[j].end(), a - x);
                auto end = upper_bound(sumset2[j].begin(), sumset2[j].end(), b - x);
                cnt += end - start;
            }
        }
    }
    // for(auto i: sumset1)
    // for(auto x: i) cout<<x<<" ";
    // cout<<"\n";
    // for(auto i: sumset2)
    // for(auto x: i) cout<<x<<" ";
    // cout<<"\n";
    // for(auto i:v) cout<<i<<" ";
    // cout<<"\n";
    // for(auto i:v1) cout<<i<<" ";
    // cout<<"\n";
    // for(auto i: v2) cout<<i<<" ";
    // cout<<"\n";
    // cout<<n<<" "<<k<<" "<<a<<" "<<b<<"\n";
    // cout<<sumset1.size()<<" "<<sumset2.size()<<"\n";
    cout<<cnt<<"\n";
}
