// https://leetcode.com/problems/closest-subsequence-sum/

class Solution {
private:
    vector<long long> get_sums(vector<int> &v)
    {
        vector<long long> sums;
        int n = v.size();
        int totalsubset = 1 << n;
        for(int mask = 0; mask < totalsubset; mask++)
        {
            long long sum = 0;
            for(int i = 0; i < n; i++)
            if(mask & (1 << i))
            sum += v[i];
            sums.emplace_back(sum);
        }
        return sums;
    }
public:
    int minAbsDifference(vector<int>& nums, int goal) {
        int n = nums.size();
        int mid = (n + 1) / 2;
        vector<int> v1, v2;
        for(int i = 0; i < mid; i++)
        v1.emplace_back(nums[i]);
        for(int i = mid; i < n; i++)
        v2.emplace_back(nums[i]);
        vector<long long> sums1 = get_sums(v1);
        vector<long long> sums2 = get_sums(v2);
        sort(sums2.begin(), sums2.end());
        long long sums1sz = sums1.size();
        long long mindiff = LLONG_MAX;
        for(int i = 0; i < sums1sz; i++)
        {
            long long tofind = goal - sums1[i];
            auto it = lower_bound(sums2.begin(), sums2.end(), tofind);
            if(it < sums2.end())
            mindiff = min(mindiff, abs(sums1[i] + *it - goal));
            if(it > sums2.begin())
            {
                it--;
                mindiff = min(mindiff, abs(sums1[i] + *it - goal));
            }
        }
        return mindiff;
    }
};