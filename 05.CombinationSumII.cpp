/*
Given a collection of candidate numbers (candidates) and a target number (target), find all unique combinations in candidates where the candidate numbers sums to target.

Each number in candidates may only be used once in the combination.

Note:

All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.
Example 1:

Input: candidates = [10,1,2,7,6,1,5], target = 8,
A solution set is:
[
  [1, 7],
  [1, 2, 5],
  [2, 6],
  [1, 1, 6]
]
Example 2:

Input: candidates = [2,5,2,1,2], target = 5,
A solution set is:
[
  [1,2,2],
  [5]
]

如果题目意思是单价和钱包总额(double), 乘以100即可转换成此题
*/

#include "LeetcodeTools.h"
using namespace leetcode;

class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        //result.clear();
        sort(candidates.begin(), candidates.end());
        dfs(0, target, candidates);

        return result;
    }

private:
    void dfs(int idx, int target, vector<int>& candidates) {
        if(target == 0) {
            result.push_back(comb);
        }
        else if(target > 0) {
            for(int i = idx; i < candidates.size() && candidates[i] <= target; i++) {
                comb.push_back(candidates[i]);
                dfs(i + 1, target - candidates[i], candidates);
                comb.pop_back();
                while(i + 1 < candidates.size() && candidates[i + 1] == candidates[i]) ++i;
            }
        }
        else {
            // Do nothing
        }
    }

    vector<int> comb;
    vector<vector<int>> result;
};  

int main () {
    Solution sol;
    vector<int> candidates{10,1,2,7,6,1,5};
    printVector2D(sol.combinationSum2(candidates, 8));

    return 0;
}