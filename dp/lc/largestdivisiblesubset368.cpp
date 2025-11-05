// https://leetcode.com/problems/largest-divisible-subset/description/

class Solution {
public:
    struct A
    {
        int mx, mn, d, prev;
    };
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<A> dp(n);
        for(int i = 0; i < n; i++)
        dp[i].mx = dp[i].mn = nums[i], dp[i].d = 1, dp[i].prev = -1;
        for(int i = 0; i < n; i++)
        for(int j = i - 1; j >= 0; j--)
        {
            if(dp[i].d >= dp[j].d + 1) continue;
            if(nums[i] % dp[j].mx == 0)
            {
                // dp[i].mx = max(dp[i].mx, dp[j].mx);
                dp[i].prev = j;
                dp[i].mn = dp[j].mn;
                dp[i].d = dp[j].d + 1;
            }
            else if(dp[j].mn % nums[i] == 0)
            {
                // dp[i].mn = min(dp[i].mn, dp[j].mn);
                dp[i].prev = j;
                dp[i].mx = dp[j].mx;
                dp[i].d = dp[j].d + 1;
            }
        }
        int mxm = 0, mxind = 0;
        for(int i = 0; i < n; i++)
        if(dp[i].d > mxm)
        mxm = dp[i].d, mxind = i;

        int curr = mxind;
        // deque<int> dq;
        vector<int> v;
        while(curr >= 0)
        {
            // dq.push_front(nums[curr]);
            v.push_back(nums[curr]);
            curr = dp[curr].prev;
        }
        
        reverse(v.begin(), v.end());
        return v;
        // return mxm;
    }
};