/*
描述
给定一系列的会议时间间隔intervals，包括起始和结束时间[[s1,e1],[s2,e2],...] (si < ei)，找到所需的最小的会议室数量。

您在真实的面试中是否遇到过这个题？  
样例
给出 intervals = [(0,30),(5,10),(15,20)], 返回 2.
*/

//关于Interval的重要解题思路: Break and sort
#include "LeetcodeTools.h"
using namespace leetcode;

class Solution {
public:
    int minMeetingRooms(vector<Interval> &intervals) {
        vector<pair<int, int>> times;
        for(int i = 0; i < intervals.size(); i++) {
            times.push_back(make_pair(intervals[i].start, true));
            times.push_back(make_pair(intervals[i].end, false));
        }
        // if at same time, the priority of leaving is higher than entering
        sort(times.begin(), times.end());

        int maxLivingCnt = -1;
        int livingCnt = 0;
        for(int i = 0; i < times.size(); i++) {
            if(times[i].second == true) { // starting
                livingCnt++;                
            }
            else { // end
                livingCnt--;
            }

            maxLivingCnt = max(maxLivingCnt, livingCnt);
        }

        return maxLivingCnt;
    }
};

int main () {
    Solution sol;
    vector<int> nums{0, 30, 5, 10, 15, 20};
    vector<Interval> intervals = buildIntervals(nums);
    cout << sol.minMeetingRooms(intervals) << endl;

    return 0;
}