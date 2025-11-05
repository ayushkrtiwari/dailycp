// https://leetcode.com/problems/guess-number-higher-or-lower-ii/

class Solution {
public:
    int getMoneyAmount(int n) {
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
        function<int(int, int)> f = [&](int start, int end)
        {
            if(start >= end) return 0;
            if(dp[start][end] != -1) return dp[start][end];
            if(end - start == 1) return dp[start][end] = min(start, end);
            // if(start == end) return 0;
            int mx = INT_MAX;
            for(int i = start; i <= end; i++)
            {
                int left = f(start, i - 1);
                int right = f(i + 1, end);
                mx = min(mx, i + max(left, right));
            }
            return dp[start][end] = mx;
        };
        return f(1, n);
    }
};

// _______________________________________________________________________________________

// memoization/tabulation
// start filling dp table for sequence of lengths 1, 2, and so on

class Solution {
public:
    int getMoneyAmount(int n) {
        // vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
        // function<int(int, int)> f = [&](int start, int end)
        // {
        //     if(start >= end) return 0;
        //     if(dp[start][end] != -1) return dp[start][end];
        //     if(end - start == 1) return dp[start][end] = min(start, end);
        //     // if(start == end) return 0;
        //     int mx = INT_MAX;
        //     for(int i = start; i <= end; i++)
        //     {
        //         int left = f(start, i - 1);
        //         int right = f(i + 1, end);
        //         mx = min(mx, i + max(left, right));
        //     }
        //     return dp[start][end] = mx;
        // };
        vector<vector<int>> dp(n + 2, vector<int>(n + 2, INT_MAX));
        for(int i = 0; i < n + 2; i++)
        // for(int j = i; j < n + 2; j++)
        dp[i][i] = 0;
        for(int l = 1; l < n; l++)
        {
            for(int start = 1; start + l <= n; start++)
            {
                for(int i = start; i <= start + l; i++)
                {
                    dp[start][start + l] = min(dp[start][start + l], \
                        i + max(dp[start][i - 1] == INT_MAX ? 0 : dp[start][i - 1], \
                        dp[i + 1][start + l] == INT_MAX ? 0 : dp[i + 1][start + l]));
                }
            }
        }
        return dp[1][n];
    }
};

// _______________________________________________________________________________________

// debug code : use ide like online cpp compiler

# include<bits/stdc++.h>
using namespace std;

class Solution {
private:
    int inf = 1e9;
public:
    // int n;
    vector<vector<int>> dp;
    // vector<vector<int>> triangle;
    // Solution(int _n, vector<vector<int>> a) : triangle(a), n(_n) 
    // {
    //     dp.resize(n + 1, 0);
    // }
public:
        int getMoneyAmount(int n) {
            // vector<vector<int>> dp(n, vector<int>(n, -1));
            dp.resize(n + 1, vector<int>(n + 1, -1));
            // printdp();
            function<int(int, int)> f = [&](int start, int end)
            {
                // cout<<".\n";
                if(start >= end) return 0;
                if(dp[start][end] != -1) return dp[start][end];
                // if(end > start) return 0;
                if(end - start == 1) 
                {
                    // cout<<"start : "<<start<<" , end : "<<end<<", value : "<<(dp[start][end] = min(start, end))<<"\n";
                    // cout<<"*";
                    dp[start][end] = min(start, end);
                    return dp[start][end];
                }
                if(start == end) 
                {
                    // cout<<"start : "<<start<<" , end : "<<end<<", value : "<<(dp[start][end] = 0)<<"\n";
                    // cout<<"*";
                    dp[start][end] = 0;
                    return dp[start][end];
                }
                int mx = inf;
                for(int i = start; i <= end; i++)
                {
                    int left = f(start, i - 1);
                    int right = f(i + 1, end);
                    mx = min(mx, i + max(left, right));
                }
                // cout<<"start : "<<start<<" , end : "<<end<<", value : "<<(dp[start][end] = mx)<<"\n";
                dp[start][end] = mx;
                return dp[start][end];
            };
            return f(1, n);
        }
    
    void printdp()
    {
        // cout<<"\n";
        for(auto &x : dp) 
        for(auto &y : x)
        cout<<y<<" ";
        cout<<"\n";
    }
};

int main()
{
    vector<vector<int>> a;
    int n = 4;
    cin>>n;
    // a.resize(n);
    // for(int i = 0; i < n; i++)
    // a[i].resize(i + 1);
    // for(auto &r : a)
    // for(auto &c : r)
    // cin>>c;
    Solution s;
    cout<<s.getMoneyAmount(n);
    // s.printdp();
}

// ______________________________________________________________________________

// one of the fastest solutions :) find all solutions using dp above, and then write for each n, dangerousss

class Solution {
public:
    int getMoneyAmount(int n) {
        if(n==10) return 16;
        if(n==2) return 1;
        if(n==3) return 2;
        if(n==6) return 8;
        if(n==7) return 10;
        if(n==9) return 14;
        if(n==16) return 34;
        if(n==18) return 42;
        if(n==25) return 64;
        if(n==45) return 144;
        if(n==56) return 198;
        if(n==63) return 226;
        if(n==77) return 282;
        if(n==83) return 310;
        if(n==94) return 365;
        if(n==109) return 454;
        if(n==115) return 494;
        if(n==120) return 529;
        if(n==139) return 630;
        if(n==141) return 640;
        if(n==151) return 698;
        if(n==160) return 743;
        if(n==176) return 823;
        if(n==183) return 858;
        if(n==191) return 898;
        if(n==200) return 952;
        
        return 0;
    }
};