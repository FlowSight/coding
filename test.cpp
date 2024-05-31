#include <iostream>
#include <vector>
#include <algorithm>
#include <vector>

using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;

// define linkedlist node
struct ListNode {
    string val;
    ListNode *next;
    ListNode(string x) : val(x), next(NULL) {}
};
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int max_profit = 0;
        int min_price = INT_MAX;
        for (int i = 0; i < prices.size(); i++) {
            min_price = min(min_price, prices[i]);
            max_profit = max(max_profit, prices[i] - min_price);
        }
        return max_profit;
    }
    // method name : createLinkedList
    // given list of connected linkedlist edges,create a linkedlist
    // edges = ["a->b", "b->c", "c->d"]
    void createLinkedList(vvi edges) {
        unordered_map<string, ListNode*> mm;
        for (auto e : edges) {
            //parse edges
            string start = string(e[0], 1);
            string end = string(e[1], 1);
            if (mm.find(start) == mm.end()) {
                mm[start] = new ListNode(stoi(start));
            }
            if (mm.find(end) == mm.end()) {
                mm[end] = new ListNode(stoi(end));
            }
            mm[start]->next = mm[end];
        }
    }

};

int main() {
    Solution sol;
    vi input = {7,1,5,3,6,4};
    auto output = sol.maxProfit(input);
    cout << output << endl;
    return 0;
}