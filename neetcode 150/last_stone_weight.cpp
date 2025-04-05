// 26 feb 25
// forgot that pq is reverser order
// sev1

class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int> pq;
        for(auto it : stones){
            pq.push(it);
        }
        while(pq.size() > 1){
            auto larger = pq.top();
            pq.pop();
            auto smaller = pq.top();
            pq.pop();
            larger-=smaller;
            if(larger)pq.push(larger);
        }
        return pq.empty() ? 0 : pq.top();
    }
};


