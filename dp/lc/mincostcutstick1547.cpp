// https://leetcode.com/problems/minimum-cost-to-cut-a-stick/

class Solution {
private:
    int inf = INT_MAX;
public:
    int minCost(int n, vector<int>& cuts) {
        // int n = cuts.size();
        sort(cuts.begin(), cuts.end());
        int m = cuts.size();
        // vector<vector<vector<vector<int>>>> dp(m, vector<vector<vector<int>>>(m, vector<vector<int>>(n, vector<int>(n, -1))));
        vector<vector<int>> dp(m, vector<int>(m, -1));
        function<int(int, int, int, int)> f = [&](int start, int end, int l, int r)
        {
            if(start > end) return 0;
            if(dp[start][end] != -1) return dp[start][end];
            // if(dp[start][end][l][r] != -1) return dp[start][end][l][r];
            // if(start == end) return static_cast<int>(r - l);
            // if(/* idx >= n or */ end <= start) return 0;
            // if(idx == n - 1) return (end - start);
            // if(cuts[idx] < cuts[idx + 1]) return (end - start) + f(cuts[idx], idx + 1, end);
            // else return (end - start) + f(start, idx + 1, cuts[idx]);
            int mn = inf;
            for(int i = start; i <= end; i++)
            {
                // int left = f(start, cuts[i] - 1);
                // int right = f(cuts[i] + 1, end);
                // int left = f(start, i - 1, cuts[start], cuts[i]);
                // int right = f(i + 1, end, cuts[i], r);
                int left = f(start, i - 1, l, cuts[i]);
                int right = f(i + 1, end, cuts[i], r);
                mn = min(mn, r - l + left + right);
            }
            return dp[start][end] = static_cast<int>(mn);
        };
        return f(0, cuts.size() - 1, 0, n);
    }
};