// member helper: ~5–20 ms

// self-lambda: ~8–30 ms

// std::function: ~30–120 ms

// bench.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int AMOUNT = 6249;
const vector<int> COINS = {186,419,83,408};
const int REPS = 200; // number of times to run each implementation for averaging

// ___________________________________________________________________

// Y-combinator helper
// wrapped to avoid self(self, ...) call syntax

template<class F> struct Y { F f; 
    template<class...Args> decltype(auto) operator()(Args&&...args) { return f(*this, forward<Args>(args)...); }
};
auto dfs = Y{[&](auto& self, int node)->bool {
    // use self(child) for recursion
    return ...;
}};
dfs(0);

// ______________________________________________________________________

// Implementation A: std::function recursive lambda
int run_std_function() {
    int amount = AMOUNT;
    auto coins = COINS;
    const int INF = amount + 1;
    int n = coins.size();
    vector<int> dp(amount+1, -1);
    function<int(int)> f = [&](int amtsum)->int{
        int res = INF;
        if(amtsum == amount) return 0;
        if(amtsum > amount) return INF;
        if(dp[amtsum] != -1) return dp[amtsum];
        for(int i=0;i<n;i++){
            if(coins[i] <= 0) continue;
            int next = amtsum + coins[i];
            if(next <= amount){
                int sub = f(next);
                if(sub != INF) res = min(res, sub + 1);
            }
        }
        return dp[amtsum] = res;
    };
    return f(0);
}

// Implementation B: self-recursive lambda (Y-combinator style)
int run_self_lambda() {
    int amount = AMOUNT;
    auto coins = COINS;
    const int INF = amount + 1;
    int n = coins.size();
    vector<int> dp(amount+1, -1);
    auto f = [&](auto&& self, int amtsum)->int{
        int res = INF;
        if(amtsum == amount) return 0;
        if(amtsum > amount) return INF;
        if(dp[amtsum] != -1) return dp[amtsum];
        for(int i=0;i<n;i++){
            if(coins[i] <= 0) continue;
            int next = amtsum + coins[i];
            if(next <= amount){
                int sub = self(self, next);
                if(sub != INF) res = min(res, sub + 1);
            }
        }
        return dp[amtsum] = res;
    };
    return f(f, 0);
}

// Implementation C: member-style helper (plain function)
int dfs_helper(int amtsum, const vector<int>& coins, vector<int>& dp, int amount) {
    const int INF = amount + 1;
    if(amtsum == amount) return 0;
    if(amtsum > amount) return INF;
    if(dp[amtsum] != -1) return dp[amtsum];
    int res = INF;
    int n = coins.size();
    for(int i=0;i<n;i++){
        if(coins[i] <= 0) continue;
        int next = amtsum + coins[i];
        if(next <= amount){
            int sub = dfs_helper(next, coins, dp, amount);
            if(sub != INF) res = min(res, sub + 1);
        }
    }
    return dp[amtsum] = res;
}
int run_helper_fn() {
    int amount = AMOUNT;
    auto coins = COINS;
    vector<int> dp(amount+1, -1);
    return dfs_helper(0, coins, dp, amount);
}

template<typename F>
double time_fn(F f, int reps){
    using clock = std::chrono::high_resolution_clock;
    auto t0 = clock::now();
    int out = 0;
    for(int i=0;i<reps;i++){
        out ^= f(); // use result so compiler doesn't optimize away (simple combine)
    }
    auto t1 = clock::now();
    double ms = chrono::duration<double, milli>(t1 - t0).count();
    // print the last result too to confirm correctness
    cout << "result checksum: " << out << endl;
    return ms;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "Benchmarking each implementation with " << REPS << " reps (same test case)\n";

    // warm up (one run each)
    run_helper_fn();
    run_self_lambda();
    run_std_function();

    double t_helper = time_fn(run_helper_fn, REPS);
    cout << "helper fn total ms: " << t_helper << ", avg ms: " << (t_helper/REPS) << "\n\n";

    double t_self = time_fn(run_self_lambda, REPS);
    cout << "self-lambda total ms: " << t_self << ", avg ms: " << (t_self/REPS) << "\n\n";

    double t_std = time_fn(run_std_function, REPS);
    cout << "std::function total ms: " << t_std << ", avg ms: " << (t_std/REPS) << "\n\n";

    return 0;
}
