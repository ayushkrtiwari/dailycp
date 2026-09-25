// https://leetcode.com/problems/last-stone-weight-ii

// TLE

class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int n = stones.size();
        int mx = 0;
        int total = accumulate(stones.begin(), stones.end(), 0);
        int target = total / 2;
        function<void(int, int)> f = [&](int idx, int sum)
        {
            if(sum > target) return;
            if(idx == n) 
            {
                mx = max(mx, sum);
                return;
            }
            f(idx + 1, sum + stones[idx]);
            f(idx + 1, sum);
        };
        f(0, 0);
        return total - 2 * mx;
    }
};

// ______________________________________________________________________

// meet in the middle

class Solution {
private:
    void generatesum(vector<int> &sumv, vector<int> &v)
    {
        int sum = 0;
        int sz = v.size();
        int total = 1 << sz;
        for(int i = 0; i < total; i++)
        {
            int sm = 0;
            for(int j = 0; j < sz; j++)
            if(j & (1 << j))
            sm += v[j];
            sumv.push_back(sm);
        }
        sort(sumv.begin(), sumv.end());
        sumv.erase(unique(sumv.begin(), sumv.end()), sumv.end());
        // return sumv;
    }
public:
    int lastStoneWeightII(vector<int>& stones) {
        int n = stones.size();
        int n1 = n / 2;
        int n2 = n - n1;
        int totalsum = accumulate(stones.begin(), stones.end(), 0);
        vector<int> stones1(n1), stones2(n2);
        for(int i = 0; i < n1; i++)
        stones1[i] = stones[i];
        for(int i = n1; i < n; i++)
        stones2[i - n1] = stones[i];
        vector<int> newsum1, newsum2;
        generatesum(newsum1, stones1);
        generatesum(newsum2, stones2);
        int mn = INT_MAX;
        int sz1 = newsum1.size();
        int sz2 = newsum2.size();
        for(int i = 0; i < sz1; i++)
        {
            int sm1 = newsum1[i];
            int calci = lower_bound(newsum2.begin(), newsum2.end(), totalsum / 2 - sm1) - newsum2.begin();
            mn = min(mn, newsum2[calci] + sm1);
        }
        return 2 * mn - totalsum;
    }
};

/** 
        Using lower bound, target greater than mid

        int mn = INT_MAX;
        // int mx = 0;
        int sz1 = newsum1.size();
        int sz2 = newsum2.size();
        for(int i = 0; i < sz1; i++)
        {
            int sm1 = newsum1[i];
            auto calci = lower_bound(newsum2.begin(), newsum2.end(), totalsum / 2 - sm1);
            if(calci == newsum2.end()) continue;
            mn = min(mn, *calci + newsum1[i]);
            // if(calci == 0) continue;
            // calci--;
            // mx = max(mx, sm1 + newsum2[calci]);
        }
        return abs(2 * mn - totalsum);
*/

// ___________________________________________________________________________________________

class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int n = stones.size();
        int sm = accumulate(stones.begin(), stones.end(), 0);
        int target = sm / 2;
        vector<vector<int>> best(n + 1, vector<int>(3005, -1));
        auto f = [&](auto self, int idx, int sum) -> int
        {
            if(idx == n) return sum;    
            if(best[idx][sum] != -1) return best[idx][sum];
            int bst = self(self, idx + 1, sum);
            if(sum + stones[idx] <= target)
            bst = max(bst, self(self, idx + 1, sum + stones[idx]));
            // take sum only when sum <= target
            return best[idx][sum] = bst;
        };
        int fnd = f(f, 0, 0);
        return abs(sm - 2 * fnd);
    }
};