// #include <bits/stdc++.h>
// using namespace std;
// int main(){
//   int n; if(!(cin>>n))return 0;
//   vector<long long>a(n);
//   for(int i=0;i<n;i++)cin>>a[i];

//   long long best=LLONG_MIN;
//   for(int i=0;i<n;i++){
//     for(int j=i;j<n;j++){
//       long long s=0;
//       for(int k=i;k<=j;k++)s+=a[k];
//       best=max(best,s);
//     }
//   }
//   cout<<best;
// }

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128_t;

// compute gcd(a,b)
ll gcdll(ll a, ll b) {
    while(b){
        ll t = a % b;
        a = b;
        b = t;
    }
    return a;
}

// safe lcm(a,b), but if it overflows past 1e18 we cap it there
ll lcmll(ll a, ll b) {
    if(a==0 || b==0) return 0;
    ll g = gcdll(a,b);
    // do in 128‑bit to avoid overflow
    i128 t = (i128)a / g * b;
    if(t > (i128)1e18) t = (i128)1e18;
    return (ll)t;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<ll> a(n);
        unordered_set<ll> S;
        for(int i = 0; i < n; i++){
            cin >> a[i];
            S.insert(a[i]);
        }

        int best = 0;
        // enumerate all non‐empty subsequences by bitmask
        // WARNING: only feasible for n ≲ 20
        int total = 1<<n;
        for(int mask = 1; mask < total; mask++)
        {
            int cnt = __builtin_popcount(mask);
            // if even the full-popcount can't beat current best, skip
            if(cnt <= best) continue;

            // compute LCM of this subsequence
            ll cur = 1;
            bool overflow = false;
            for(int i = 0; i < n; i++){
                if(mask & (1<<i)){
                    cur = lcmll(cur, a[i]);
                    // if lcm got huge, we know it's not in S
                    if(cur > (ll)1e9){
                        overflow = true;
                        break;
                    }
                }
            }
            // if we overflowed beyond the input range,
            // it's certainly not in S
            if(overflow){
                best = cnt;
                continue;
            }
            // otherwise check membership
            if(!S.count(cur)){
                best = cnt;
            }
        }

        // don't forget: the empty subsequence has LCM=0,
        // which is never in S since ai≥1, so if best is still 0,
        // you could also choose the empty subsequence (but
        // its length is 0 so best=0 is correct).
        cout << best << "\n";
    }
    return 0;
}
