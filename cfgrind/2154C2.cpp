// https://codeforces.com/contest/2154/problem/D

#include <bits/stdc++.h>
using namespace std;
# define int long long
const int MAXN = 200005;
vector<int> spf(MAXN);

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};


void spff() 
{
    spf.assign(MAXN + 1, 0);
    spf[0] = 0, spf[1] = 1;
    for (int i = 2; i <= MAXN; ++i) {
        if (spf[i] == 0) 
        {
            for (int j = i; j <= MAXN; j += i) 
            {
                if (spf[j] == 0) 
                spf[j] = i;
            }
        }
    }
}

bool prime(int x)
{
    if(x == spf[x])
    return true;
    return false;
}

int32_t main() {
	int t;
	cin>>t;
	spff();
    for(int tt = 1; tt <= t; tt++)
	{
	    int n;
	    cin>>n;
	    vector<int> a(n), b(n);
	    for(auto &x : a) cin>>x;
	    for(auto &x : b) cin>>x;
	    unordered_map<int, int, custom_hash> ump;
	    bool is1poss = false, is0poss = false;
	    // for each prime factor, we make vector of (cost, freq)
	    // denoting b[i] and once freq update for unique prime factor per b[i]
	    // freq denotes freq of a[i] with that cost with that prime factor 
	   // vector<vector<pair<int, int>>> costprimes(n + 1);
	   // but while putting {cost, freq} in costprimes, i realised
	   // how will we manage freq in a pair, retrieval, sort, update
	   // hence we will only keep cost, and sort every 1D vector in costprimes
	   // and then we can do binary search for freq. Great !!
	   
	   // Again a problem is that I need to assign cost for these primes
	   // in vector, but neither the size nor the assignment for those
	   // primes can be created in costprimes for large value of 1e9, 
	   // since generating value will make space and time complexity to exceed
	   // coordinate compression wont work too thus
	   
	   // Now I want another way to store these primes and cost, not using
	   // a linear data structure, but a random like unordered map, 
	   // but first issue is how do we generate all primes upto 1e9 and primesize
	   
	   // i got to know the use of unordered map < int, vector > 
	    
	   // vector<vector<int>> costprimes(primesize + 1);
	    unordered_map<int, vector<int>> costprimes;
	    auto add = [&](int prime, int cost) -> void
	    {
	        costprimes[prime].push_back(cost);
	    };
	    for(int i = 0; i < n; i++) 
	    {
	        int x = a[i];
	        while(x != 1)
	        {
	            int f = spf[x];
	            ump[f]++;
	            add(f, b[i]);
	            while(x % f == 0)
	            x /= f;
	        }
	    }
	   // for(auto &row : costprimes)
	   // sort(row.begin(), row.end());
	    
	    int mnamt = LLONG_MAX;
	    
	    // checking possibility in 0 update
	    for(auto &x : ump) 
	    if(x.second > 1) 
	    {
	        int prime = x.first;
	        mnamt = min(mnamt, 0ll);
	       // mnamt = min(mnamt, costprimes[prime][0] + costprimes[prime][1]);
	        is0poss = true;
	    }
	    if(is0poss)
	    {
	        cout<<0<<"\n";
	        continue;
	    }
	   // cout<<mnamt<<". ";
	    
	    // checking possibility in 1 update
	    for(int i = 0; i < n; i++)
	    {
	        int nmb = a[i] + 1;
	        while(nmb != 1)
	        {
	            int spfnmb = spf[nmb];
	            if(ump[spfnmb] == 1)
	            {
	                is1poss = true;
	                mnamt = min(mnamt, b[i]);
	            }
	            while(nmb % spfnmb == 0)
	            nmb /= spfnmb;
	        }
	    }
	   // cout<<mnamt<<".. ";
	    
	    // one more possibility in 1 update, 
	    // we can increase 1 element a no of times to become another element
	    vector<pair<int, int>> ab;
	    for(int i = 0; i < n; i++)
	    ab.push_back({a[i], b[i]});
	    
	   // sort(ab.begin(), ab.end());
	   // // both adjacent elements should not be 1
	   // if(ab[0].first != 1 or ab[1].first != 1)
	   // mnamt = min(mnamt, 1ll * ab[0].second * (ab[1].first - ab[0].first));
	   //// cout<<mnamt<<", ";
	   // if(ab[n - 2].first != 1 or ab[n - 1].first != 1)
	   // mnamt = min(mnamt, 1ll * ab[n - 2].second * (ab[n - 1].first - ab[n - 2].first));
	   //// cout<<mnamt<<",, ";
	   // for(int i = 1; i < n - 1; i++)
	   // {
	   //     if(ab[i - 1].first != 1 or ab[i].first != 1)
	   //     mnamt = min(mnamt, 1ll * ab[i - 1].second * (ab[i].first - ab[i - 1].first));
	   //    // cout<<mnamt<<",,, ";
	   //     if(ab[i].first != 1 or ab[i + 1].first != 1)
	   //     mnamt = min(mnamt, 1ll * ab[i].second * (ab[i + 1].first - ab[i].first));
	   //    // cout<<mnamt<<",,,, ";
	   // }
	    // checking possibility in 2 updates
	    // take 2 minms of all costs
	    sort(b.begin(), b.end());
	    mnamt = min(mnamt, b[0] + b[1]);
	   // cout<<mnamt<<"- ";
	    
	    // one more case is there, if one is odd, other even,
	    // increase the odd one till gcd > 1
	    // again it may happen that increase odd one is costly 
	    // while increasing even one is cheaper
	    // or say even one reaches destination first much cheaper than odd one
	    // hence we need to check this way for all pairs
	    // so we need to get a suitable approach, somewhat dp
	   // like here failed in test case 2
	   // also, take case, a : 2, 25; b : 1, 100
	   // now, we cant increase 25 since it costs much more
	   // but we can increase 2 -> 5, hence mnamt = 3
	   // i only need to finally handle the case where there can be 
	   // abruptly increase in one of the elements
	   // Not satisfied with the editorial, since it says only 1 increase needed per element
	   // This is not right or i am not getting something, according to above examples
	   // now i got the editorial, if we have 2 elements to be updated
	   // then thus we take b1 + bx, since any other combination other than b1
	   // will give bx + by >= b1 + bx, hence we take a1 into account
	   // so we will update a1 and check if any ax can have same gcd
	   // here, we wont be needing to update more than 1 element more than once,
	   // since if such happens we will just increase both by 1, 
	   // and they are divisible by 2. so this one we do by updating b1 + b2 with mnamt
	   // did that already. Now I increase just 1st element and check its gcd with others
	   // since the ump contains prime factors of a1 while we change a1,
	   // we make new umpnew without primes of a1
	   unordered_map<int, int, custom_hash> umpnew;
	   //vector<pair<int, int>> ba;
	   //for(int i = 0; i < n; i++)
	   //ba.push_back({b[i], a[i]});
	   sort(ab.begin(), ab.end(), [&](const auto pr1, const auto pr2){
	       return pr1.second < pr2.second;
	   });
	   
	   for(int i = 1; i < n; i++)
	   {
	       int nm = ab[i].first;
	       int f = spf[nm];
	       while(nm != 1)
	       {
	           umpnew[f]++;
	           while(nm % f == 0)
	           nm /= f;
	           f = spf[nm];
	       }
	   }
	   
	   // after getting so much tle on tc 6 even after commenting and removing
	   // unwanted lines, it did not pass. I think its likely that while(!done)
	   // loop is executing infinitely. no it wont be infinite, but huge
	   // i think if a1 < a2 and a2 - a1 is huge gap
	   // like > 1e7, then it will tle, so what we should do.. i dont know
	   // nope its only 2e5 by constraints
	   // no issue from !done infinitely cycle
	   // no issue of huge gap
	   // no issue for isumpnewempty function check in loop
	   
	   // then where do we get tle for tight constraints
	   // should i get to some ide, or stress test on large case
	   // and see till which constraints of n is code passing
	   // then i can get code's time complexity
	   
	   // from all the testcases till 6, i see that everything runs,
	   // but this may be failing at 6 where large tc of t = 1e4, small n,
	   // (since n over all tc <= 2e5), elements are large and has huge gaps
	   // in submissions, its showing output, but not answer, and this is strange
	   // since while tle, output isn't shown, but answer is shown
	   
	   // increasing by that huge gap over all pair of elements will tle easily
	   
	   // got help by gpt now : 
	   // the expensive part figured out is the increment of ab1.first
	   // we can directly jump to next common gcd, using modulo equality
	   // we want (ab0.first + k) % p == 0, k == (p - (ab0.first % p)) % p
	   
	   bool done = false;
	   int inc = 0;
	   //bool isumpnewempty = umpnew.empty();
	   //while(!isumpnewempty and !done)
	   //{
	   //    ab[0].first++;
	   //    inc++;
	   //    for(auto &x : umpnew)
	   //    {
	   //        if(ab[0].first % x.first == 0)
	   //        {
	   //            done = true;
	   //            mnamt = min(mnamt, 1ll * inc * ab[0].second);
	   //            break;
	   //        }
	   //    }
	   //}
	   //for(int i = 1; i < n; i++)
	   //{
	       for(auto &x : umpnew)
	       {
	           inc = (x.first - (ab[0].first % x.first)) % x.first;
	           // if(ab[0].first % x.first == 0)
	           mnamt = min(mnamt, 1ll * inc * ab[0].second);
	       }
	   //}
	   //cout<<"\n";
	   //for(auto &x : ab)
	   //cout<<x.first<<" "<<x.second<<"\n";
	   
	   // cout<<mnamt<<": ";
	   // cout<<"\n";
	   cerr<<"Case "<<tt<<": "<<mnamt<<"\n";
	    cout<<mnamt<<"\n";
	}
}