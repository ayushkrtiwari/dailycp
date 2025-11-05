// https://leetcode.com/problems/2-keys-keyboard/

// i understood the problem wrong
// this version is for using any part and doubling it
// so for minm, i only take power of 2, which will give minm for all
// but we could only paste what we copied last time
// eg : for n = 7 : soln = A -> AA -> AAAA -> AAAAAA -> AAAAAAA is wrong
// but soln = A -> AA -> AAA -> AAAA -> AAAAA -> AAAAAA -> AAAAAAA is right
// eg : for n = 6 : soln = A -> AA -> AAAA -> AAAAAA is right hence 3 ops

class Solution {
public:
    int minSteps(int n) {
        int ops = 0;
        int start = 1;
        // vector<int> present(n, false);
        while(start <= n)
        {
            // n -= start;
            // present[start] = true;
            start *= 2;
            ops++;
        }
        n -= start / 2;
        while(n > 0)
        {
            start /= 2;
            if(n >= start)
            {
                n -= start;
                ops++;
            }
        }
        return ops - 1;
    }
};

// ___________________________________________________________________________________

// what i wronged here is in 2nd recursive call, i did copy and paste at once
// while it should only have been the copy call
// also prevent infinite copy by (idx != currcopy)
// also wrongly used idx + 1. 
// Instead use idx, since idx is next place where filling starts, not where filling ends

class Solution {
private:
    const int inf = 1e4;
public:
    int minSteps(int n) {
        int res = 0;
        function<int(int, int)> f = [&](int currcopy, int idx)
        {
            if(idx > n) return inf;
            if(idx == n) return 0;
            int mn = inf;
            // for(int i = 0; i < n; i++)
            mn = min(mn, 1 + f(currcopy, idx + currcopy)); // paste prev copied
            mn = min(mn, 1 + f(idx + 1, idx + (idx + 1))); // copy and paste
            return mn;
        };
        return f(1, 0) - 1;
    }
};

// _______________________________________________________________________________________

class Solution {
private:
    const int inf = 1e4;
public:
    int minSteps(int n) {
        vector<vector<int>> dp(n, vector<int>(n, -1));
        function<int(int, int)> f = [&](int copylength, int idx)
        {
            if(idx == n) return 0;
            if(idx > n) return inf;
            if(dp[copylength][idx] != -1) return dp[copylength][idx];
            int mn = inf;
            if(copylength > 0) mn = min(mn, 1 + f(copylength, idx + copylength)); // paste
            if(idx != copylength) mn = min(mn, 1 + f(idx, idx)); // copy
            return dp[copylength][idx] = mn;
        };
        return f(0, 1);
    }
};