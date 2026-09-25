// https://leetcode.com/problems/triangle/description/

// 2 states

    class Solution {
    private:
        int inf = 1e9;
    public:
        int minimumTotal(vector<vector<int>>& triangle) {
            int n = triangle.size();
            // vector<vector<int>> dp(n, vector<int>(n, -1));
            vector<vector<int>> dp(n, vector<int>(n, inf));
            // for(int i = 0; i < n; i++) dp[i].assign(i + 1, inf);
            function<int(int, int)> f = [&](int row, int idx)
            {
                if(row == n) return 0;
                if(dp[row][idx] != inf) return dp[row][idx];
                return dp[row][idx] = triangle[row][idx] + min(f(row + 1, idx), f(row + 1, idx + 1));
            };
            return f(0, 0);
        }
    };

// ________________________________________________________________________________________________________

// 1 state

class Solution {
private:
    int inf = 1e9;
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        vector<int> dp(n + 1, 0);
        // for(int i = 0; i < n; i++) dp[i] = triangle[n - 1][i];
        for(int i = n - 1; i >= 0; i--)
        {
            for(int j = 0; j <= i; j++)
            // for(int j = i; j >= 0; j--)
            {
                // if(j == i)
                // {
                //     dp[j] = triangle[i][j];
                //     continue;
                // }
                // assert(j + 1 < n and i < n);
                // dp[j] = dp[j] + min(triangle[i][j], triangle[i][j + 1]);
                dp[j] = triangle[i][j] + min(dp[j], dp[j + 1]);
            }
        }
        // return *min_element(dp.begin(), dp.end());
        // return dp[0] + triangle[0][0];
        return dp[0];
        // if(n == 1) return triangle[0][0];
        // return triangle[0][0] + min(dp[0], dp[1]);
        // return dp[0];
    }
};

// ____________________________________________________________________________________________

// debugging code

# include<bits/stdc++.h>
using namespace std;

class Solution {
private:
    int inf = 1e9;
public:
    int n;
    vector<int> dp;
    vector<vector<int>> triangle;
    Solution(int _n, vector<vector<int>> a) : triangle(a), n(_n) 
    {
        dp.resize(n + 1, 0);
    }
public:
    int minimumTotal() {
        // printdp();
        for(int i = n - 1; i >= 0; i--)
        {
            for(int j = 0; j <= i; j++)
            // for(int j = i; j >= 0; j--)
            {
                // if(j == i) 
                // {
                //     dp[j] = triangle[i][j];
                //     continue;
                // }
                // assert(j + 1 < n and i < n);
                // dp[j] = dp[j] + min(triangle[i][j], triangle[i][j + 1]);
                dp[j] = triangle[i][j] + min(dp[j], dp[j + 1]);
            }
            printdp();
        }
        // return *min_element(dp.begin(), dp.end());
        return dp[0];
        // return dp[0] + triangle[0][0];
        // if(n == 1) return triangle[0][0];
        // return triangle[0][0] + min(dp[0], dp[1]);
        // return dp[0];
    }
    
    void printdp()
    {
        // cout<<"\n";
        for(auto &x : dp) cout<<x<<" ";
        cout<<"\n";
    }
};

int main()
{
    vector<vector<int>> a;
    int n = 4;
    a.resize(n);
    for(int i = 0; i < n; i++)
    a[i].resize(i + 1);
    for(auto &r : a)
    for(auto &c : r)
    cin>>c;
    Solution s(n, a);
    cout<<s.minimumTotal();
    // s.printdp();
}