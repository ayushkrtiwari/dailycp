// https://codeforces.com/contest/2135/problem/D1

// do not flush each time at output
// flush when you want to give judge to read the output

#include<bits/stdc++.h>
using namespace std;
int32_t main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t;
    cin>>t;
    while(t--)
    {
        cout<<"? "<<100000<<" ";
        for(int i = 0; i < 100000; i++)
        cout<<1<<" \n"[i == 99999];
        // cout<<"\n";
        cout.flush();
        int lines;
        cin>>lines;
        assert(lines > 0);
        int n = 100000;
        if(lines == 1) // * missed this part
        {
            cout<<"! "<<n<<"\n";
            cout.flush();
            continue;
        }
        int l = ceil(n / (long double)lines);
        int u = floor((n - 1) / (long double)(lines - 1)); 
        // taking just before upper bound to avoid inclusion of upper bound, hence floor
        cout<<"? "<<(u - l + 1) * 2<<" ";
        for(int i = 1; i <= u - l + 1; i++)
        cout<<l<<" "<<i<<" \n"[i == u - l + 1];
        cout.flush();
        // cout<<"\n"<<flush;
        cin>>lines;
        assert(lines >= 0);
        // int doubles = lines - (r - l + 1) * 2;
        int singles = (u - l + 1) * 2 - lines;
        cout<<"!"<<" "<<l + singles<<"\n";
        cout.flush();
    }
}