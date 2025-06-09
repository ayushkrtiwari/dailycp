// https://atcoder.jp/contests/abc109/tasks/abc109_d#:~:text=Operation%3A%20Choose%20a%20cell%20that%20was%20not%20chosen,of%20coins.%20All%20values%20in%20input%20are%20integers.


// Dimension Reduction: Reduce trees into array or 2D into 1D

#include<bits/stdc++.h>
using namespace std;
int main()
{
    int h,w;
    cin>>h>>w;
    vector<vector<int>> v(h,vector<int>(w));
    for(int i=0;i<h;i++)
    for(int j=0;j<w;j++)
    cin>>v[i][j];
    
    
    // question proposes condition not to revisit a cell
    // walk in snake traversal
    
    int lasti = -1, lastj = -1;
    int odd = 0;
    vector<pair<pair<int,int>,pair<int,int>>> res;
    for(int i=0;i<h;i++)
    {
        if(i%2==0)
        {
            for(int j=0;j<w;j++)
            {
                if(odd)
                {
                    res.push_back({{lasti,lastj},{i,j}});   
                    // You can directly print this instead of storing but you do need to have number of operations to print
                }
                odd ^= v[i][j]%2;
                lasti = i, lastj = j;
            }
        }
        else
        {
            for(int j=w-1;j>=0;j--)
            {
                if(odd)
                {
                    res.push_back({{lasti,lastj},{i,j}});
                }
                odd ^= v[i][j]%2;
                lasti = i, lastj = j;
            }
        }
    }
    cout<<res.size()<<"\n";
    for(auto i:res)
    cout<<i.first.first+1<<" "<<i.first.second+1<<" "<<i.second.first+1<<" "<<i.second.second+1<<"\n";
}