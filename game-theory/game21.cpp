// https://cses.fi/problemset/task/2208

// If all x[i] are even, then every move subtracts 1 from some subset of heaps, 
// turning each chosen heap from even→odd. But since you must choose at least one heap, 
// you’ll always leave at least one odd heap for your opponent. 
// By symmetry the opponent can always “mirror” your choice of which heaps
// to remove from (removing from the same subset), restoring all heaps back to even. 
// Eventually you’ll face the all-zero position and lose.

#include<bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        vector<int> x(n);
        for(auto &e : x)
        cin>>e;
        bool firstwin = false;
        for(auto &e : x)
        if(e % 2)
        {
            firstwin = true;
            break;
        }
        cout<<(firstwin ? "first\n" : "second\n");
    }
}