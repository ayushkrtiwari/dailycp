// https://leetcode.com/problems/minimum-cost-tree-from-leaf-values/description/

// very nice problem from my pov, even after learning dp so much, could not figure out equation :)

class Solution {
private:
    const int inf = 1e9;
// private:
//     struct node
//     {
//         int lmax = 0, rmax = 0, val = 1;
//     };
public:
    int mctFromLeafValues(vector<int>& arr) {
        // int ss = arr.size();
        // vector<vector<pair<int, int>>> dp(ss, vector<pair<int, int>>(ss, {0, 1}));
        // return value is {max, node value = leftmx * rightmx}
        // auto f = [&](int start, int end) -> pair<int, int>
        // {
            // if(start > end) return {0, 1};
            // if(end - start == 1) return {max(arr[start], arr[end]), arr[start] * arr[end]};
            // if(start == end) return {arr[start], arr[start]};
            // if(dp[start][end] != {0, 1}) return dp[start][end]; 
            // // int mn = inf;
            // pair<int, int> best = {0, 1};
            // for(int i = start + 1; i < end; i++)
            // {
            //     pair<int, int> left = f(start, i - 1);
            //     pair<int, int> right = f(i + 1, end);
            //     // mn = min(mn, left * right);
            //     pair<int, int> best = {max(left.first, right.first), left.first * right.first};
            // }
            // return dp[start][end] = best;
        // };
        // pair<int, int> ans = f(0, ss - 1);
        // return ans.first;
        int ss = arr.size();
        vector<vector<int>> dp(ss, vector<int>(ss, inf));
        // vector<int> mx(n, 0);
        // for(int i = 0; i < n; i++) mx[i] = max((i == 0 ? arr[0] : mx[i - 1]), arr[i]); 
        function<int(int, int)> mxm = [&](int start, int end)
        {
            int mx = 0;
            for(int i = start; i <= end; i++)
            mx = max(arr[i], mx);
            return mx;
        };
        function<int(int, int)> f = [&](int start, int end)
        {
            if(start > end) return 0;
            // if(start == end) return arr[start];
            if(start == end) return 0;
            if(dp[start][end] != inf) return dp[start][end];
            // assert(start >= 0 and end >= 0 and end < ss and start < ss);
            int mn = inf;
            for(int i = start; i < end; i++) // this wont be infinite loop due to recursive (start, start) since "< end" condn.
            mn = min(mn, f(start, i) + f(i + 1, end) + mxm(start, i) * mxm(i + 1, end));
            return dp[start][end] = mn;
        };
        int ans = f(0, ss - 1);
        return ans;
    }
};

// __________________________________________________________________________________________

// monotonic stack, by gpt
// this approach is working since : for every two elements as we move forward in array
// we do multiply the maxm 2 elements we encountered till now

class Solution {
public:
    int mctFromLeafValues(vector<int>& arr) {
        int res = 0;
        stack<int> st;
        st.push(INT_MAX); // sentinel
        for (int x : arr) {
            while (st.top() <= x) {
                int mid = st.top(); st.pop();
                res += min(st.top(), x) * mid;
            }
            st.push(x);
        }
        while (st.size() > 2) { // sentinel + one more left
            int mid = st.top(); st.pop();
            res += st.top() * mid;
        }
        return res;
    }
};
