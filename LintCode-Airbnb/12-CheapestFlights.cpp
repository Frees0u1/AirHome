/*
描述
有n个城市被m条航班所连接。每个航班(u,v,w) 从城市u出发，到达城市v，航班价格为w。

现在给定所有的城市和航班，以及所有的航班(u,v,w) 。你的任务是找到从出发站src到终点站dst的最便宜线路，而旅途中最多经停k次，即最多能经过k个中转机场。如果没有找到合适的线路，则输出-1。

总城市数n 在 1-100 之间，每个城市被标号为 0 到 n-1。
航线的总数在 0 到 n * (n - 1) / 2 之间
每条航线会被以（出发站，终点站，价格）的形式展现。
每条航线的价格都在 1-10000之间。
中转站的总数限制范围为 0 到 n-1 之间。
不会有重复或者自环航线出现

您在真实的面试中是否遇到过这个题？  
样例
输入:
城市总数 = 3, 每条线路的价格 = [[0,1,100],[1,2,100],[0,2,500]]
出发站 = 0, 终点站 = 2, 中转站 = 1
输出: 200

输入:
城市总数 = 3, 每条线路的价格 = [[0,1,100],[1,2,100],[0,2,500]]
出发站 = 0, 终点站 = 2, 中转站 = 0
输出: 500
*/
#include "../LeetcodeTools.h"
using namespace leetcode;


class Solution {
    struct stopInfo{
        int cost;
        int nextStop;
        int step;

        stopInfo(int c, int n, int s) : cost(c), nextStop(n), step(s) {}
    };
public:
    int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int K) {
        unordered_map<int, vector<pair<int, int>>> G;
        for(int i = 0; i < flights.size(); i++) {
            int from = flights[i][0];
            int to = flights[i][1];
            int cost = flights[i][2];

            if(G.find(from) == G.end()) {
                G[from] = vector<pair<int, int>>{make_pair(cost, to)};
            }
            else {
                G[from].push_back({cost, to});
            }
        }    
        
        if(G.find(src) == G.end()) return -1;

        auto cmp = [](const stopInfo& lhs, const stopInfo& rhs) {
            return lhs.cost > rhs.cost;
        };
        priority_queue<stopInfo, vector<stopInfo>, decltype(cmp)> hq(cmp);
        for(int i = 0; i < G[src].size(); i++) {
            hq.push(stopInfo(G[src][i].first, G[src][i].second, 0));
        }

        while(!hq.empty()) {
            int curCost = hq.top().cost;
            int curStop = hq.top().nextStop;
            int step = hq.top().step;
            hq.pop();

            if(step > K) continue;
            else if(curStop == dst) return curCost;

            if(G.find(curStop) != G.end()) {
                for(int i = 0; i < G[curStop].size(); i++) {
                    hq.push(stopInfo( curCost + G[curStop][i].first, G[curStop][i].second, step + 1 ));
                }
            }
        }

        return -1;            
    }
};

int main() {
    vector<vector<int>> flights{
        {0, 1, 100},
        {1, 2, 100},
        {0, 2, 500}
    };

    Solution sol;

    cout << sol.findCheapestPrice(3, flights, 0, 2, 0) << endl;
}