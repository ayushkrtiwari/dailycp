// https://leetcode.com/problems/shifting-letters-ii/description/

class Solution {
public:
    string shiftingLetters(string s, vector<vector<int>>& shifts) {
        int n = s.size();
        vector<int> v(n+2,0);
        int m = shifts.size();
        for(int i=0 ; i < m; i++)
        {
            int l = shifts[i][0];
            int r = shifts[i][1];
            int d = shifts[i][2];
            if(d)
            {
                v[l]++;
                v[r + 1]--;
            }
            else
            {
                v[l]--;
                v[r + 1]++;
            }
        }
        int curr = 0;
        for(int i = 0; i < n; i++)
        {
            curr += v[i];
            int change = curr % 26;
            if(s[i] + change > 122)
            s[i] += (change - 26);
            else
            s[i] += change;
            if(s[i] < 97)
            s[i] += 26;
        }
        return s;
    }
};