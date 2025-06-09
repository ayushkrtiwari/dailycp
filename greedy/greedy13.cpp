// https://codeforces.com/problemset/problem/979/B

// Trick: It's easy to observe for N < rem.

#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    string s1,s2,s3;
    cin>>s1>>s2>>s3;
    int s = s1.size();
    vector<int> fs1(52,0),fs2(52,0),fs3(52,0); // a-z, A-Z
    bool isallusedup1 = true, isallusedup2 = true, isallusedup3 = true;
    for(int i=0;i<s;i++)
    {
        if(s1[i]>=97 and s1[i]<=122) fs1[s1[i]-'a']++;
        else fs1[s1[i]-'A'+26]++;
        if(s2[i]>=97 and s2[i]<=122) fs2[s2[i]-'a']++;
        else fs2[s2[i]-'A'+26]++;
        if(s3[i]>=97 and s3[i]<=122) fs3[s3[i]-'a']++;
        else fs3[s3[i]-'A'+26]++;
    }
    
    // for(int i=0;i<52;i++)
    // {
    //     if(fs1[i]==0) isallusedup1 = false;
    //     if(fs2[i]==0) isallusedup2 = false;
    //     if(fs3[i]==0) isallusedup3 = false;
    // }

    int mxf1 = *max_element(fs1.begin(),fs1.end());
    int mxf2 = *max_element(fs2.begin(),fs2.end());
    int mxf3 = *max_element(fs3.begin(),fs3.end());
    
    int cnt1 = 0, cnt2 = 0, cnt3 = 0;
    
    if(mxf1 == s)  
    {
        if(n == 1)
        cnt1 = mxf1 - 1;
        else
        cnt1 = mxf1;
    }
    else
    {
        int rem = s - mxf1;
        if(n < rem)
        cnt1 = mxf1 + n;
        else
        {
            // cnt1 = s - (n-rem)%2;
            // if(n >= rem + s)
            // {
            //     // what if we can do rem and whole s again
            //     cnt1 = max(cnt1,s - (n - (rem + s)%2));
            // }
            cnt1 = s;
        }
    }
    if(mxf2 == s)
    {
        if(n == 1)
        cnt2 = mxf2 - 1;
        else
        cnt2 = mxf2;
    }
    else
    {
        int rem = s - mxf2;
        if(n < rem)
        cnt2 = mxf2 + n;
        else
        {
            cnt2 = s;
            // cnt2 = s - (n-rem)%2;
            // if(n >= rem + s)
            // {
            //     cnt2 = max(cnt2,s - (n - (rem + s)%2));
            // }
        }
    }
    if(mxf3 == s)
    {
        if(n==1)
        cnt3 = mxf3 - 1;
        else
        cnt3 = mxf3;
    }
    else
    {
        int rem = s - mxf3;
        if(n < rem)
        cnt3 = mxf3 + n;
        else
        {
            cnt3 = s;
            // cnt3 = s - (n-rem)%2;
            // if(n >= rem + s)
            // {
            //     cnt3 = max(cnt3,s - (n - (rem + s)%2)); 
            // }
        }
    }
    
    // if(n >= s)              // what if we change whole string once
    // {
    //     cnt1 = max(cnt1,s - ((n-s)%2));
    //     cnt2 = max(cnt2,s - ((n-s)%2));
    //     cnt3 = max(cnt3,s - ((n-s)%2));
    // }
    
    // if(n - 2*s >= 0)         // what if we change whole string twice
    // {
    //     cnt1 = max(cnt1,(s - (n-2*s)%2));
    //     cnt2 = max(cnt2,(s - (n-2*s)%2));
    //     cnt3 = max(cnt3,(s - (n-2*s)%2));
    // }
    
    // what if no different letters are there from unchanged ones
    
    // if(isallusedup1)
    // {
    //     cnt1 = mxf1;
    // }
    // if(isallusedup2)
    // {
    //     cnt2 = mxf2;
    // }
    // if(isallusedup3)
    // {
    //     cnt3 = mxf3;
    // }
    
    if(max(cnt1,cnt2) == cnt3 or max(cnt2,cnt3) == cnt1 or max(cnt3,cnt1) == cnt2)
    cout<<"Draw\n";
    else if(cnt1 > max(cnt2,cnt3))
    cout<<"Kuro\n";
    else if(cnt2 > max(cnt1,cnt3))
    cout<<"Shiro\n";
    else if(cnt3 > max(cnt1,cnt2))
    cout<<"Katie\n";
    
    // cout<<s<<" "<<cnt1<<" "<<cnt2<<" "<<cnt3<<"\n";
    // for(auto i:fs1)
    // cout<<i<<" ";
    // cout<<"\n";
    // for(auto i:fs2)
    // cout<<i<<" ";
    // cout<<"\n";
    // for(auto i:fs3)
    // cout<<i<<" ";
    // cout<<"\n";
}