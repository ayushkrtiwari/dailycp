// https://leetcode.com/problems/minimum-score-triangulation-of-polygon/

class Solution {
private:
    int inf = INT_MAX;
public:
    int minScoreTriangulation(vector<int>& values) {
        int n = values.size();
        // since ccw order, no sorting needed
        vector<vector<int>> dp(n, vector<int>(n, -1));
        function<int(int, int)> cost = [&](int start, int end)
        {
            if(dp[start][end] != -1) return dp[start][end];
            if(end - start <= 1) return dp[start][end] = 0;
            int mn = inf;
            for(int i = start + 1; i < end; i++)
            {
                int left = cost(start, i);
                int right = cost(i, end);
                mn = min(mn, left + right + values[start] * values[i] * values[end]);
            }
            // for(int i = start; i <= end; i++)
            // {
            //     int left = cost(start, i - 1);
            //     int right = cost(i + 1, end);
            //     mn = min(mn, left + right + values[start] * values[i] * values[end]);
            // this is wrong since we need to take strictly the points in between start and end
            // else if i == start, then mn = 0 + 0 + values[start] * values[start] * values[end]
            // which is wrong
            // }
            return dp[start][end] = mn;
        };
        int res = cost(0, n - 1);
        return res;
    }
};