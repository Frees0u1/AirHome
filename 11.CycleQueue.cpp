#include "LeetcodeTools.h"
using namespace leetcode;

class CircularQueue {
public:
    /** Initialize your data structure here. Set the size of the queue to be k. */
    CircularQueue(int k)
    : maxSize_(k), front_(0), count_(0), que_(k, -1)
    {
        
    }
    
    /** Insert an element into the circular queue. Return true if the operation is successful. */
    bool enQueue(int value) {
        if(isFull()) return false;
        que_[(front_ + count_++) % maxSize_] = value;

        return true;
    }
    
    /** Delete an element from the circular queue. Return true if the operation is successful. */
    bool deQueue() {
        if(isEmpty()) return false;
        front_ = (front_ + 1) % maxSize_;
        --count_;

        return true;
    }
    
    /** Get the front item from the queue. */
    int Front() const {
        return que_[front_];
    }
    
    /** Get the last item from the queue. */
    int Rear() const {
        return que_[(front_ + count_ - 1) % maxSize_];
    }
    
    /** Checks whether the circular queue is empty or not. */
    bool isEmpty() const {
        return count_ == 0;
    }
    
    /** Checks whether the circular queue is full or not. */
    bool isFull() const {
        return count_ == maxSize_;
    }

private:
    vector<int> que_;
    int front_;
    int count_;
    int maxSize_;
};

int main() {

}