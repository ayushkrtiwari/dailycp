// https://leetcode.com/problem-list/o1qf3c31/

class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        int n = trips.size();
        vector<int> travel(1002,0);
        for(int i=0;i<n;i++)
        {
            int x = trips[i][1];
            int y = trips[i][2];
            int cnt = trips[i][0];
            travel[x]+=cnt;
            travel[y]-=cnt;
        }
        int sum=0,mxsum=0;
        for(int i=0;i<1002;i++)
        {
            sum+=travel[i];
            if(sum>capacity) return false;
            // mxsum=max(mxsum,sum);
        }
        return true;
    }
};