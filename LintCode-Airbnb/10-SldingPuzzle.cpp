/*
On a 2x3 board, there are 5 tiles represented by the integers 1 through 5, and an empty square represented by 0.

A move consists of choosing 0 and a 4-directionally adjacent number and swapping it.

The state of the board is solved if and only if the board is [[1,2,3],[4,5,0]].

Given a puzzle board, return the least number of moves required so that the state of the board is solved. If it is impossible for the state of the board to be solved, return -1.

样例
Given board = [[1,2,3],[4,0,5]], return 1.

Explanation: 
Swap the 0 and the 5 in one move.
Given board = [[1,2,3],[5,4,0]], return -1.

Explanation: 
No number of moves will make the board solved.
Given board = [[4,1,2],[5,0,3]], return 5.
*/

#include "../LeetcodeTools.h"
using namespace leetcode;

class Solution{
    struct state{
        string stat;
        int step;
        int pos; // 0的位置

        state(string& s, int sp, int p) :
            stat(s), step(sp), pos(p) 
        {}
    };
public:
    int slidingPuzzle(vector<vector<int>> &board) {
        string s;
        string target = "123450";
        int start = -1;
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 3; j++) {
                s.push_back('0' + board[i][j]);
                if(0 == board[i][j]) start = 3 * i + j;
            }
        }
        if(s == target) return 0;
        unordered_set<string> visited;
        queue<state> Q; Q.push(state(s, 0, start)); visited.insert(s);

        while(!Q.empty()) {
            string cur = Q.front().stat;
            int step = Q.front().step;
            int pos = Q.front().pos;

            //cout <<step <<": " << cur << endl;
            Q.pop();

            if(cur == target) return step;
            int i = pos / 3;
            int j = pos % 3;

            for(int d = 0; d < 4; d++) {
                int ii = i + dx[d];
                int jj = j + dy[d];
                if(ii >= 0 && ii < 2 && jj >= 0 && jj < 3) {
                    int newPos = ii * 3 + jj;
                    string nxt = cur; swap(nxt[newPos], nxt[pos]);
                    
                    if(visited.find(nxt) == visited.end()) {
                        Q.push(state(nxt, step + 1, newPos));
                        visited.insert(nxt);
                    }
                }
            }
        }

        return -1;
    }
private:
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};
};

int main() {
    vector<vector<int>> board{{4, 1, 2}, {5, 0, 3}};
    Solution sol;
    cout << sol.slidingPuzzle(board) << endl;

    return 0;
}