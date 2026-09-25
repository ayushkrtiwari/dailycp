// https://leetcode.com/problems/minimum-number-of-refueling-stops/

// starting wrong solution approach

class Solution {
private:
    const int inf = INT_MAX;
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        // stations.push_front({0, 0});
        stations.push_back({target, 0});
        int n = stations.size();
        // start from end to begin since it's not known what liter to start with from begin
        vector<int> dp(n, -1);
        function<int(int, int)> f = [&](int nidx, int currfuel)
        {
            if(nidx < 0) return 0;
            // if(nidx == 0 and currfuel >= startFuel) return 0;
            // if(nidx == 0 and currfuel < startFuel) return inf;
            if(nidx == 0 and currfuel < stations[0][0]) return inf;
            if(nidx == 0 and currfuel >= stations[0][0]) return 0;
            if(currfuel < 0) return inf;
            // if(dp[nidx] != -1) return dp[nidx];
            int res = inf;
            for(int idx = nidx - 1; idx >= 0; idx--)
            {
                if(stations[nidx][0] - stations[idx][0] <= currfuel + stations[nidx][1])
                // dp[idx] = min(dp[idx], 1 + dp[nidx]);
                res = min(res, 1 + f(idx, currfuel - (stations[nidx][0] - stations[idx][0]) + stations[nidx][1]));
                // else break;
            }
            return dp[nidx] = res;
        };
        int r = f(n - 1, startFuel);
        return r == INT_MAX ? -1 : r;
    }
};