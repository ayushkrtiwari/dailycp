// https://leetcode.com/problems/minimum-cost-to-merge-stones/

class Solution {
private:
    int inf = 1e9;
public:
    int mergeStones(vector<int>& stones, int k) {
        int n = stones.size();
        if((n - 1) % (k - 1) != 0) return -1;
        vector<int> pre(n, 0);
        vector<vector<int>> dp(n, vector<int>(n, -1));
        for(int i = 0; i < n; i++) pre[i] = (i == 0 ? stones[0] : pre[i - 1] + stones[i]);
        function<int(int, int)> f = [&](int start, int end)
        {
            // if(end >= n or start >= n) return 0;
            if(end == start) return 0;
            if(end - start + 1 < k) return 0;
            // assert(end > start and start >= 0 and end >= 0);
            // assert(end < n and start < n);
            if(dp[start][end] != -1) return dp[start][end];
            // if(end - start + 1 == k) return pre[end] - (start == 0 ? 0 : pre[start - 1]);
            int mn = inf;
            for(int i = start; i < end; i += (k - 1))
            {
                int left = f(start, i);
                int right = f(i + 1, end);
                mn = min(mn, left + right);
                // doing left = f(start, i - 1) and right = f(i, end) is wrong
            }
            if((end - start) % (k - 1) == 0) mn += pre[end] - (start == 0 ? 0 : pre[start - 1]);
            return dp[start][end] = mn;
        };
        return f(0, n - 1);
    }
};