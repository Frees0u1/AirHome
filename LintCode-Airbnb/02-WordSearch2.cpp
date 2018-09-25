#include "../LeetcodeTools.h"
using namespace leetcode;

class Solution{
public:
    vector<string> wordSearchII(vector<vector<char>> &board, vector<string> &words) {
        vector<string> result;
        
        string word = "";
        int m = board.size(); if(0 == m) return result;
        int n = board[0].size(); if(0 == n) return result;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        root = new TrieNode();
        for(string& word : words) {
            insert(word);
        }

        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                dfs(i, j, board, word, result, root);
            }
        }

        return result;
    }

private:
    struct TrieNode{
        bool isLeaf;
        vector<TrieNode*> next;
        TrieNode(): isLeaf(false), next(26, nullptr)
        {
        }
        
    };

    TrieNode* root;

    void insert(string& word) {
        TrieNode* cur = root;
        for(int i = 0; i < word.size(); i++) {
            int idx = word[i] - 'a';
            if(cur->next[idx] == nullptr) {
                cur->next[idx] = new TrieNode();                    
            }
            cur = cur->next[idx];
            //cur->prevCnt++;
        }
        cur->isLeaf = true;
    }


    void dfs(int i, int j, vector<vector<char>> &board, string& word, vector<string>& result, TrieNode* prev) {
        char c = board[i][j];
        if( board[i][j] == '#' || prev->next[ board[i][j] - 'a' ] == nullptr) return;

        word.push_back(board[i][j]);
        if(prev->next[board[i][j] - 'a']->isLeaf) {
            result.push_back(word);
            prev->next[board[i][j] - 'a']->isLeaf = false;          
        }
        board[i][j] = '#';
        prev = prev->next[c - 'a'];
        if(i > 0) dfs(i - 1, j, board, word, result, prev);
        if(j > 0) dfs(i, j - 1, board, word, result, prev);
        if(i < board.size() - 1) dfs(i + 1, j, board, word, result, prev);
        if(j < board[0].size() - 1) dfs(i, j + 1, board, word, result, prev);

        board[i][j] = c;
        word.pop_back();
    }
};

int main() {
    vector<vector<char>> board{
        {'d', 'o', 'a', 'f'},
        {'a', 'g', 'a', 'i'},
        {'d', 'c', 'a', 'n'}
    };

    vector<string> words{"dog", "dad", "dgdg", "can", "again"};

    Solution sol;
    printVector(sol.wordSearchII(board, words), "\n");
}