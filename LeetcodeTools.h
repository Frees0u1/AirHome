/*
    Leetcode Normal Tools
    @Author: loskyer
    @Date: 2018/08/22
*/
#ifndef _LEETCODE_H_
#define _LEETCODE_H_

#include <vector>
#include <string>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <algorithm>
#include <functional>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>
#include <iterator>
#include <limits>
#include <climits>
#include <assert.h>
#include <numeric>
#include <bitset>
#include <memory>
#include <cstring>

/*
==> code snippet
#include "LeetcodeTools.h"
using namespace leetcode;

class Solution {
public:

};

int main () {
    Solution sol;

    return 0;
}
*/

namespace leetcode {
using namespace std;

// ======================================================= For Intervals ====================================================
typedef struct Interval {
    int start, end;
    Interval(int start, int end) {
        this->start = start;
        this->end = end;
    }
}Interval;

// make Interval can be cout
std::ostream &operator<<(std::ostream &os, const Interval& inv) {
    return os << "[" << inv.start << ", " << inv.end << "]";
}

vector<Interval> buildIntervals(vector<int> vec) {
    assert(vec.size() % 2 == 0);
    vector<Interval> res;
    
    for(int i = 0; i < vec.size() - 1; i += 2) {
        res.push_back(Interval(vec[i], vec[i + 1]));
    }

    return res;
}

// ======================================================= For Trees ========================================================
struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int val) {
        this->val = val;
        this->left = this->right = NULL;
    }
};

// make tree node cout able
std::ostream &operator<<(std::ostream &os, const TreeNode& node) {
    string left = node.left ? to_string(node.left->val) : "null";
    string right = node.right ? to_string(node.right->val) : "null";
    return os << "[" << node.val << "](" << left << ")(" << right << ")";
}

std::ostream &operator<<(std::ostream &os, const TreeNode* nodePtr) {
    if(nodePtr == nullptr) {
        return os << "null";
    }
    else {
        return os << nodePtr->val;
    }
}

/*
    Serialize & Deserialize a binary tree, using codec as below:
    - Level travsal, '#' for a null
    - End with last not null
*/
class TreeCodec {
public:

    // Encodes a tree to a single string.
    static string serialize(TreeNode* root) {
        string res = "[";
        
        queue<TreeNode*> Q; Q.push(root);
        int count = (int)(root != nullptr);
        while(!Q.empty() && count > 0) {
            TreeNode* cur = Q.front(); Q.pop();            
            if(cur == nullptr) {
                res += "#,";
            }
            else {
                count--;
                res += to_string(cur->val) + ",";
                Q.push(cur->left);
                Q.push(cur->right);
                count += (int)(cur->left != nullptr) + (int)(cur->right != nullptr);
            }
        }
        if(res.back() == ',') res.pop_back();
        res += "]";

        return res;        
    }

    // Decodes your encoded data to tree.
    static TreeNode* deserialize(string data) {
        int l = 1, r = 1;
        vector<TreeNode* > prev;
        vector<TreeNode* > cur;
        TreeNode* root = nullptr;
        if(data.size() <= 2) return root;
        
        int k = 0;
        
        while(r < data.size()){
            while(r < data.size() && data[r] != ',' && data[r] != ']') r++;
            string sval = data.substr(l, r - l);
            
            if(root == nullptr) { // first node, must non-empty
                TreeNode* node = new TreeNode( stoi(sval) );
                root = node;
                cur.push_back(node);
                swap(cur, prev);
                k = 0;
            }
            else{
                if(k / 2 >= prev.size()) { //上一行的节点用完了
                    cur.swap(prev);
                    k = 0;
                    cur.clear();
                }
                
                if(sval != "#") {
                    TreeNode* node = new TreeNode(stoi(sval));
                    (k % 2 == 0) ? prev[k / 2]->left = node : prev[k / 2]->right = node;
                    //cur[k] = node;
                    cur.push_back(node);
                }
                k++;
            }
            
            l = r + 1; r = l;
        }
        return root;
    }    
};

void printTree(TreeNode* p, int indent = 4)
{
    if(p != NULL) {
        if(p->right) {
            printTree(p->right, indent+4);
        }
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        if (p->right) std::cout<<" /\n" << std::setw(indent) << ' ';
        std::cout<< p->val << "\n ";
        if(p->left) {
            std::cout << std::setw(indent) << ' ' <<" \\\n";
            printTree(p->left, indent+4);
        }
    }
}

// Another way 
// Print the arm branches (eg, /    \ ) on a line
void printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<TreeNode*>& nodesQueue, ostream& out) {
  deque<TreeNode*>::const_iterator iter = nodesQueue.begin();
  for (int i = 0; i < nodesInThisLevel / 2; i++) {  
    out << ((i == 0) ? setw(startLen-1) : setw(nodeSpaceLen-2)) << "" << ((*iter++) ? "/" : " ");
    out << setw(2*branchLen+2) << "" << ((*iter++) ? "\\" : " ");
  }
  out << endl;
}
 
// Print the branches and node (eg, ___10___ )
void printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<TreeNode*>& nodesQueue, ostream& out) {
  deque<TreeNode*>::const_iterator iter = nodesQueue.begin();
  for (int i = 0; i < nodesInThisLevel; i++, iter++) {
    out << ((i == 0) ? setw(startLen) : setw(nodeSpaceLen)) << "" << ((*iter && (*iter)->left) ? setfill('_') : setfill(' '));
    out << setw(branchLen+2) << ((*iter) ? to_string((*iter)->val) : "");
    out << ((*iter && (*iter)->right) ? setfill('_') : setfill(' ')) << setw(branchLen) << "" << setfill(' ');
  }
  out << endl;
}
 
