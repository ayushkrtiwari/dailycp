// https://leetcode.com/problems/minimum-cost-for-tickets/

// for coveredidx == -1 so for invalid array access, 
// use extra dp array length, and use [coveredidx + 1] instead of [coveredidx]

class Solution {
private:
    const int inf = 1e9;
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        int n = days.size();
        vector<int> daylength = {1, 7, 30};
        // vector<vector<int>> dp(3, vector<int>(n, inf));
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, inf));
        
        function<int(int, int)> f = [&](int coveredidx, int curridx)
        {
            if(curridx == n) return 0;
            // assert(curridx >= 0 and coveredidx >= 0);
            // assert(curridx < n and coveredidx < n);
            // if(coveredidx != -1 and dp[coveredidx][curridx] != inf) return dp[coveredidx][curridx];
            if(dp[coveredidx + 1][curridx] != inf) return dp[coveredidx + 1][curridx];
            if(curridx <= coveredidx) return dp[coveredidx + 1][curridx] = f(coveredidx, curridx + 1);
            int mn = inf;
            for(int i = 0; i < 3; i++)
            {
                int nxt = curridx;
                // use lower_bound for faster search
                // int tofind = days[curridx] + daylength[i];
                // int nxt = lower_bound(days.begin(), days.end(), tofind) - days.begin();
                while(nxt < n and days[nxt] <= days[curridx] + daylength[i] - 1) nxt++;
                mn = /*costs[i]*/ + min(mn, costs[i] + f(nxt - 1, curridx + 1));
            }
            return dp[coveredidx + 1][curridx] = mn;
        };
        return f(-1, 0);
    }
};

// __________________________________________________________________________________________

class Solution {
private:
    const int inf = 1e9;
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        int n = days.size();
        vector<int> daylength = {1, 7, 30};
        vector<int> dp(n, inf);
        function<int(int)> f = [&](int idx){
            if(idx == n) return 0;
            if(dp[idx] != inf) return dp[idx];
            int mn = inf;
            for(int i = 0; i < 3; i++)
            {
                int tofind = days[idx] + daylength[i] - 1;
                int nxtidx = upper_bound(days.begin(), days.end(), tofind) - days.begin();
                mn = min(mn, costs[i] + f(nxtidx));
            }
            return dp[idx] = mn;
        };
        return f(0);
    }
};