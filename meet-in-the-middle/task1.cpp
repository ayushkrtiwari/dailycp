// https://lightoj.com/problem/funny-knapsack

#include <bits/stdc++.h>
using namespace std;
# define int long long

// Reads two integers and prints their sum
void basicIO() {
    int a, b;
    cin >> a >> b;
    cout << a + b << endl;
}

vector<int> get_sums(vector<int> v)
{
    vector<int> sums;
    int vsize = v.size();
    int totalsubset = 1 << vsize;
    for(int mask = 0; mask < totalsubset; mask++)
    {
        int sum = 0;
        for(int i = 0; i < vsize; i++)
            if(mask & (1 << i))
                sum += v[i];
        sums.emplace_back(sum);
    }
    return sums;
}

int32_t main() {
    // basicIO();
    // Your cpp code here
    int t;
    cin>>t;
    for(int i = 1; i <= t; i++)
    {
        int n,w;
        cin>>n>>w;
        vector<int> v(n);
        for(auto &x: v)
            cin>>x;
        int mid = (n + 1) / 2;
        vector<int> v1, v2;
        for(int i = 0; i < mid; i++)
            v1.emplace_back(v[i]);
        for(int i = mid; i < n; i++)
            v2.emplace_back(v[i]);
        vector<int> sum1 = get_sums(v1);
        vector<int> sum2 = get_sums(v2);
        sort(sum2.begin(), sum2.end());
        int sum1sz = sum1.size();
        int cnt = 0;
        for(int i = 0; i < sum1sz; i++)
        {
            int tofind = w - sum1[i];
            auto it = upper_bound(sum2.begin(), sum2.end(), tofind);
            // if(it == sum2.begin()) continue;
            cnt += it - sum2.begin();
        }
        cout<<"Case "<<i<<": "<<cnt<<"\n";
    }
    return 0;
}