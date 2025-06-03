// https://atcoder.jp/contests/abc395/tasks/abc395_d


// More of mind-trick than DSU.
// Trick is you need to use 3 vectors to store three information
// box means position here, while label means the box number (which was alloted at begin to the boxes)
// eg: start: 1 4 3 5 2 (sequence of numbering given to nests at beginning)   
// after some swaps it becomes: *3* 4 1 2 5 -> now here 3 is label of the nest at position 1(box 1)
// 1st: pigeontobox, tells the pigeon is in which box at present
// 2nd: boxtolabel, tells this box contains which label 
// 3rd: labeltobox, tells this label is contained in which box

// since you are swapping so you need to interchange stored variables info(box/label), so you need to have both boxtolabel and labeltobox
// so that you can have the index to swap the values
// Also trick: instead of swapping pigeons, we swap nests


#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n,q;
    cin>>n>>q;
    //   vector<int> parentnest(2*n+1);
    //   vector<int> realnest(n+1);
    //   vector<int> realnestlocation(n+1);
    //   iota(parentnest.begin(),parentnest.end(),0);
    //   iota(realnest.begin(),realnest.end(),0);
    //   iota(realnestlocation.begin(),realnestlocation.end(),0);
    
    vector<int> pigeontobox(n+1);
    vector<int> labeltobox(n+1);
    vector<int> boxtolabel(n+1);
    iota(pigeontobox.begin(),pigeontobox.end(),0);
    iota(labeltobox.begin(),labeltobox.end(),0);
    iota(boxtolabel.begin(),boxtolabel.end(),0);
    
    //   for(auto i:realnest)cout<<i<<" ";

    //   for(int i=1;i<=n;i++)
    //   {
    //     parent[i]=i+n;
    //     parent[i+n]=i+n;
    //   }
    while(q--)
    {
        int qt;
        cin>>qt;
        if(qt==1) 
        {
            int a,b;
            cin>>a>>b;
            int labelposition=labeltobox[b];
            pigeontobox[a]=labelposition;
        //   realnest[a]=realnest[realnestlocation[b]];
        }
        if(qt==2) 
        {
            int a,b;
            cin>>a>>b;
        //   swap(realnest[realnestlocation[a]],realnest[realnestlocation[b]]);
        //   swap(realnestlocation[a],realnestlocation[b]);
            swap(boxtolabel[labeltobox[a]],boxtolabel[labeltobox[b]]);
            swap(labeltobox[a],labeltobox[b]);
        }
        if(qt==3) 
        {
            int a;
            cin>>a;
            cout<<boxtolabel[pigeontobox[a]]<<"\n";
        //   cout<<realnestlocation[realnest[a]]<<"\n";
        }
    }
}