// https://atcoder.jp/contests/abc178/tasks/abc178_f

// One pass, two pointer, Group aware, Greedy Swap

// Both array may or may not be distinct but equal length
// O(N) not O(N^2) 
// When a[i] is same as old, j will only move forward and never becomes j = 0, thus one iteration 
// When a[i] is new, j = 0 and this happens for all distinct a[i] values. But the exchange element in found in few steps only
// and takes max step when searching exchange element for a[i] with maxf. So in total O(N)

// GPT: You only scan j when you actually have a conflict a[i] == b[i]. If there’s no conflict, you don’t touch j.
// Within a single block of equal a[i] values, j only moves forward and never backtracks, 
// so total work is bounded by “length of block + total pointer advances.” 
// And since each j gets incremented at most once per failed check, 
// you end up doing at most one full pass of j over 0…n−1 across that block.
// When you switch to a new block, you reset j=0, but that only happens once per distinct value in A. 
// In the worst case (all A[i] distinct) you do that reset 
// n times—but notice in that scenario almost never will b[i]==a[i] 
// except exactly when i equals the index of the global maximum of B or its duplicates. 
// So you’ll rarely enter the inner for(;j<n;j++) loop, and when you do, you exit it in one or two steps.
// Putting it all together, each conflict triggers at most one forward scan of j until you find a valid partner (or fail), 
// and across the entire run j never moves backwards inside the block. That guarantees an amortized 
// O(n) total cost.

#include<bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin>>n;
    vector<int> a(n),b(n);
    for(auto &x:a) cin>>x;
    for(auto &x:b) cin>>x;
    int before = -1;
    int j = 0;
    for(int i = 0; i < n; i++)
    {
        if(before != a[i]) j = 0;
        if(a[i] == b[i])
        {
            for(; j < n; j++)
            {
                if(a[i] != a[j] and a[i] != b[j])
                {
                    swap(b[i], b[j]);
                    break;
                }
            }
            if(a[i] == b[i])
            {
                cout<<"No\n";
                return 0;
            }
        }
        before = a[i];
    }
    cout<<"Yes\n";
    for(auto i:b)
    cout<<i<<" ";
    cout<<"\n";
}