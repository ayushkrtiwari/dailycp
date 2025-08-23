// https://leetcode.com/problems/determine-if-two-events-have-conflict/description/

class Solution {
public:
    bool haveConflict(vector<string>& event1, vector<string>& event2) {
        vector<int> e(2500,0);
        int n = event1.size();
            string s1=event1[0],s3 = event2[0],s2=event1[1], s4 = event2[1];
            int x1 = 0, x2 = 0;
            int y1 = 0, y2 = 0;
            x1 += (s1[0]-'0') * 1000 + (s1[1]-'0') * 100 + (s1[3]-'0') * 10 + (s1[4]-'0');
            x2 += (s2[0]-'0') * 1000 + (s2[1]-'0') * 100 + (s2[3]-'0') * 10 + (s2[4]-'0');
            y1 +=(s3[0]-'0') * 1000 + (s3[1]-'0') * 100 + (s3[3]-'0') * 10 + (s3[4]-'0');
            y2 += (s4[0]-'0') * 1000 + (s4[1]-'0') * 100 + (s4[3]-'0') * 10 + (s4[4]-'0');
            if(x1 >= y1 and x1 <= y2) return true;
            else if(y1 >= x1 and y1 <= x2) return true;
            else if(x2 >= y1 and x2 <= y2) return true;
            else if(y2 >= x1 and y2 <= x2) return true;
            return false;
    }
};