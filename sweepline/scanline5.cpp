// https://leetcode.com/problems/my-calendar-iii/description/

class MyCalendarThree {
public:
    map<int,int> m;
    MyCalendarThree() {
        // map<int,int> m;
    }
    
    int book(int startTime, int endTime) {
        m[startTime]++;
        m[endTime]--;
        int cnt=0;
        int mxcnt=0;
        for(auto i:m)
        {
            cnt+=i.second;
            mxcnt=max(mxcnt,cnt);
        }
        return mxcnt;
    }
};

/**
 * Your MyCalendarThree object will be instantiated and called as such:
 * MyCalendarThree* obj = new MyCalendarThree();
 * int param_1 = obj->book(startTime,endTime);
 */