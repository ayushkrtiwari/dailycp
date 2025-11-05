#include <bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
    int t = 1;
    // cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        string s;
        cin>>s;
        int i = 0;
        int cnt0, cnt1;
        cnt0 = cnt1 = 0;
        int c = 0;
        bool is1start = false;
        while(s[i] == '1') 
        {
            is1start = true;
            i++;
        }
        for(; i < n; i++)
        {
            if(i > 0 and s[i - 1] == '1' and s[i] == '0')
            {
                if(cnt1 != cnt0) c++;
                cnt0 = cnt1 = 0;
            }
            if(s[i] == '0') cnt0++;
            else cnt1++;
        }
        if(cnt1 != cnt0) c++;
        if(n == 1) cout<<1<<"\n";
        else
        cout<<c + (is1start ? 1 : 0)<<"\n";
    }
}
