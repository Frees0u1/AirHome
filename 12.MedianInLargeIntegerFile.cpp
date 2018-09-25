#include "LeetcodeTools.h"
#include <fstream>
using namespace leetcode;

class Solution{
    double findMedian(string fileName){
        ifstream inStream(fileName.c_str());
        priority_queue<int> mHeap;
        priority_queue<int, vector<int>, std::greater<int>> MHeap;

        if(!inStream) {
            cout << "No such file!" << endl;
            return -1;
        }

        string line;
        while(getline(inStream, line)) {
            int x = stoi(line);
            
            mHeap.push(x);
            if(mHeap.size() > MHeap.size() + 1) {
                MHeap.push(mHeap.top());
                mHeap.pop();
            }
        }

        if(mHeap.size() > MHeap.size()) return (double)mHeap.top() / 2;
        else
            return (mHeap.top() + MHeap.top()) / 2.0;
    }    
};



int main() {


}