#include "../LeetcodeTools.h"
using namespace leetcode;

class Tarjan{
public:
    vector<unordered_set<int>> findAllScc(unordered_map<int, unordered_set<int>>& G, int start, int end) {
        vector<int> status(end + 1, -1); // -1 undiscovered, 1 visiting, 2 visited
        stack<int> S;

        vector<unordered_set<int>> result;
        vector<int> DFN(end + 1, -1);
        vector<int> LOW(end + 1, -1);
        idx = 0;

        for(int i = start; i <= end; i++) {
            if(status[i] == -1) {
                tarjan(i, S, status, DFN, LOW, G, result);
            }
        }

        return result;
    }

private:
    int idx;
    void tarjan(int u, stack<int>& S,vector<int>& status, 
                vector<int>& DFN, vector<int>& LOW,
                unordered_map<int, unordered_set<int>>& G, vector<unordered_set<int>>& result) {
        
        if(status[u] == 2) return;

        DFN[u] = LOW[u] = ++idx;
        S.push(u); status[u] = 1; // visiting
        for(int v : G[u]) {            
            if(status[v] == -1) { // UNDISCOVERED
                tarjan(v, S, status, DFN, LOW, G, result);
                LOW[u] = min(LOW[u], LOW[v]);
            }
            else if(status[v] == 1) {
                LOW[u] = min(LOW[u], DFN[v]);
            }
        }

        if(DFN[u] == LOW[u]) {
            int v; result.push_back(unordered_set<int>());
            do {
                v = S.top(); S.pop();
                result.back().insert(v);
            }while(v != u);
        }

        status[u] = 2;
    }
};


int main () {
    unordered_map<int, unordered_set<int>> G;
    G[1] = unordered_set<int>{2, 9};
    G[2] = unordered_set<int>{1, 8};
    G[3] = unordered_set<int>{2, 6, 7};
    G[4] = unordered_set<int>{3};
    G[5] = unordered_set<int>{5, 6};
    G[6] = unordered_set<int>{7, 4};
    G[7] = unordered_set<int>{8};
    G[8] = unordered_set<int>{7};
    G[9] = unordered_set<int>{1, 8};

    Tarjan tar;
    auto res = tar.findAllScc(G, 1, 9);
    int ix = 0;
    for(auto& s : res) {
        cout << "SCC " << ++ix << ": ";
        for(auto x : s){
            cout << x << ' ';
        }

        cout << endl;
    }

    return 0;
}