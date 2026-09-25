// https://codeforces.com/contest/1915/problem/F

#include <bits/stdc++.h>
using namespace std;
# define int long long

static constexpr int N = 2e5 + 5;

struct Fenwick
{
    int BIT[N];
    
    void update(int x, int val) 
    { 
        ++x;
        while(x <= N)  
        {  
            BIT[x] += val;  
            x += (x & -x);  
        } 
    }
    
    int query(int x) 
    {  
        ++x;  
        int res=0;  
        while(x > 0)  
        {  
            res += BIT[x];  
            x -= (x & -x);  
        } 
        return res; 
    }
    
    void clear()
    {
        fill(BIT, BIT + N, 0);
    }
};

int32_t main() {
	// your code goes here
	int t;
	cin>>t;
	while(t--)
	{
	    Fenwick f;
	    f.clear();
        int n;
        cin>>n;
        vector<pair<int,int>> ab(n);
        for(int i = 0; i < n; i++)
        cin>>ab[i].first>>ab[i].second;
        sort(ab.begin(), ab.end(), [&](const auto &qa, const auto &qb){
            return qa.first < qb.first;
        });
        
        vector<int> destination;
        for(auto &[_, d] : ab)
            destination.emplace_back(d);
        
        
        vector<int> comp(n);
        sort(destination.begin(), destination.end());
        destination.erase(unique(destination.begin(), destination.end()), destination.end());
        for(int i = 0; i < n; i++)
        comp[i] = lower_bound(destination.begin(), destination.end(), ab[i].second) - destination.begin();
        
        int total = 0;
        int processed = 0;
        int smalleq = 0;
        for(int i = 0; i < n; i++)
        {
            int compd = comp[i];
            smalleq = f.query(compd);
            total += processed - smalleq;
            f.update(compd, 1);
            processed++;
        }
        cout<<total<<"\n";
	}
}