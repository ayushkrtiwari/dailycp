// https://leetcode.com/problems/count-ways-to-choose-coprime-integers-from-rows/

// This overcounts for each divisor : like multiple of 15 is counted two times, one in 3 and other in 5
// wrong solution due to overcounting

# define MAXN 200
# define MOD 1000000007
vector<int> spf(MAXN, 1);
class Solution {
private:
    void spff()
    {
        for(int i = 2; i < MAXN; i++)
        {
            if(spf[i] != 1) continue;
            for(int j = i; j < MAXN; j += i)
            spf[j] = i;
        }
    }
    int binexp(int b, int e)
    {
        int res = 1;
        while(e)
        {
            if(e & 1) res = (res * b) % MOD;
            b = (b * b) % MOD;
            e >>= 1;
        }
        return res;
    }
public:
    int countCoprime(vector<vector<int>>& mat) {
        spff();
        int rs = mat.size();
        if(rs == 1)
        {
            int cnt1 = 0;
            for(auto &r : mat)
            for(auto &x : r)
            if(x == 1) cnt1++;
            return cnt1;
        }
        int cs = mat[0].size();
        vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149};
        // [rows, prime multiple in each row cnt]
        vector<vector<int>> cntrprime(150, vector<int>(150, 0));
        int ans = 0;
        vector<vector<int>> dp(rs, vector<int>(150, 0));
        for(int i = 0; i < rs; i++)
        {
            for(int j = 0; j < cs; j++)
            {
                int x = mat[i][j];
                while(x != 1)
                {
                    int f = spf[x];
                    dp[i][spf[x]]++;
                    while(x % f == 0)
                    x /= f;
                }
            }
        }
        for(int p = 2; p < 150; p++)
        {
            int gcdnot1 = 1;
            for(int r = 0; r < rs; r++)
            gcdnot1 = (gcdnot1 * dp[r][p]) % MOD;
            ans = (ans + gcdnot1) % MOD;
        }
        int total = binexp(cs, rs);
        return ((total - ans) % MOD + MOD) % MOD;
    }
};

// ___________________________________________________________________________________

// This uses mobius inversion, to remove overcounting
// Thus applies principle of inclusion exclusion
// Mobius removes overcounting as : 
// add all multiples of {1}, {2}, {3}, {4} ...
// then subtract all multiples of {1, 2}, {2, 3}, {1, 3}..
// then subtract all multiples of {1, 2, 3}, {2, 3, 4}, ...
// and so on. this way solving overcounting

// Mobius formula:
// if for n, there comes any 2 times same prime factor : mu(n) = 0
// if for n, there comes even times prime factors : mu(n) = 1
// if for n, there comes odd times prime factors : mu(n) = -1

// 0, since it would have been already contributed(added or subtracted)
// 1 since f(n) would be added like we added(see above) when there are odd times factors,
// -1 since f(n) would be subtracted like we subtracted when there are even times factors
// f(n) is what we are calculating using n, 
// like here we are calculating ways of getting gcd == n in the given matrix by performing operations as said

// directly by gpt :
// Möbius inversion / inclusion–exclusion works over distinct primes. 
// We add/subtract counts for sets divisible by single primes, 
// subtract/add back for intersections of distinct primes, and so on. 
// Combinations that involve the same prime twice (like requiring divisibility by 
// 2 and again by 2) don’t produce new independent constraints — that is why μ(d) is 0 for such d.

// Practically: selections that are divisible by 4 are already counted in ways(2) 
// (because being divisible by 4 implies divisible by 2). 
// Inclusion–exclusion will handle those via the μ(2) term (and μ(1) = +1 baseline). 
// The μ(4) coefficient is 0 because you would otherwise be trying to include/exclude the same prime twice, 
// which inclusion–exclusion does not do.

// so if you want gcd == 1, 
// f(1)=μ(1)⋅ways(1)+μ(2)⋅ways(2)+μ(4)⋅ways(4)=1−1+0=0

# define MAXN 200
# define MOD 1000000007
vector<int> spf(MAXN, 1);
class Solution {
private:
    vector<int> mobius_sieve(int maxv) 
    {
        vector<int> mu(maxv+1, 1), primes;
        vector<int> mind(maxv+1, 0);
        mu[0] = 0; // unused
        mu[1] = 1;
        for(int i = 2; i <= maxv; ++i) {
            if(!mind[i]) {
                mind[i] = i;
                primes.push_back(i);
                mu[i] = -1;
            }
            for(int p: primes) {
                int v = int(i) * p;
                if(v > maxv) break;
                mind[v] = p;
                if(i % p == 0) {
                    mu[v] = 0;
                    break;
                } else {
                    mu[v] = -mu[i];
                }
            }
        }
        return mu;
    }
public:
    int countCoprime(vector<vector<int>>& mat) {
        spff();
        vector<int> mobsieve = mobius_sieve(200);
        int rs = mat.size();
        if(rs == 1)
        {
            int cnt1 = 0;
            for(auto &r : mat)
            for(auto &x : r)
            if(x == 1) cnt1++;
            return cnt1;
        }
        int cs = mat[0].size();
        vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149};
        // [rows, prime multiple in each row cnt]
        vector<vector<int>> cntrprime(150, vector<int>(150, 0));
        int ans = 0;
        vector<vector<int>> dp(rs, vector<int>(151, 0));
        for(int i = 0; i < rs; i++)
        {
            for(int j = 0; j < cs; j++)
            {
                for(int k = 1; k <= mat[i][j]; k++)
                {
                    if(mat[i][j] % k == 0)
                    dp[i][k]++;
                }
            }
        }
        for(int p = 1; p <= 150; p++)
        {
            int gcdnot1 = 1;
            for(int r = 0; r < rs; r++)
            gcdnot1 = ((int64_t)gcdnot1 * dp[r][p]) % MOD;
            // ans = (ans + gcdnot1) % MOD;
            ans = (ans + ((mobsieve[p] * gcdnot1 % MOD) + MOD) % MOD) % MOD;
        }
        return ans;
    }
};

