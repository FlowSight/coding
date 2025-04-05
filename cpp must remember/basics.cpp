priority_queue basic is REVERSE ORDER


this is must..without vector<int> declaration it wont understand how to compare..
priority_queue<int, vector<int>,greater<int>> pq; 



SET

    LOWER_BOUND 
    UPPER_BOUND




MAP 
// lower bound code
int getLowerBound(int key){
    if(mm.size() == 0) return -1;
    auto it = mm.lower_bound(key);
    if(it ==mm.end() || it->first > key) it--;
    if(it->first > key) return -1;
    return it->second;
}

// upper bound code..
int getUpperBound(int key){
    if(mm.size() == 0) return -1;
    auto it = mm.lower_bound(key);
    if(it ==mm.end()) return -1;
    return it->second;
}
/////////////////////////////comparators///////////////////////

 //if you HAVE TO use given STRUCT :
    struct cmp {
        bool operator() (const ListNode* node1, const ListNode* node2) const {
            return node1->val < node2->val;
        }
    };
    // works for:pq, sets 
    // pq needs vector and opp comparator

// if you HAVE TO use given CLASS :
    struct cmp {
        bool operator< (const ListNode* node1) const {
            return this->val < node1->val;
        }
    };

// if you are flexible, choose struct over class..

