// https://leetcode.com/problems/number-of-longest-increasing-subsequence/

class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, 1), cnt(n, 1);
        for(int i = 0; i < n; i++)
        for(int j = 0; j < i; j++)
        // if(dp[j] + 1 >= dp[i]) 
        if(nums[j] < nums[i])
        {
            if(dp[j] + 1 == dp[i])
            cnt[i] += cnt[j];
            else if(dp[j] == dp[i])
            cnt[i] = cnt[j], dp[i] = dp[j] + 1;
        }
        int mx = 0, count = 0;
        for(int i = 0; i < n; i++)
        if(dp[i] > mx) mx = dp[i], count = cnt[i];
        else if(dp[i] == mx) count += cnt[i];
        return count;
    }
};