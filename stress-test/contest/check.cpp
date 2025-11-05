#include<bits/stdc++.h>
using namespace std;
int32_t main()
{
    vector<int> a(20);
    for(auto &x : a) cin>>x;
    vector<pair<bool, int>> pass(200000, {false, 0});
    int total = 1 << 20;
    for(int i = 0; i < total; i++)
    {
        int sum = 0, passtime = 0;
        for(int mask = 0; mask < 20; mask++)
        {
            if((1 << mask) & i)
            sum += a[mask], passtime++;
        }
        pass[sum] = {true, passtime};
        // passtime = 0;
    }
    for(int i = 0; i < 50005; i++)
    if(pass[i].second > 10 or !pass[i].first) cout<<i<<" \n"[i == 50004];
    cout<<"done";
}