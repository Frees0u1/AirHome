/*
写一个算法来判断一个数是不是"快乐数"。

一个数是不是快乐是这么定义的：对于一个正整数，每一次将该数替换为他每个位置上的数字的平方和，然后重复这个过程直到这个数变为1，或是无限循环但始终变不到1。如果可以变为1，那么这个数就是快乐数。

您在真实的面试中是否遇到过这个题？  
样例
19 就是一个快乐数。

1^2 + 9^2 = 82
8^2 + 2^2 = 68
6^2 + 8^2 = 100
1^2 + 0^2 + 0^2 = 1
*/
#include "../LeetcodeTools.h"
using namespace leetcode;

class Solution {
public:    
    bool isHappy(int n) {
        unordered_set<int> visited;
        visited.insert(n);

        while(n != 1) {
            n = getNext(n);
            if(visited.find(n) != visited.end()) return false;
            visited.insert(n);
        }

        return true;
    }
private: 
    int getNext(int n) {
        int next = 0;
        while(n) {
            int t = n % 10; n /= 10;
            next += t * t;
        }

        return next;
    }
};

int main(){
    Solution sol;
    cout << sol.isHappy(19) << endl;
}