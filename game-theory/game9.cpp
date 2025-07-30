// https://www.hackerrank.com/contests/5-days-of-game-theory/challenges/tower-breakers-3/problem

#include <bits/stdc++.h>
using namespace std;
static constexpr int MAXN = 1e5 + 2;
vector<int> grundy(MAXN);

int findmex(set<int> &mex)
{
    int cnt = 0;
    for(auto &x : mex)
        if(cnt != x) return cnt;
        else cnt++;
    return cnt;
}

void precompute()
{
    grundy[0] = 0, grundy[1] = 0;
    for(int i = 2; i < MAXN; i++)
    {
        // int xorg = 0;
        set<int> mex;
        for(int j = 2; j * j <= i; j++)
        {
            if(i % j) continue;
            int div1 = j, div2 = i/j;
            if(div1 % 2 and div2 % 2)
            mex.insert(grundy[div1]), mex.insert(grundy[div2]);
            else if(div1 % 2) mex.insert(grundy[div2]);
            else if(div2 % 2) mex.insert(grundy[div1]);
            else mex.insert(0);
        }
        mex.insert(0); // since when broken into parts of 1 then grundy will be 0
        grundy[i] = findmex(mex);
        mex.clear();
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    precompute();
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        vector<int> h(n);
        for(auto &x:h) cin>>x;
        // for(auto &x:h) x = grundy[x];
        int xorg = 0;
        for(auto &x: h) xorg ^= grundy[x];
        if(xorg) cout<<"1\n";
        else cout<<"2\n";
    }
    // for(int x = 0; x < 101; x++) cout<<grundy[x]<<" ";
    return 0;
}

// _____________________________________________________________________________________

#include <bits/stdc++.h>
using namespace std;
static constexpr int MAXN = 1e5 + 2;
vector<int> grundy(MAXN);

int findmex(set<int> &mex)
{
    int cnt = 0;
    for(auto &x : mex)
        if(cnt != x) return cnt;
        else cnt++;
    return cnt;
}

void precompute()
{
    grundy[0] = 0, grundy[1] = 0;
    for(int i = 2; i < MAXN; i++)
    {
        // int xorg = 0;
        set<int> mex;
        for(int j = 2; j * j <= i; j++)
        {
            if(i % j) continue;
            int div1 = j, div2 = i/j;
            if(div1 % 2 and div2 % 2)
            mex.insert(grundy[div1]), mex.insert(grundy[div2]);
            else if(div1 % 2) mex.insert(grundy[div2]);
            else if(div2 % 2) mex.insert(grundy[div1]);
            else mex.insert(0);
        }
        mex.insert(0); // since when broken into parts of 1 then grundy will be 0
        grundy[i] = findmex(mex);
        mex.clear();
    }
}

int winpossible(int n, int xorall, vector<int> &h)
{
    for(auto &x:h)
    {
        xorall ^= grundy[x];
        // These below commented lines are what my thought process gone wrong at start

        // set<int> mex;
        // // now find whether we can make this xorall by any step in one turn
        // for(int j = 2; j * j <= x; j++)
        // {
        //     if(x % j) continue;
        //     int div1 = j, div2 = x/j;
        //     if(div1 % 2 and div2 % 2)
        //     mex.insert(grundy[div1]), mex.insert(grundy[div2]);
        //     else if(div1 % 2) mex.insert(grundy[div2]);
        //     else if(div2 % 2) mex.insert(grundy[div1]);
        //     else mex.insert(0);
        // }
        // if(x % 2) mex.insert(1);
        // int xrr = findmex(mex);
        for(int j = 2; j * j <= x; j++)
        {
            if(x % j) continue;
            int div1 = j, div2 = x/j;
            if(div1 % 2 and div2 % 2)
                if(grundy[div1] == xorall or grundy[div2] == xorall) return 1;
            else if(xorall == 0) return 1;
            else if(div1 % 2)
                if(grundy[div2] == xorall) return 1;
            else if(div2 % 2)
                if(grundy[div1] == xorall) return 1;
        }
        // edge case divisor 1
        if(x % 2 and xorall == 0) return 1;
        xorall ^= grundy[x];
    }
    return 0;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    precompute();
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        vector<int> h(n);
        for(auto &x:h) cin>>x;
        // for(auto &x:h) x = grundy[x];
        int xorg = 0;
        for(auto &x: h) xorg ^= grundy[x];
        int win = winpossible(n, xorg, h);
        if(win) cout<<"1\n";
        else cout<<"2\n";
    }
    // for(int x = 0; x < 101; x++) cout<<grundy[x]<<" ";
    return 0;
}
