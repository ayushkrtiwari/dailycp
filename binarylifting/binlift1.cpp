// https://cses.fi/problemset/task/1687

#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,q;
    cin>>n>>q;
    int col = (int)log2(n) + 1;
    vector<vector<int>> binlift(n + 1, vector<int>(col, -1));
    for(int i = 2; i <= n; i++)
    cin>>binlift[i][0];
    for(int c = 1; c < col; c++)
    for(int i = 2; i <= n; i++)
    if(binlift[i][c - 1] != -1 and binlift[binlift[i][c - 1]][c - 1])
    binlift[i][c] = binlift[binlift[i][c - 1]][c - 1];
    while(q--)
    {
        int emp, k;
        cin>>emp>>k;
        int x = col;
        // int ans = -1;
        for(int i = 0; i <= x; i++)
        if(k & (1<<i))
        if(binlift[emp][i] == -1) 
        {
            emp = -1;
            break;
        }
        else
        emp = binlift[emp][i];
        cout<<emp<<"\n";
    }
}