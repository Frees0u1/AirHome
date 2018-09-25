/*
5 Travel Buddy
I have a wish list of cities that I want to visit to, my friends also have city wish lists that they want to visit to. If one of my friends share more than 50% (over his city count in his wish list), he is my buddy.

Given a list of city wish list, output buddy list sorting by similarity.
*/

#include "LeetcodeTools.h"
using namespace leetcode;

class Solution{
public:
    vector<vector<int>> travelBuddy(vector<int>& myList, vector<vector<int>>& lists) {
        unordered_set<int> wishList(myList.begin(), myList.end());
        
        // key is the number of same desternation, val is the record index of lists
        multimap<int, int, std::greater<int>> buddyMap;
        int buddyLevel = (myList.size() + 1)/ 2;

        for(int i = 0; i < lists.size(); i++) {
            int cnt = 0;
            for(int j = 0; j < lists[i].size(); j++) {
                if(wishList.find(lists[i][j]) != wishList.end()) {
                    cnt++;
                }
            }
            if(cnt >= buddyLevel) buddyMap.insert({cnt, i});
        }

        vector<vector<int>> result;
        for(auto& p : buddyMap) {
            result.push_back(lists[p.second]);
        }

        return result;
    }

};


int main() {
    vector<int> myWishList{1, 2, 3, 4};

    vector<vector<int>> lists{
        {1, 2, 5, 6},
        {1, 3, 4, 7},
        {3, 6, 5, 7}
    };

    Solution sol;
    printVector2D(sol.travelBuddy(myWishList, lists));

}