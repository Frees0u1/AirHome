/*
描述
将K个排序的间隔列表合并到一个排序的间隔列表中，你需要合并重叠的间隔。

您在真实的面试中是否遇到过这个题？  
样例
给定：

[
  [(1,3),(4,7),(6,8)],
  [(1,2),(9,10)]
]
返回

[(1,3),(4,8),(9,10)]

*/
#include "../LeetcodeTools.h"
using namespace leetcode;

class Solution {
public:
    /**
     * @param intervals: the given k sorted interval lists
     * @return:  the new sorted interval list
     */
    vector<Interval> mergeKSortedIntervalLists(vector<vector<Interval>> &intervals) {
        vector<Interval> result;
        int n = intervals.size(); if(0 == n) return result;

        auto cmp = [&intervals](pair<int, int>& lhs, pair<int, int>& rhs) { // first idx; second is row idx
            return intervals[lhs.first][lhs.second].start > intervals[rhs.first][rhs.second].start;
        };

        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> heap(cmp);
        for(int i = 0; i < n; i++) {
            if(intervals[i].size() > 0) {
                heap.push(make_pair(i, 0));
            }
        }

        while(!heap.empty()) {
            int i = heap.top().first;
            int j = heap.top().second;
            heap.pop();

            if(result.empty() || intervals[i][j].start > result.back().end) {
                result.push_back(intervals[i][j]);
            } 
            else if(intervals[i][j].end > result.back().end) {
                result.back().end = intervals[i][j].end;
            }
            else {
                // Do nothing
            }
            
            
            if(++j < intervals[i].size()) {
                heap.push(make_pair(i, j));
            }
        }

        return result;
    }
};

int main() {
    vector<vector<Interval>> intervals {        
        buildIntervals( vector<int>{1,3,4,7,6,8}),
        buildIntervals(vector<int>{1, 2, 9, 10})
    };
    Solution sol;
    printVector(sol.mergeKSortedIntervalLists(intervals));
}