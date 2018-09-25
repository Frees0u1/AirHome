/*
描述
给出一个只含有小写字母的字符串的集合以及一个目标串，输出所有可以经过不多于 k 次操作得到目标字符串的字符串。

你可以对字符串进行一下的3种操作:

加入1个字母

删除1个字母

替换1个字母

您在真实的面试中是否遇到过这个题？  
样例
给出字符串 ["abc","abd","abcd","adc"]，目标字符串为 "ac" ，k = 1
返回 ["abc","adc"]
*/

#include "../LeetcodeTools.h"
using namespace leetcode;

// 方法1: Naive 动规 => 每一个单词计算对应的edit distance
class Solution{
public:
    vector<string> kDistance(vector<string> &words, string &target, int k) {
        vector<string> result;
        for(int i = 0; i < words.size(); i++) {
            if(editDist(words[i], target) <= k) {
                result.push_back(words[i]);
            }            
        }

        return result;
    }
private:
    int editDist(string& src, string& target) {
        int m = src.size();
        int n = target.size();
        if(m == 0 || n == 0) return m + n;

        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for(int i = 0; i <= m; i++) {
            dp[i][0] = i;
        }
        for(int j = 0; j <= n; j++) {
            dp[0][j] = j;
        }

        for(int i = 1; i <= m; i++) {
            for(int j = 1; j <= n; j++) {
                if(src[i - 1] == target[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else {
                    dp[i][j] = min(min(dp[i][j - 1], dp[i - 1][j]), dp[i - 1][j - 1]) + 1;
                }                
            }
        }

        return dp[m][n];
    }
};


class Solution2{
    struct TrieNode{
        bool isLeaf;
        TrieNode* next[26];

        TrieNode() : isLeaf(false) {
            fill_n(next, 26, nullptr);
        }
    };

    class Trie{
    public:
        Trie(){
            root_ = new TrieNode();
        }
        TrieNode* root() const { return root_; }

        void insert(string& word) {
            TrieNode* p = root_;
            for(int i = 0; i < word.size(); i++) {
                int idx = word[i] - 'a';
                if(p->next[idx] == nullptr) p->next[idx] = new TrieNode();
                p = p->next[idx];
            }
            p->isLeaf = true;
        }

    private:
        TrieNode* root_;        
    };
public:
    vector<string> kDistance(vector<string> &words, string &target, int k) {
        Trie trie;
        for(string& word : words) trie.insert(word);
        
        vector<int>prev2target(target.size() + 1, 0);
        for(int i = 1; i <= target.size(); i++) prev2target[i] = i;

        string curStr;
        vector<string> result;

        dfs("", target, result, k, trie.root(), prev2target);

        return result;
    }
private:
    void dfs(string cur, const string& target, vector<string>& result, int k, 
            TrieNode* curNode, vector<int>& dp) {
        if(curNode->isLeaf && dp[target.size()] <= k) {        
            result.push_back(cur);
        }
        
        for(int i = 0; i < 26; i++) {
            if(curNode->next[i] != nullptr) {
                vector<int> dpNew = dp;
                dpNew[0]++;
                char c = i + 'a';
                bool hasValid = dpNew[0] <= k;
                for(int j = 1; j <= target.size(); j++) {
                    if(c == target[j - 1]) {
                        dpNew[j] = dp[j - 1];
                    }
                    else {
                        dpNew[j] = min(min(dp[j], dp[j - 1]), dpNew[j - 1]) + 1;
                    }
                    if(dpNew[j] <= k) hasValid = true;
                }                
                if(hasValid) dfs(cur + c, target, result, k, curNode->next[i], dpNew);
            }
        }
    }
};


int main() {
    vector<string> words{"ab","ba","bab","cab","abc","cba"};
    string target = "ab";
    Solution2 sol;

    cout << sol.kDistance(words, target, 2) << endl;
}