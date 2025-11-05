// https://leetcode.com/problems/burst-balloons/

// if say, there is a block [A, .. ,B], then we are bursting balloons only strictly between A and B

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(n + 2, vector<int>(n + 2, -1));
        function<int(int, int)> f = [&](int l, int r){
            // if(l > r) return 0;
            if(r - l == 1) return dp[l + 1][r + 1] = 0;
            if(dp[l + 1][r + 1] != -1) return dp[l + 1][r + 1];
            int mx = 0;
            for(int i = l + 1; i < r; i++)
            {
                int left = f(l, i);
                int right = f(i, r);
                int leftvalue = (l == -1 ? 1 : nums[l]);
                int rightvalue = (r == n ? 1 : nums[r]);
                mx = max(mx, left + right + leftvalue * nums[i] * rightvalue);
            }
            return dp[l + 1][r + 1] = mx;
        };
        int ans = f(-1, n);
        return ans;
    }
};