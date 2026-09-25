#include<bits/stdc++.h>
using namespace std;

int randno(int a, int b)
{
    return a + (rand() % (b - a + 1));
}

pair<int, int> finduniquecord(const set<pair<int, int>> &s, int a, int b)
{
    pair<int, int> uniquecoor = {randno(a, b), randno(a, b)};
    if(s.find(uniquecoor) != s.end()) return finduniquecord(s, a, b);
    else  return uniquecoor;
}

int main()
{
    srand(time(0));
    int sqbrdl = randno(1, 40);
    cout<<sqbrdl<<"\n";
    pair<int, int> coordb = {randno(1, 40), randno(1, 40)};
    cout<<coordb.first<<" "<<coordb.second<<"\n";
    int n = randno(1, 200);
    cout<<n<<"\n";
    set<pair<int,int>> cord;
    while(n--)
    {
        pair<int, int> coorpr = finduniquecord(cord, 1, 40);
        cout<<coorpr.first<<" "<<coorpr.second<<" "<<randno(0, 1)<<" \n"[n != 0];
    }
}