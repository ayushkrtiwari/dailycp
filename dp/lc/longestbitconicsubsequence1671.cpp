// https://leetcode.com/problems/minimum-number-of-removals-to-make-mountain-array/

// Striver's longest bitconic subsequence

class Solution {
public:
    int minimumMountainRemovals(vector<int>& nums) {
        int n = nums.size();
        int check1 = 1200, check2 = -1;
        for(int i = 0; i < n - 1; i++)
        if(nums[i] < nums[i + 1]) check1 = min(check1, i);
        for(int i = n - 2; i >= 0; i--)
        if(nums[i] > nums[i + 1]) check2 = max(check2, i + 1);
        if(check1 >= check2) return n;
        vector<int> dpi(n, 1), dpd(n, 1);
        for(int i = 0; i < n; i++)
        for(int j = 0; j < i; j++)
        if(nums[i] > nums[j]) dpi[i] = max(dpi[i], dpi[j] + 1);
        for(int i = n - 1; i >= 0; i--)
        for(int j = n - 1; j > i; j--)
        if(nums[i] > nums[j]) dpd[i] = max(dpd[i], dpd[j] + 1);
        int mx = 0;
        for(int i = 1; i < n; i++)
        if(dpi[i] == 1 or dpd[i] == 1) continue;
        else mx = max(mx, dpi[i] + dpd[i] - 1);

        // for(int i = check1 + 1; i <= check2 - 1; i++)
        // mx = max(mx, dpi[i] + dpd[i] - 1); this also works, reason it out urself

        // for(int i = check1; i <= check2; i++)
        // mx = max(mx, dpi[i] + dpd[i] - 1); this also works, reason it out
        return n - mx;
    }
};