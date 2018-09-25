#include "../LeetcodeTools.h"
using namespace leetcode;

class Solution{
public:
    bool isMatch(string& str, string& pattern) {
        int m = str.size();
        int n = pattern.size();
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
        dp[0][0] = true;

        for(int i = 0; i <= m; i++) {
            for(int j = 1; j <= n; j++) {
                if(pattern[j - 1] == '*') {
                    dp[i][j] = j > 1 && (dp[i][j - 2] || 
                               ( (i > 0) && dp[i - 1][j] && (pattern[j - 2] == str[i - 1] || pattern[j - 2] == '.')) );                                        
                }
                else {
                    dp[i][j] = (i > 0) && dp[i - 1][j - 1] && (pattern[j - 1] == '.' || pattern[j - 1] == str[i - 1]);
                }
            }
        }

        return dp[m][n];
    }
};


int main() {
    string str = "aa";
    string pattern = "a*";
    Solution sol;
    
    cout << sol.isMatch(str, pattern) << endl;
}