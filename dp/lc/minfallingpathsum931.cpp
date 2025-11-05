// https://leetcode.com/problems/minimum-falling-path-sum/

class Solution {
private:
    const int inf = 1e5;
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        vector<vector<int>> dp(n, vector<int>(n, inf));
        function<int(int, int)> f = [&](int r, int c)
        {
            int mn = inf;
            if(c < 0 or c >= n) return inf;
            if(r == n - 1) return matrix[r][c];
            if(dp[r][c] != inf) return dp[r][c];
            vector<int> coladd = {-1, 0, 1};
            for(int i = 0; i < 3; i++)
            mn = min(mn, matrix[r][c] + f(r + 1, c + coladd[i]));
            return dp[r][c] = mn;
        };
        int mnm = inf;
        for(int i = 0; i < n; i++)
        mnm = min(mnm, f(0, i));
        return mnm;
    }
};