// https://codeforces.com/contest/1142/problem/B

// Not a cup of tea! Follow throughout the process
// We could think of a naive solution, and it would get TLE
// Then we thought to know at which position we should go next in a to save time.
// So we stored the positions of all numbers in a in pos,
// and to know which number will come next in permutation p, 
// we stored their position in posinperm.

#include <bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
    int n,m,q;
    cin>>n>>m>>q;
    vector<int> p(n);
    vector<int> posinperm(n, -1);
    for(int i = 0; i < n; i++) 
    {
        cin>>p[i];
        p[i]--;
        posinperm[p[i]] = i;
    }
    vector<int> a(m);
    vector<vector<int>> pos(n);
    for(int i = 0; i < m; i++) 
    {
        cin>>a[i];
        a[i]--;
        pos[a[i]].push_back(i);
    }
    vector<int> nxt(m); // for next position of next permutation element in a
    // next permuting element is: p[posinperm[a[i]] + 1]
    // do binary search for its next position in a: lower_bound(pos[npe].begin(), pos[npe].end(), i)
    for(int i = 0; i < m; i++)
    {
        int npe = p[(posinperm[a[i]] + 1) % n];
        auto it = lower_bound(pos[npe].begin(), pos[npe].end(), i + 1); 
        // we are doing binary search on pos not a, so its return value is iterator from pos, not actual position of npe
        if(it == pos[npe].end()) nxt[i] = m;
        else nxt[i] = *it;
        // if element not found, next [i] = m - 0 = m, and we have valid elements in 0 to m - 1
    }
    int LOG = (int)log2(m) + 1;
    vector<vector<int>> binjump(m + 1, vector<int>(LOG, m));
    // You can also initialise by -1, but also do both lines below together
    // vector<vector<int>> binjump(m + 1, vector<int>(LOG, m));
    // binjump[m][0] = m;
    for(int i = 0; i < m; i++)
    binjump[i][0] = nxt[i];
    
    for(int j = 1; j < LOG; j++)
    for(int i = 0; i <= m; i++)
    binjump[i][j] = binjump[binjump[i][j - 1]][j - 1];
    
    int totaljumps = n - 1;
    vector<int> reached(m);
    for(int i = 0; i < m; i++)
    {
        int atpos = i;
        for(int j = 0; j < LOG; j++)
        {
            if((totaljumps>>j) & 1)
            {
                atpos = binjump[atpos][j];
            }
        }
        reached[i] = atpos;
    }
    
    int k = (int)log2(m) + 1;
    vector<vector<int>> sparse(k, vector<int>(m, -1));
    for(int j = 0; j < m; j++)
    sparse[0][j] = reached[j];
    for(int i = 1; i < k; i++)
    for(int j = 0; j + (1 << i) <= m; j++)
    sparse[i][j] = min(sparse[i - 1][j], sparse[i - 1][j + (1 << (i - 1))]);

    while(q--)
    {
        int l, r;
        cin>>l>>r;
        l--, r--;
        if(n > m)
        cout<<0;
        else
        {
            int i = log2(r - l + 1);
            int minimum = min(sparse[i][l], sparse[i][r - (1 << i) + 1]);
            if(minimum <= r)
            cout<<1;
            else
            cout<<0;
        }
    }
    cout<<"\n";
}