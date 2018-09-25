#include "../LeetcodeTools.h"
using namespace leetcode;

class Solution {
public:
    /**
     * @param lists: a list of ListNode
     * @return: The head of one sorted list.
     */
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        // return true: 右边在堆顶
        auto cmp = [](ListNode* lhs, ListNode* rhs) {
            if(lhs == nullptr) return false;
            if(rhs == nullptr) return true;

            return lhs->val > rhs->val;
        };

        make_heap(lists.begin(), lists.end(), cmp);
        ListNode dummy(-1);
        ListNode* pLast = &dummy;

        while(!lists.empty()) {
            pop_heap(lists.begin(), lists.end(), cmp);
            ListNode* cur = lists.back();
            lists.pop_back();
            if(cur != nullptr){
                ListNode* curNxt = cur->next;
                cur->next = nullptr;
                pLast->next = cur;
                pLast = cur;

                cur = curNxt;
                if(cur) {
                    lists.push_back(cur);
                    push_heap(lists.begin(), lists.end(), cmp);
                }
            }
        }

        return dummy.next;
    }
};

int main (){
    vector<ListNode*> lists{
        nullptr,
        buildList(vector<int>{1,3,5,7}),
        buildList(vector<int>{2,4,6,8})
    };
    Solution sol;
    ListNode* res = sol.mergeKLists(lists);

    printList(res);
    return 0;
}

