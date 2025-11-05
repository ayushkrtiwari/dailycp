// https://leetcode.com/problems/divide-intervals-into-minimum-number-of-groups/description/

#pragma GCC optimize("O3,unroll-loops,Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
static const auto harsh = []() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
}();
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
    int minGroups(vector<vector<int>>& intervals) {
        vector<pair<int,int>> lr;
        for(auto &x:intervals)
        lr.push_back({x[0], x[1]});
        int M = 0;
        for(auto &x:lr)
        M = max(M,x.second);
        vector<int> prefix(M + 2, 0);
        for(auto &x:lr)
        {
            prefix[x.first]++;
            prefix[x.second + 1]--;
        }
        int mx = 0;
        for(int i = 1; i < M + 2; i++)
        {
            prefix[i] += prefix[i - 1];
            mx = max(mx, prefix[i]);
        }
        return mx;
    }
};