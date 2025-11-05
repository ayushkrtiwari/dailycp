// https://leetcode.com/problems/merge-intervals/description/

// This is wrong solution, since we only need to join two overlapping intervals
// take case : [1, 4], [5, 6] -> [1, 6] wrong, no join would be performed.
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        // int n = intervals.size();
        int n = 10000;
        vector<int> range(n + 4, 0);
        for(auto &r : intervals)
        range[r[0]]++, range[r[1] + 1]--;
        int sum = 0;
        for(int i = 0; i < n + 4; i++)
        {
            sum += range[i];
            range[i] = sum;
        }
        vector<vector<int>> res;
        int s = 0, r = 0;
        int lastsum = 0;
        for(int i = 0; i < n + 4; i++)
        {
            if(lastsum == 0 and range[i] > 0)
            s = i;
            if(lastsum > 0 and range[i] == 0)
            r = i - 1, res.push_back({s, r});
            lastsum = range[i];
        }
        return res;
    }
};

// ___________________________________________________________________________________________________________

// Sorting the queries

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [&](const auto &qa, const auto &qb){
            if(qa[0] == qb[0]) return qa[1] < qb[1];
            return qa[0] < qb[0];
        });
        int n = intervals.size();
        vector<vector<int>> res;
        int s = intervals[0][0], r = intervals[0][1];
        for(int i = 1; i < n; i++)
        {
            if(intervals[i][0] <= r) r = max(r, intervals[i][1]);
            else res.push_back({s, r}), s = intervals[i][0], r = intervals[i][1];
        }
        res.push_back({s, r});
        return res;
    }
};