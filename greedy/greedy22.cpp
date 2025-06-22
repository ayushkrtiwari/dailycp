// https://codeforces.com/problemset/problem/2052/A

// Topic: Exchange Argument, Sorting
// Trick: Most of the part is answered in comments. Just this is unique sorting problem

#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    vector<int> c(n);
    for(auto &x: c)
    cin>>x;
    vector<pair<int,int>> res;
    // a to c will take more time complexity
    // c to a is fast since positions in a is known 
    // if you are traversing forward, do cars backward or vice-versa.
    
    // the above points are wrong, since you can check if element has reached position in c
    // for(int i = 0; i < n; i++)
    // {
    //     for(int j = i; j > 0; j--)
    //     {
    //         // assert(c[j] > 0 and c[j - 1] > 0);
    //         res.push_back({c[j], c[j - 1]});
    //         swap(c[j], c[j - 1]);
    //     }
    //     int x = c[0] - 1;
    //     for(int j = 0; j < x; j++)
    //     {
    //         // assert(c[j] > 0 and c[j + 1] > 0);
    //         res.push_back({c[j], c[j + 1]});
    //         swap(c[j], c[j + 1]);
    //     }
    // }
    
    // this above method will produce wrong result since say:
    // you are at i = 2, and swapped element x to 4 then when you reach 4, you again start swapping it
    // thus this produces wrong result
    // so instead of swapping it together, swap both processes independently, that is one at a time
    
    // so below we will first sort c into decreasing order and then afterwards we sort into ascending
    
    // 5 1 2 4 3
    
    for(int i = 0; i < n; i++) // if traversing forward, swap elements backward so you dont encounter them again
    {
        while(i > 0 and c[i - 1] < c[i]) // swap elements if they are in wrong order else break out. This will bring them in correct order(desc)
        {
            res.push_back({c[i - 1], c[i]});
            swap(c[i - 1], c[i]);
            i--;
        }
    }
    
    // 5 4 3 2 1
    
    for(int i = n - 1; i >= 0; i--)
    {
        while(i < n - 1 and c[i + 1] < c[i])
        {
            res.push_back({c[i], c[i + 1]});
            swap(c[i], c[i + 1]);
            i++;
        }
    }
    
    // 1 2 3 4 5
    
    cout<<res.size()<<"\n";
    
    for(auto r = res.rbegin(); r < res.rend(); r++)
    cout<<r->first<<" "<<r->second<<"\n";
}