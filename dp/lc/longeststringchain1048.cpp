// https://leetcode.com/problems/longest-string-chain/description/

class Solution {
private:
    bool check(string a, string b)
    {
        int diff = 0;
        if(a.size() > b.size()) swap(a, b); // b is bigger string
        int ss = max(a.size(), b.size());
        // int ss = b.size();
        int l = 0, r = 0;
        for(int i = 0; i < ss; i++)
        if(diff and a[l] != b[r])
        return false;
        else if(a[l] != b[r]) diff++, r++;
        else l++, r++;
        return true;
    }
public:
    int longestStrChain(vector<string>& words) {
        sort(words.begin(), words.end(), [&](const auto &qa, const auto &qb)
        {
            return qa.size() < qb.size();
        });
        int n = words.size();
        vector<int> dp(n, 1);
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < i; j++)
            {
                if(words[i].size() == words[j].size() + 1 and check(words[i], words[j]))
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        return *max_element(dp.begin(), dp.end());
    }
};