#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("tests.txt","r",stdin);
    freopen("ans.txt","w",stdout);


    long long x, y;
    // read point; if running locally you can type into stdin,
    // in contest you’ll redirect from angle1.in
    while(cin>>x>>y)
    {
        // Compute angle in [-π, +π]
        long double ang = atan2((long double)y, (long double)x);
        // Shift negatives up to [0, 2π)
        if (ang < 0) ang += 2 * acosl(-1.0L);

        // Print exactly 5 decimal places
        // (you can also do: cout<<fixed<<setprecision(5)<< (double)ang; )
        printf("%.5Lf\n", ang);
    }
    return 0;
}
