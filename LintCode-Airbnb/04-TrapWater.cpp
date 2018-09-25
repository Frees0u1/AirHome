#include "../LeetcodeTools.h"
using namespace leetcode;

class Solution{
public:
    int trapRainWater(vector<int>& heights) {
        int leftMax = 0, rightMax = 0;
        int l = 0, r = heights.size() - 1;
        int water = 0;

        while(l <= r) {
            leftMax = max(leftMax, heights[l]);
            rightMax = max(rightMax, heights[r]);
            if(leftMax < rightMax) {
                water += leftMax - heights[l];
                l++;
            }
            else {
                water += rightMax - heights[r];
                r--;
            }
        }
        
        return water;
    }
};


int main(){
    
    return 0;
}