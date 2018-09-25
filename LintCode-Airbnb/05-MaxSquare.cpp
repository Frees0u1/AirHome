/*
在一个二维01矩阵中找到全为1的最大正方形
*/

#include "../LeetcodeTools.h"
using namespace leetcode;

class Solution {
public:   
    int maxSquare(vector<vector<int>> &matrix) {
        int m = matrix.size(); if(0 == m) return 0;
        int n = matrix[0].size(); if(0 == n) return 0;
        vector<vector<int>> left1s(m + 1, vector<int>(n + 1, 0));
        vector<vector<int>> up1s(m + 1, vector<int>(n + 1, 0));

        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0)); // 前i行前j列的最大方形边长
        int maxLen = 0;

        for(int i = 1; i <= m; i++){
            for(int j = 1; j <= n; j++){               
                left1s[i][j] = matrix[i - 1][j - 1] == 0 ? 0 : left1s[i][j - 1] + 1;
                up1s[i][j] = matrix[i - 1][j - 1] == 0 ? 0 : up1s[i - 1][j] + 1;                               
               
                dp[i][j] = min( min(left1s[i][j], up1s[i][j]), dp[i - 1][j - 1] + 1 );                

                maxLen = max(maxLen, dp[i][j]);
            }
        }

        return maxLen * maxLen;
    }
};

int main() {
    vector<vector<int>> matrix{
        {1, 0, 1, 0, 0},
        {1, 0, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 0, 0, 1, 0}
    };

    Solution sol;
    cout << sol.maxSquare(matrix) << endl;
}