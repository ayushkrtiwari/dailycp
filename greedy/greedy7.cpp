// जय श्री राम                              JAI SHREE RAM

// https://codeforces.com/contest/632/problem/C

// Exchange Argument, Sorting
// Trick: To sort lexicographically the string vector,
// just check if my first ordering is better than second.
// A + B < B + A -> return order A,B else B,A

#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    vector<string> str;
    string s;
    while(cin>>s)
    {
        str.push_back(s);
    }
    sort(str.begin(),str.end(),[](const string &A, const string &B)
    {
        return A+B<B+A;
    });
    string ansstr = "";
    int ss = str.size();
    for(int i=0;i<ss;i++)
    {
        ansstr = ansstr + str[i];
    }
    cout<<ansstr<<"\n";
}