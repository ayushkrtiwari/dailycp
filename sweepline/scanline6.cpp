// https://leetcode.com/problems/number-of-flowers-in-full-bloom/description/?envType=problem-list-v2&envId=o1qf3c31

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> fullBloomFlowers(vector<vector<int>>& flowers, vector<int>& people) {
        int n = flowers.size(), m = people.size();
        vector<int> starts(n), ends(n);
        for (int i = 0; i < n; ++i) {
            starts[i] = flowers[i][0];
            ends[i]   = flowers[i][1];
        }
        sort(starts.begin(), starts.end());
        sort(ends.begin(), ends.end());

        vector<int> ans(m);
        for (int i = 0; i < m; ++i) {
            int t = people[i];
            // count flowers with start <= t
            int cntStart = upper_bound(starts.begin(), starts.end(), t) - starts.begin();
            // count flowers with end < t
            int cntEnd   = lower_bound(ends.begin(), ends.end(), t) - ends.begin();
            ans[i] = cntStart - cntEnd;
        }
        return ans;
    }
};

// Example usage:
// int main() {
//     Solution sol;
//     vector<vector<int>> flowers = {{1, 6}, {3, 7}, {9, 12}, {4, 13}};
//     vector<int> people = {2, 3, 7, 11};
//     auto res = sol.fullBloomFlowers(flowers, people);
//     for (int x : res) cout << x << " ";  // expected: 1 2 2 2
//     cout << '\n';
//     return 0;
// }