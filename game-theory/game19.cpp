// https://cses.fi/problemset/task/1099

// In 1-indexed
// On odd positions, any no of ball you bring to lower position, the move will be copied by same amount of balls by opponent
// Thus only even positions account for grundy values
// SG value of a stair is the no of balls on it, since it acts as a stone pile
// Thus taking nim sum gives the winner in optimal play

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
        vector<int> p(n);
        for(auto &x : p)
        {
            cin>>x;
            // x %= 2;
        }
        int nim = 0;
        for(int i = 1; i < n; i++)
        {
            if(i % 2)
            nim ^= p[i];
        }
        if(nim) cout<<"first\n";
        else cout<<"second\n";
    }
}