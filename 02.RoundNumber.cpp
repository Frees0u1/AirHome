/*
When you book on airbnb the total price is:

Total price = base price + service fee + cleaning fee + …

input : array of decimals ~ X
output : array of int ~ Y
But they need to satisfy the condition:

sum(Y) = round(sum(x))
minmize (|y1-x1| + |y2-x2| + ... + |yn-xn|)
Example1:
input = 30.3, 2.4, 3.5
output = 30 2 4

Example2:
input = 30.9, 2.4, 3.9
output = 31 2 4
*/

#include "LeetcodeTools.h"
using namespace leetcode;

class Solution{
public:
    vector<int> roundNumbers(vector<double>& X ) {
        vector<int> result;
        for(int i = 0; i < X.size(); i++) {
            int lb = (int)X[i];
            int ub = lb + 1;
            if(X[i] - lb < ub - X[i]) {
                result.push_back(lb);
            }
            else {
                result.push_back(ub);
            }
        }

        return result;
    }

};

int main() {
    vector<double> X{30.9, 2.4, 3.9};
    Solution sol;
    cout << sol.roundNumbers(X);
}
