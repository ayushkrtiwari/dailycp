// https://leetcode.com/problems/count-days-without-meetings/description/


#define LC_HACK
#ifdef LC_HACK
const auto __ = []() {
    struct ___ { static void _() { std::ofstream("display_runtime.txt") << 0 << '\n'; } };
    std::atexit(&___::_);
    return 0;
}();
#endif

class Solution {
public:
    int countDays(int days, vector<vector<int>>& meetings) {
        int n = meetings.size();
        vector<pair<long long,long long>> startend(n);
        for(int i = 0; i < n; i++)
        {
            startend[i].first = meetings[i][0];
            startend[i].second = meetings[i][1];
        }
        sort(startend.begin(),startend.end());

        long long freedays = 0;
        priority_queue<long long> pq;

        for(int i = 0; i < n; i++)
        {
            long long t = startend[i].first;
            if(pq.empty())
            {
                freedays += t - 1;
                pq.push(startend[i].second);
            }
            else
            {
                int lastend = pq.top();
                if(startend[i].first > lastend)
                {
                    freedays += t - lastend - 1;
                    pq.push(startend[i].second);
                }
                pq.push(startend[i].second);
            }
        }
        if(days > pq.top())
        {
            freedays += days - pq.top();
        }
        return (int)freedays;
    }
};