// https://atcoder.jp/contests/abc178/tasks/abc178_f

// Derangement, No Overlap Intersection, Disjoint Interval, Cyclic Shift, All possible rotation values

// For each number, there will be 1 segment both in A and B of length >= 0. 
// You need to shift by a number say x. 
// Sort the array with taking elements as pair to keep info of index as : {element, index}


#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n;
    cin>>n;
    vector<int> a(n),b(n);
    for(auto &x:a) cin>>x;
    for(auto &x:b) cin>>x;
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    vector<int> lesstilla(n+1,0),lesstillb(n+1,0);
    for(int i = 0; i < n; i++)
    {
        lesstilla[a[i]]++;
        lesstillb[b[i]]++;
    }
    for(int i = 1; i < n + 1; i++)
    {
        lesstilla[i] += lesstilla[i - 1];
        lesstillb[i] += lesstillb[i - 1];
    }
    vector<int> L(n + 1), R(n + 1);
    for(int i = 1; i < n + 1; i++)
    {
        L[i] = lesstilla[i] - lesstillb[i - 1];
        R[i] = lesstilla[i - 1] + n - lesstillb[i];
    }
    int mxL = *max_element(L.begin() + 1, L.end());
    int mnR = *min_element(R.begin() + 1, R.end());
    int possiblex;
    if(mnR < mxL)
    {
        cout<<"No\n";
        return;
    }
    else
    {
        possiblex = mxL; // x has all possible values from mxL to mnR
        // rotate array by x right
        vector<int> res(n);
        for(int i = 0; i < n; i++)
        res[i] = b[(((i - possiblex) % n) + n) % n];
        
        cout<<"Yes\n";
        for(auto v: res)
        cout<<v<<" ";
        cout<<"\n";
    }
}

int main() {
	// your code goes here
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
}
