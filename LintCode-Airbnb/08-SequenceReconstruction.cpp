/*
605. 序列重构
判断是否序列 org 能唯一地由 seqs重构得出. org是一个由从1到n的正整数排列而成的序列，1 ≤ n ≤ 10^4。 重构表示组合成seqs的一个最短的父序列 (意思是，一个最短的序列使得所有 seqs里的序列都是它的子序列).
判断是否有且仅有一个能从 seqs重构出来的序列，并且这个序列是org。

样例
给定 org = [1,2,3], seqs = [[1,2],[1,3]]
返回 false
解释:
[1,2,3] 并不是唯一可以被重构出的序列，还可以重构出 [1,3,2]

给出 org = [1,2,3], seqs = [[1,2]]
返回 false
解释:
能重构出的序列只有 [1,2].

给定 org = [1,2,3], seqs = [[1,2],[1,3],[2,3]]
返回 true
解释:
序列 [1,2], [1,3], 和 [2,3] 可以唯一重构出 [1,2,3].

给定org = [4,1,5,2,6,3], seqs = [[5,2,6,3],[4,1,5,2]]
返回 true
*/
#include "../LeetcodeTools.h"
using namespace leetcode;

// 方法1: Naive的拓扑排序
class Solution {
public:
    
    bool sequenceReconstruction(vector<int> &org, vector<vector<int>> &seqs) {
        for(int i = 0; i < seqs.size(); i++) {
            for(int j = 0; j < (int)seqs[i].size() - 1; j++) {
                int from = seqs[i][j];
                int to = seqs[i][j + 1];
                G[from].push_back(to);

                if(inDeg.find(from) == inDeg.end()) inDeg[from] = 0;
                inDeg[to]++;
            }
            
            if(seqs[i].size() > 0) {
                int from = seqs[i].back();
                if(inDeg.find(from) == inDeg.end()) inDeg[from] = 0;
            }
        }

        vector<int> zeroDegs;
        for(auto& p : inDeg) {
            if(p.second == 0) zeroDegs.push_back(p.first);
            if(zeroDegs.size() > 1) return false;
        }

        for(int i = 0; i < org.size(); i++) {
            if(inDeg.find(org[i]) == inDeg.end()) return false;
        }

        int k = 0;
        while(!zeroDegs.empty()) {
            int cur = zeroDegs[0]; zeroDegs.clear();
            if(k >= org.size() || org[k++] != cur) return false;
            for(int i = 0; i < G[cur].size(); i++) {
                if(--inDeg[G[cur][i]] == 0) zeroDegs.push_back(G[cur][i]);

                if(zeroDegs.size() > 1) return false;
            }
        }

        return true;
    }
private:
    vector<int> G[10005];
    unordered_map<int, int> inDeg;
};

// 注意到这里的org是一个1~n的排列,可以利用这一性质
class Solution2 {
public:
    bool sequenceReconstruction(vector<int>& org, vector<vector<int>>& seqs) {
        unordered_map<int, int> pos, pre;
        // pre指向每一个元素的前一个位置,最终看是否与org中的位置相吻合
        for (int i = 0; i < org.size(); ++i) pos[org[i]] = i;
        for (auto& seq : seqs) {
            for (int i = 0; i < seq.size(); ++i) {
                if (pos.find(seq[i]) == pos.end()) {
                    return false;
                }
                if (i > 0 && pos[seq[i - 1]] >= pos[seq[i]]) {
                    return false;
                }
                if (pre.find(seq[i]) == pre.end()) {
                    pre[seq[i]] = (i > 0) ? pos[seq[i - 1]] : -1;
                } else {
                    pre[seq[i]] = max(pre[seq[i]], (i > 0) ? pos[seq[i - 1]] : -1);
                }
            }
        }
        for (int i = 0; i < org.size(); ++i) {
            if (pre[org[i]] != i - 1) 
                return false;
        }
        return true;
    }
};

int main() {
    vector<int> org{1, 2, 3};
    vector<vector<int>> seqs {
        {1, 2},
        {1, 3},
        {2, 3}
    };

    Solution2 sol;
    cout << sol.sequenceReconstruction(org, seqs) << endl;;

    return 0;
}