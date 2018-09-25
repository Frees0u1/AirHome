/*
1 Collatz Conjecture
* If a number is odd, the next transform is 3*n+1
* If a number is even, the next transform is n/2
* The number is finally transformed into 1.
The step is how many transforms needed for a number turned into 1.

Given an integer n, output the max steps of transform number in [1, n] into 1.
*/
#include "LeetcodeTools.h"
using namespace leetcode;


class Solution{
public:
    int maxTransStep(int n) {
        int maxStep = 0;
        transSteps.clear();
        transSteps[1] = 1;
        for(int i = 2; i <= n; i++) {
            maxStep = max(maxStep, maxTransStepCore(i));           
        }

        return maxStep;
    }

private:
    unordered_map<int, int> transSteps;

    int maxTransStepCore(int x) {
        if(transSteps.find(x) == transSteps.end()) {
            if(x % 2 == 0) transSteps[x] = maxTransStepCore(x / 2) + 1;
            else transSteps[x] = maxTransStepCore(x * 3 + 1) + 1;
        }

        return transSteps[x];
    }
};


int main() {
    Solution sol;
    cout << sol.maxTransStep(101) << endl;
}