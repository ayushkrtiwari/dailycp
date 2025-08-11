// https://codeforces.com/group/DeilFl9Bhi/contest/329185/problem/B

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
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        vector<Point<int>> p(n);
        for(auto &e : p)
        cin>>e.x;
        set<int> lengths;
        for(int i = 0; i < n; i++)
        {
            for(int j = i + 1; j < n; j++)
                lengths.insert(abs(p[i].x - p[j].x));
        }
        cout<<lengths.size()<<"\n";
    }
}
