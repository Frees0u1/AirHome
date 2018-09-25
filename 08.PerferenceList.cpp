/*
每个人都有一个preference的排序，在不违反每个人的preference的情况下得到总体的preference的排序 拓扑排序解决
例如：
[[3, 5, 7, 9],
[2, 3, 8],
[5, 8]]

然后你要根据这个输入，输出一个总的preference list
这这一题应该就是：
[2, 3, 5, 8, 7, 9]
*/

#include "LeetcodeTools.h"
using namespace leetcode;

class Solution {
public:
    vector<int> perferenceList(vector<vector<int>> pLists) {
        buildGraph(pLists);
        queue<int> zeroQ;
        for(auto& p : inDeg) if(p.second == 0) zeroQ.push(p.first);

        vector<int> res;

        while(!zeroQ.empty()) {
            int cur = zeroQ.front(); zeroQ.pop();
            res.push_back(cur);
            for(int i = 0; i < G[cur].size(); i++) {
                if(--inDeg[G[cur][i]] == 0) {
                    zeroQ.push(G[cur][i]);
                }                
            }
        }

        return res.size() != inDeg.size() ? vector<int>() : res;
    }

private:
    vector<vector<int>> G;
    unordered_map<int, int> inDeg;
    int M;

    void buildGraph(vector<vector<int>>& pLists) {
        M = 0;
        for(int i = 0; i < pLists.size(); i++) {
            for(int j = 0; j < pLists[i].size() - 1; j++) {
                int from = pLists[i][j];
                int to = pLists[i][j + 1];

                M = max(M, max(from, to));
                
                if(max(from, to) >= G.size()){
                    for(int i = G.size(); i <= M; i++) {
                        G.push_back(vector<int>());
                    }
                }

                if(inDeg.find(from) == inDeg.end()) inDeg[from] = 0;
                G[from].push_back(to);
                inDeg[to]++;
            }
        }
    }
};

int main () {
    Solution sol;
    vector<vector<int>> pLists
    {
        {3, 5, 7, 9},
        {2, 3, 8},
        {5, 8}
    };

    cout << sol.perferenceList(pLists) << endl;

    return 0;
}