// Print the leaves only (just for the bottom row)
void printLeaves(int indentSpace, int level, int nodesInThisLevel, const deque<TreeNode*>& nodesQueue, ostream& out) {
  deque<TreeNode*>::const_iterator iter = nodesQueue.begin();
  for (int i = 0; i < nodesInThisLevel; i++, iter++) {
    out << ((i == 0) ? setw(indentSpace+2) : setw(2*level+2)) << ((*iter) ? to_string((*iter)->val) : "");
  }
  out << endl;
}

int maxHeight(TreeNode* root) {
    if(root == nullptr) return 0;
    return max(maxHeight(root->left), maxHeight(root->right)) + 1;
}

// Pretty formatting of a binary tree to the output stream
// @ param
// level  Control how wide you want the tree to sparse (eg, level 1 has the minimum space between nodes, while level 2 has a larger space between nodes)
// indentSpace  Change this to add some indent space to the left (eg, indentSpace of 0 means the lowest level of the left node will stick to the left margin)
void printPretty(TreeNode *root, int level = 1, int indentSpace = 0, ostream& out = std::cout) {
  int h = maxHeight(root);
  int nodesInThisLevel = 1;
 
  int branchLen = 2*((int)pow(2.0,h)-1) - (3-level)*(int)pow(2.0,h-1);  // eq of the length of branch for each node of each level
  int nodeSpaceLen = 2 + (level+1)*(int)pow(2.0,h);  // distance between left neighbor node's right arm and right neighbor node's left arm
  int startLen = branchLen + (3-level) + indentSpace;  // starting space to the first node to print of each level (for the left most node of each level only)
    
  deque<TreeNode*> nodesQueue;
  nodesQueue.push_back(root);
  for (int r = 1; r < h; r++) {
    printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);
    branchLen = branchLen/2 - 1;
    nodeSpaceLen = nodeSpaceLen/2 + 1;
    startLen = branchLen + (3-level) + indentSpace;
    printNodes(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);
 
    for (int i = 0; i < nodesInThisLevel; i++) {
      TreeNode *currNode = nodesQueue.front();
      nodesQueue.pop_front();
      if (currNode) {
       nodesQueue.push_back(currNode->left);
       nodesQueue.push_back(currNode->right);
      } else {
        nodesQueue.push_back(NULL);
        nodesQueue.push_back(NULL);
      }
    }
    nodesInThisLevel *= 2;
  }
  printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);
  printLeaves(indentSpace, level, nodesInThisLevel, nodesQueue, out);
}

// ======================================================= For ListNode ======================================================
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int v) : val(v), next(nullptr){}
};

ListNode* buildList(vector<int> dat) {
    ListNode dummy(-1);
    ListNode* pLast = &dummy;
    for(int i = 0; i < dat.size(); i++) {
        pLast->next = new ListNode(dat[i]);
        pLast = pLast->next;
    }

    return dummy.next;
}

void printList(ListNode* cur){
    while(cur != nullptr) {
        cout << cur->val << " -> ";
        cur = cur->next;
    }
    cout << "null" << endl;
}

std::ostream &operator<<(std::ostream &os, const ListNode* nodePtr) {
    if(nodePtr == nullptr) {
        return os << "null";
    }
    else {
        return os << nodePtr->val;
    }
}

// =========================================================== Utility print =======================================
template<typename T>
void printVector(vector<T> vec, string split = " ") {
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<T>(std::cout, split.c_str()));
    cout << endl;
}

template<typename T>
void printVector2D(vector<vector<T>> vec, string split = " ") {
    for(int i = 0; i < vec.size(); i++) {
        printVector(vec[i], split);
    }
}

// C++ template to print vector container elements 
template <typename T> 
ostream& operator<<(ostream& os, const vector<T>& v) 
{ 
    os << "["; 
    for (int i = 0; i < v.size(); ++i) { 
        os << v[i]; 
        if (i != v.size() - 1) 
            os << ", "; 
    } 
    os << "]\n"; 
    return os; 
} 

// C++ template to print list container elements
template <typename T> 
ostream& operator<<(ostream& os, const list<T>& ls) 
{   
    for(auto& x : ls){
        cout << x << " -> ";
    }
    os << "NULL\n"; 
    return os; 
} 


template <typename T> 
ostream& operator<<(ostream& os, const set<T>& v) 
{ 
    os << "["; 
    for (auto it : v) { 
        os << it; 
        if (it != *v.rbegin()) 
            os << ", "; 
    } 
    os << "]\n"; 
    return os; 
}

// C++ template to print map container elements 
template <typename T, typename S> 
ostream& operator<<(ostream& os, const map<T, S>& v) 
{ 
    for (auto it : v)  
        os << it.first << " : " 
           << it.second << "\n"; 
      
    return os; 
}

// C++ template to print pair<> 
// class by using template 
template <typename T, typename S> 
ostream& operator<<(ostream& os, const pair<T, S>& v) 
{ 
    os << "("; 
    os << v.first << ", " 
       << v.second << ")"; 
    return os; 
} 

// Notice: Pass value here!!
template<typename T>
void printStack(stack<T> stk, string split = " ") {
    cout << "[ ";
    while(!stk.empty()) {        
        cout << stk.top() << split;
        stk.pop();
    }
    cout << ">";
    cout << endl;
}

// Notice: Pass value here!!
template<typename T>
void printQueue(queue<T> que, string split = " ") {
    cout << "< ";
    while(!que.empty()) {        
        cout << que.front() << split;
        que.pop();
    }
    cout << "]";
    cout << endl;
}

// ============================================= For Point ==============================================================
struct Point {
     int x;
     int y;
     Point() : x(0), y(0) {}
     Point(int a, int b) : x(a), y(b) {}
};

}

#endif