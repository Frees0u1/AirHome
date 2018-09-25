/*
https://www.lintcode.com/problem/pour-water/description
*/
#include "LeetcodeTools.h"
using namespace leetcode;

class Solution {
public:
    /**
     * @param heights: the height of the terrain
     * @param V: the units of water
     * @param K: the index
     * @return: how much water is at each index
     */
    vector<int> pourWater(vector<int> &heights, int V, int K) {
        while(V--) drop(heights, K);
        return heights;
    }
private:
    void drop(vector<int>& heights, int K) {
        int best = K;
        for(int d = -1; d <= 1; d += 2) { // left and right
            int i = K + d;
            while(i>= 0 && i < heights.size() && heights[i] <= heights[i - d]) {
                if(heights[i] < heights[best]) best = i;
                i += d;
            }

            if(best != K) break; // if left is ok, moving left
        }
        ++heights[best];
    }
};

class Solution2 {
public:
    /**
     * @param heights: the height of the terrain
     * @param V: the units of water
     * @param K: the index
     * @return: how much water is at each index
     */
    vector<int> pourWater(vector<int> &heights, int V, int K) {
        stack<int> left; left.push(K);
        stack<int> right; right.push(K);
        fillStack(heights, -1, left, K);
        fillStack(heights, 1, right, K);
        //cout << heights << endl;
        while(V--) {
            drop(heights, left, right, K);
          // cout << heights << endl;
        }
        return heights;
    }
private:
    void drop(vector<int>& heights,stack<int>& left, stack<int>& right, int K) {
        int best = left.top();
        if(heights[left.top()] == heights[K] && heights[right.top()] < heights[K]) best = right.top();

        ++heights[best];

        if(best != K && best == left.top() && heights[best] > heights[best + 1]) left.pop();
        else if(best != K && best == right.top() && heights[best] > heights[best - 1]) right.pop();
        else {
            fillStack(heights, -1, left, K);
            fillStack(heights, 1, right, K);
        }
    }

    void fillStack(vector<int>& heights, int d, stack<int>& stk, int K) { // d = -1 left; d = 1 go right
        for(int i = stk.top() + d; i >= 0 && i < heights.size(); i += d) {
            if(heights[i] <= heights[i - d]) { stk.push(i);}
            else break;
        }

        while(stk.top() != K && heights[stk.top()] == heights[stk.top() - d] ) stk.pop();        
    }
};


int main() {
    vector<int> heights{11,9,8,3,3,13,2,11,9,15};
    Solution2 sol;
    vector<int> res = sol.pourWater(heights, 16, 8);
    //cout << res << endl;

    return 0;
}