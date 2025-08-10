// जय श्री राम  JAI SHREE RAM

// https://codeforces.com/group/DeilFl9Bhi/contest/329185/problem/A

// Basic Geometry, Template Practice

// Count number of points lying on both sides of Y-axis
// If any count is <= 1, solution possible else not

#include<bits/stdc++.h>
using namespace std;

template <class F>
struct Point {
    F x, y;
    Point() : x(0), y(0) {}
    Point(const F& x, const F& y) : x(x), y(y) {}
};

int main()
{
    int n;
    cin>>n;
    vector<Point<long long>> p(n);
    for(auto &e : p)
    cin>>e.x>>e.y;
    int posx = 0, negx = 0;
    for(auto &e : p)
    if(e.x > 0) posx++;
    else negx++;
    if(posx < 2 or negx < 2) cout<<"Yes";
    else cout<<"No";
}
