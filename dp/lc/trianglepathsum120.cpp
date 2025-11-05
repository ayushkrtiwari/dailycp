// https://leetcode.com/problems/triangle/

    class Solution {
    private:
        int inf = 1e9;
    public:
        int minimumTotal(vector<vector<int>>& triangle) {
            int n = triangle.size();
            // vector<vector<int>> dp(n, vector<int>(n, -1));
            vector<vector<int>> dp(n, vector<int>(n, inf));
            // for(int i = 0; i < n; i++) dp[i].assign(i + 1, inf);
            function<int(int, int)> f = [&](int row, int idx)
            {
                if(row == n) return 0;
                if(dp[row][idx] != inf) return dp[row][idx];
                return dp[row][idx] = triangle[row][idx] + min(f(row + 1, idx), f(row + 1, idx + 1));
            };
            return f(0, 0);
        }
    };