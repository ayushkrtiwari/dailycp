// https://leetcode.com/problems/unique-binary-search-trees/

class Solution {
public:
    int numTrees(int n) {
        // vector<int> a(n);
        // for(int i = 0; i < n; i++) a[i] = i + 1;
        vector<vector<int>> dp(n, vector<int>(n, -1));
        function<int(int, int)> f = [&](int start, int end)
        {
            if(end < start) return 1;
            if(dp[start][end] != -1) return dp[start][end];
            // if(end <= start) return 1;
            int sum = 0;
            for(int i = start; i <= end; i++)
            {
                int left = f(start, i - 1);
                int right = f(i + 1, end);
                sum += left * right;
            }
            return dp[start][end] = sum;
        };
        int res = f(0, n - 1);
        return res;
    }
};