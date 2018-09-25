/*
Given a list of unique words, find all pairs of distinct indices (i, j) in the given list, so that the concatenation of the two words, i.e. words[i] + words[j] is a palindrome.

Example 1:

Input: ["abcd","dcba","lls","s","sssll"]
Output: [[0,1],[1,0],[3,2],[2,4]] 
Explanation: The palindromes are ["dcbaabcd","abcddcba","slls","llssssll"]
Example 2:

Input: ["bat","tab","cat"]
Output: [[0,1],[1,0]] 
Explanation: The palindromes are ["battab","tabbat"]
*/


// native solution will TLE

#include "LeetcodeTools.h"
using namespace leetcode;

class Solution {
public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        unordered_map<string, int> wordIdx;
        set<int> wordLen;
        vector<vector<int>> res;

        for(int i = 0; i < words.size(); i++) {
            wordIdx[words[i]] = i;
            wordLen.insert(words[i].size());
        }

        for(int i = 0; i < words.size(); i++) {
            string t = words[i];
            reverse(t.begin(), t.end());
            if(wordIdx.count(t) && wordIdx[t] != i){
                res.push_back(vector<int>{i, wordIdx[t]});
            }

            // for each word, find all possible pair for let self as long word
            for(auto it = wordLen.begin(); *it < t.size(); it++) {
                int d = *it;
                // self as start part                
                if(wordIdx.count(t.substr(t.size() - d)) && isPalindrome(t, 0, t.size() - d - 1) ) {
                    res.push_back(vector<int> {i, wordIdx[t.substr(t.size() - d)]});
                }
                // self as end part
                if(wordIdx.count(t.substr(0, d)) && isPalindrome(t, d, t.size() - 1)) {
                    res.push_back(vector<int> {wordIdx[t.substr(0, d)], i});
                }
            }
        }

        return res;
    }
private:
    bool isPalindrome(string& s, int lo, int hi) {
        while(lo < hi) {
            if(s[lo++] != s[hi--]) return false;
        }

        return true;
    }
};

int main() {
    Solution sol;
    vector<string> words{"abcd","dcba","lls","s","sssll"};
    printVector2D(sol.palindromePairs(words));
}