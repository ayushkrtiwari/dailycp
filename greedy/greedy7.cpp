// https://codeforces.com/contest/632/problem/C

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