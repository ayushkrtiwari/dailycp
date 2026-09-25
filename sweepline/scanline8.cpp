// https://www.naukri.com/code360/problems/minimum-number-of-platforms_799400

int calculateMinPatforms(int at[], int dt[], int n) {
    // Write your code here.
    
    vector<int> v(2500,0);
    for(int i=0;i<n;i++)
    {
        int x=at[i];
        v[x]++;
    }
    for(int i=0;i<n;i++)
    {
        int y=dt[i];
        v[y+1]--;
    }
    int sum=0;
    int mxsum=0;
    for(int i=0;i<2500;i++)
    {
        sum+=v[i];
        mxsum=max(sum,mxsum);
    }
    return mxsum;
}