// जय श्री राम                              JAI SHREE RAM

// https://leetcode.com/problems/stone-game-vi/description/

class Solution {
public:
    int stoneGameVI(vector<int>& aliceValues, vector<int>& bobValues) {
        long long sumalice=0,sumbob=0;
        int n=bobValues.size();
        vector<pair<int,int>> group(n);
        for(int i=0;i<n;i++)
        group[i].first=aliceValues[i],group[i].second=bobValues[i];
        sort(group.begin(),group.end(),[](const pair<int,int>&A,const pair<int,int>&B)
        {
            return A.first+A.second>B.first+B.second;
        });
        for(int i=0;i<n;i++)
        if(i&1)
        {
            sumbob+=group[i].second;
        }
        else
        {
            sumalice+=group[i].first;
        }
        if(sumalice>sumbob) return 1;
        if(sumalice<sumbob) return -1;
        return 0;
    }
};