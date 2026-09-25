// https://leetcode.com/problems/coin-change/description/

// # define int long long
// # define int uint32_t
class Solution {
private:
    const int inf = 1e4 + 5;
public:
    int coinChange(vector<int>& coins, int amount) {
        // int ans = 0;
        int n = coins.size();
        // greedy wont work since there may be a case where taking smaller coin
        // would give us exact amount but we are taking here larger first greedily
        // hence we need dp for all minm combination of the amounts .. knapsack
        // sort(coins.begin(), coins.end(), greater<int>());
        // for(int i = 0; i < n; i++)
        // {
        //     while(amount - coins[i] >= 0)
        //     {
        //         amount -= coins[i];
        //         // sum += coins[i];
        //         ans++;
        //     }
        // }
        // return amount == 0 ? ans : -1;
        // vector<int> dp(10005, inf);
        // vector<int> freq(n, 0);
        function<int(int)> f = [&](int amtsum)
        {
            int res = inf;
            if(amtsum == amount) return 0;
            for(int i = 0; i < n; i++)
            {
                // if(assert(amtsum + coins[i] <= 2147483647); amtsum + coins[i] <= amount)
                // assert(1 + f(amtsum + coins[i]) <= 2147483647),
                // i dont know but here some error was coming for overflow while there shouldn't be any
                // since i am using 1e4 + 5 as inf not INT_MAX, and if the 'if' condition isn't satisfied
                // then directly res(as inf) should be returned which shouldn't overflow INT_MAX at any cost
                // and hence this check : sentcheck != inf wasn't needed 
                // but still if removed it gives the same error
                if(amtsum + static_cast<long long>(coins[i]) <= amount)
                // we cannot put long long everywhere due to already given int paramters in function header
                // hence we just use casting in coins[i] since its 1e9
                // hence adding wont overflow if long long is done at intermediate
                {
                    int sentcheck = f(amtsum + coins[i]); 
                    if(sentcheck != inf)
                    res = min(res, 1 + f(amtsum + coins[i]));
                }
            }
            return res;
        };
        int ans = f(0);
        return ans == inf ? -1 : ans;
    }
};

// _________________________________________________________________________________

// TLE occurrence issue in this code was : 
// i used sentinel inf value as both uncomputed value and large garbage value,
// this means if at any amtsum value has already been calculated but was not possible,
// so it returned inf at that value, but when again this would be retrieved then 
// it would again be calculated and hence dp is of no use
// Thus keep sentinel and uncomputed values different.

// using self recursive lambda function removes std::function overhead
// If you switch to std::function you avoid the compile error, 
// but you pay runtime overhead for each call (type-erasure + possible heap allocations).
// Tips : If you prefer clarity and performance and you’re inside a class (like Solution), 
// implementing the recursive helper as a private member function is equally minimal and may be even faster

// member helper: ~5–20 ms

// self-lambda: ~8–30 ms

// std::function: ~30–120 ms

class Solution {
private:
    const int inf = 1e4 + 5;
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        vector<int> dp(amount + 1, -1);
        auto f = [&](auto&& self, int amtsum) -> int // can use auto const& self or auto& self
        {
            int res = inf;
            if(amtsum == amount) return 0;
            if(amtsum > amount) return inf;
            if(dp[amtsum] != -1) return dp[amtsum];
            for(int i = 0; i < n; i++)
            {
                if((long long)amtsum + static_cast<long long>(coins[i]) <= (long long)amount)
                {
                    int sentcheck = self(self, (int)((long long)amtsum + (long long)coins[i])); 
                    if(sentcheck != inf)
                    res = min(res, 1 + sentcheck);
                }
                // this works too
                // if(amtsum + (long long)coins[i] <= amount)
                // {
                //     int sentcheck = self(self, amtsum + coins[i]); 
                //     if(sentcheck != inf)
                //     res = min(res, 1 + sentcheck);
                // }
            }
            return dp[amtsum] = res;
        };
        int ans = f(f, 0);
        return ans == inf ? -1 : ans;
    }
};