// https://leetcode.com/problems/valid-triangle-number/

// #pragma GCC optimize("O3,unroll-loops,Ofast")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
// static const auto harsh = []() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(nullptr);
//     cout.tie(nullptr);
//     return 0;
// }();
// #define LC_HACK
// #ifdef LC_HACK
// const auto __ = []() {
//   struct ___ { static void _() { std::ofstream("display_runtime.txt") << 0 << '\n'; } };
//   std::atexit(&___::_);
//   return 0;
// }();
// #endif

// O(n^2 log n)
class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int res = 0;
        int i = 0;
        while(i < n and nums[i] == 0) i++;
        for(; i < n - 2; i++)
        {
            for(int j = i + 1; j < n - 1; j++)
            {
                int y = nums[j], x = nums[i];
                int start = lower_bound(nums.begin(), nums.end(), abs(y - x) + 1) - nums.begin();
                int end = upper_bound(nums.begin(), nums.end(), x + y - 1) - nums.begin();
                start = max(start, j + 1);
                res += end - start;
            }
        }
        return res;
    }
};

// O(n^2)

class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int res = 0;
        for(int i = 0; i < n - 2; i++)
        {
            int k = i + 2;
            for(int j = i + 1; j < n - 1; j++)
            {
                while(k < n and nums[i] + nums[j] > nums[k]) k++;
                res += max(0, k - j - 1);
            }
        }
        return res;
    }
};