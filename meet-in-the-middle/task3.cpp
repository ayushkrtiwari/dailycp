// https://lightoj.com/problem/coin-change-iv


// Here, we need base 3 mask instead of base 2, for 0, 1, 2 times sum
// n = 18 hence, 3 ^ 18 => 1e9, but 3 ^ (18/2) = 3 ^ 9 => 1e5, hence meet in the middle

// 1280 KB, 163 ms

#include <bits/stdc++.h>
using namespace std;
# define int long long

// Reads two integers and prints their sum

vector<int> gen_sums(vector<int> &v)
{
    int vsz = v.size();
    int totalsubset = pow(3, vsz);
    vector<int> sums;
    for(int mask = 0; mask < totalsubset; mask++)
    {
        int tmp = mask;
        int sum = 0;
        for(int i = 0; i < vsz; i++)
        {
            int digit = tmp % 3;
            sum += v[i] * digit;
            tmp /= 3;
        }
        sums.emplace_back(sum);
    }
    return sums;
}

int32_t main() {
    // basicIO();
    // Your cpp code here
    int t;
    cin>>t;
    for(int tc = 1; tc <= t; tc++)
    {
        int n, k;
        cin>>n>>k;
        vector<int> v(n);
        for(auto &x: v) cin>>x;
        int mid = (n + 1) / 2;
        vector<int> v1, v2;
        for(int i = 0; i < mid; i++)
            v1.emplace_back(v[i]);
        for(int i = mid; i < n; i++)
            v2.emplace_back(v[i]);
        vector<int> sum1 = gen_sums(v1);
        vector<int> sum2 = gen_sums(v2);
        sort(sum2.begin(), sum2.end());
        int sum1sz = sum1.size();
        bool possible = false;
        for(int i = 0; i < sum1sz; i++)
        {
            auto it = lower_bound(sum2.begin(), sum2.end(), k - sum1[i]);
            if(it == sum2.end()) continue;
            if(sum1[i] + *it == k)
            {
                possible = true;
                break;
            }
        }
        cout<<"Case "<<tc<<": "<<(possible ? "Yes\n": "No\n");
    }
    return 0;
}

// ______________________________________________________________________________

// GPT's solution

// 1036 KB, 94 ms

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// generate all possible sums by choosing each coin in arr[pos..end) 0,1,2 times
void gen_sums(const vector<ll>& arr, int pos, ll curr, vector<ll>& out) {
    if (pos == (int)arr.size()) {
        out.push_back(curr);
        return;
    }
    // use 0 times
    gen_sums(arr, pos+1, curr, out);
    // use 1 time
    gen_sums(arr, pos+1, curr + arr[pos], out);
    // use 2 times
    gen_sums(arr, pos+1, curr + 2*arr[pos], out);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for(int tc = 1; tc <= T; ++tc){
        int n;
        ll K;
        cin >> n >> K;
        vector<ll> A(n);
        for(int i = 0; i < n; i++) 
            cin >> A[i];

        // split into two halves
        int mid = n/2;
        vector<ll> left(A.begin(), A.begin() + mid), right(A.begin()+mid, A.end());

        // generate all sums for each half
        vector<ll> Ls, Rs;
        Ls.reserve(pow(3, left.size()));
        Rs.reserve(pow(3, right.size()));
        gen_sums(left,  0, 0LL, Ls);
        gen_sums(right, 0, 0LL, Rs);

        // sort the right sums for binary search
        sort(Rs.begin(), Rs.end());

        bool ok = false;
        for (ll s : Ls) {
            ll need = K - s;
            // binary search in Rs for exactly 'need'
            if (binary_search(Rs.begin(), Rs.end(), need)) {
                ok = true;
                break;
            }
        }

        cout << "Case " << tc << ": " << (ok ? "Yes\n" : "No\n");
    }
    return 0;
}
