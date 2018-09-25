/*
Description
There is a new alien language which uses the latin alphabet. However, the order among letters are unknown to you. You receive a list of non-empty words 
from the dictionary, where words are sorted lexicographically by the rules of this new language. Derive the order of letters in this language.

You may assume all letters are in lowercase.
You may assume that if a is a prefix of b, then a must appear before b in the given dictionary.
If the order is invalid, return an empty string.
There may be multiple valid order of letters, return the smallest in lexicographical order

Example
Given the following words in dictionary,

[
  "wrt",
  "wrf",
  "er",
  "ett",
  "rftt"
]
The correct order is: "wertf"

Given the following words in dictionary,

[
  "z",
  "x"
]
The correct order is: "zx".
*/
// from => to means from is smaller than to
#include "LeetcodeTools.h"
using namespace leetcode;

class Solution{
public:
    string alienOrder(vector<string> &words) {
        buildGraph(words);
        priority_queue<int, vector<int>, std::greater<int>> zeroDegNodes;
        int total = 0;
        for(int i = 0; i < words.size(); i++) {
            for(int j = 0; j < words[i].size(); j++) {
                if(occured[words[i][j] - 'a'] == false) {
                    occured[words[i][j] - 'a'] = true;
                    total++;
                }
            }
        }

        for(int i = 0; i < 26; i++) if(occured[i] && inDeg[i] == 0) zeroDegNodes.push(i);
        string res = "";

        while(!zeroDegNodes.empty()) {
            int cur = zeroDegNodes.top(); zeroDegNodes.pop();

            for(int i = 0; i < G[cur].size(); i++){
                if(--inDeg[G[cur][i]] == 0) zeroDegNodes.push(G[cur][i]);
            }

            res.push_back('a' + cur);
        }

        return (res.size() < total ) ? "" : res;
    }
private:
    vector<int> G[26];
    int inDeg[26]; //入度
    bool occured[26];

    void buildGraph(vector<string> & words) {
        memset(inDeg, 0, sizeof(inDeg));
        memset(occured, false, sizeof(occured));
        for(int i = 0; i < words.size() - 1; i++) {
            int j = 0;
            while(j < words[i].size() && words[i][j] == words[i + 1][j]) j++;
            if(j == words[i].size()) continue; 

            int from = words[i][j] - 'a';
            int to = words[i + 1][j] - 'a';
            G[from].push_back(to);
            inDeg[to]++;
        }        
    }
};

int main () {
    Solution sol;
    vector<string> words{        
        "wrt",
        "wrf",
        "er",
        "ett",
        "rftt"
    };

    //vector<string> words {"ab", "adc"};

    cout << sol.alienOrder(words) << endl;

    return 0;
}