// __________________________________________________________________________________

// This is another implementation of mobius. 
// here we have just counted for all d = 2 to MAXN which gives us :
// - (multiples of (1, 2) + multiples of (2, 3) + multiples of (1, 2) + ..)
// + (multiples of (1, 2, 3) + multiples of (1, 2, 4) + ..)
// - (...) + (...) 
// it started with - since mobius of 2 is -1, since 2 has 2 divisors : 1, 2
// it would start with + if we had not taken divisor 1 while precomputing mobius
// hence our last answer is total combn - above calculated sum
// total combn is just cs ^ rs, which is just counting of all ways of taking numbers
// from each row divisible by 1, and when we subtract sum from it, we mean we are
// remove overcounting just by removing all other numbers like multiples of {1, 2}, {1, 3} and so on
// then again adding multiples of {1, 2, 3}, {1, 2, 3} and so on and then again subtracting
// multiples of {1, 2, 3, 4}, {1, 2, 4, 5} and so on

# define MAXN 200
# define MOD 1000000007
vector<int> spf(MAXN, 1);
class Solution {
private:
    void spff()
    {
        for(int i = 2; i < MAXN; i++)
        {
            if(spf[i] != 1) continue;
            for(int j = i; j < MAXN; j += i)
            spf[j] = i;
        }
    }
    int binexp(int b, int e)
    {
        int res = 1;
        while(e)
        {
            if(e & 1) res = (res * b) % MOD;
            b = (b * b) % MOD;
            e >>= 1;
        }
        return res;
    }
    vector<int> mobius_sieve(int maxv) 
    {
        vector<int> mu(maxv+1, 1), primes;
        vector<int> mind(maxv+1, 0);
        mu[0] = 0; // unused
        mu[1] = 1;
        for(int i = 2; i <= maxv; ++i) {
            if(!mind[i]) {
                mind[i] = i;
                primes.push_back(i);
                mu[i] = -1;
            }
            for(int p: primes) {
                int v = int(i) * p;
                if(v > maxv) break;
                mind[v] = p;
                if(i % p == 0) {
                    mu[v] = 0;
                    break;
                } else {
                    mu[v] = -mu[i];
                }
            }
        }
        return mu;
    }
public:
    int countCoprime(vector<vector<int>>& mat) {
        spff();
        vector<int> mobsieve = mobius_sieve(200);
        int rs = mat.size();
        if(rs == 1)
        {
            int cnt1 = 0;
            for(auto &r : mat)
            for(auto &x : r)
            if(x == 1) cnt1++;
            return cnt1;
        }
        int cs = mat[0].size();
        vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149};
        // [rows, prime multiple in each row cnt]
        // vector<vector<int>> cntrprime(150, vector<int>(150, 0));
        int ans = 0;
        vector<vector<int>> dp(rs, vector<int>(151, 0));
        for(int i = 0; i < rs; i++)
        {
            for(int j = 0; j < cs; j++)
            {
                // int x = mat[i][j];
                // dp[i][1]++;
                // while(x != 1)
                // {
                //     int f = spf[x];
                //     dp[i][spf[x]]++;
                //     while(x % f == 0)
                //     x /= f;
                // }
                for(int k = 2; k <= mat[i][j]; k++)
                {
                    if(mat[i][j] % k == 0)
                    dp[i][k]++;
                }
            }
        }
        for(int p = 2; p <= 150; p++)
        {
            int gcdnot1 = 1;
            for(int r = 0; r < rs; r++)
            gcdnot1 = ((int64_t)gcdnot1 * dp[r][p]) % MOD;
            // ans = (ans + gcdnot1) % MOD;
            ans = (ans + ((mobsieve[p] * gcdnot1 % MOD) + MOD) % MOD) % MOD;
        }
        int total = binexp(cs, rs);
        // return ((total - ans) % MOD + MOD) % MOD; this is wrong mobius implementation
        return (((total + ans) % MOD) + MOD) % MOD;
    }
};