// https://www.hackerrank.com/contests/5-days-of-game-theory/challenges/tower-breakers

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int t;
    cin>>t;
    while(t--)
    {
        int n, m;
        cin>>n>>m;
        if(m == 1 or n % 2 == 0)
            cout<<"2\n";
        else
            cout<<"1\n";
    }
    return 0;
}