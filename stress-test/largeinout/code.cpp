#include <bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
    int t;
    cin>>t;
    for(int tt = 1; tt <= t; tt++)
    {
        int n;
        cin>>n;
        vector<int> a(n);
        for(auto &x : a) cin>>x;
        int mx = 0;
        for(int i = 0; i < n - 1; i++)
        mx = max(mx, abs(a[i] - a[i + 1]));
        cout<<"Case #"<<tt<<": "<<mx<<"\n";
    }
}
