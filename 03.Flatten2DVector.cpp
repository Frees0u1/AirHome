/*
Implement an iterator to flatten a 2d vector.

Have you met this question in a real interview?  
Example
Given 2d vector =

[
  [1,2],
  [3],
  [4,5,6]
]
By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,2,3,4,5,6].
*/

#include "LeetcodeTools.h"
using namespace leetcode;

class Vector2D {
public:
    Vector2D(vector<vector<int>>& vec2d) : vec(vec2d), curRow(0), curCol(0){
        while(curRow < vec.size() && curCol >= vec[curRow].size()) {
            curRow++;
            curCol = 0;
        }
    }

    int next() {
        assert(hasNext());
        int val = vec[curRow][curCol++];

        while(curRow < vec.size() && curCol >= vec[curRow].size()) {
            curRow++;
            curCol = 0;
        }  

        return val;
    }

    bool hasNext() {
        return curRow < vec.size() && curCol < vec[curRow].size();
    }
private:
    vector<vector<int>>& vec;
    int curRow = 0;
    int curCol;
};


int main () {
    vector<vector<int>>vec {{}, {1,2}, {}, {4, 5, 6}, {}};
    Vector2D v2d(vec);
    while(v2d.hasNext()) {
        cout << v2d.next() << " ";
    }

    cout << endl;

    return 0;
}