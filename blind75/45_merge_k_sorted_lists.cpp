// 11 mar 2025
// forgot comparator syntax..
// also forgot base case..
// sev0...


// nov 10 2024..fucked up many things
// 1. forgot how to define custom comparator for priority queue and set, if you HAVE to work with given struct
// 2. missed a critical base case.
// sev0

//approach 1:
ListNode* mergeKLists(vector<ListNode*>& lists) {
    while(lists.size() > 1) {
        auto last = lists.back();
        lists.pop_back();
        auto secondLast = lists.back();
        lists.pop_back();
        lists.push_back(merge2Lists(last,secondLast));
    }
    return lists.empty() ? nullptr : lists[0];
}    
ListNode* merge2Lists(ListNode* node1, ListNode* node2){
    if(!node1) return node2;
    if(!node2) return node1;
    if(node1->val < node2->val){
        node1->next = merge2Lists(node1->next, node2);
        return node1;
    } else {
        node2->next = merge2Lists(node1, node2->next);
        return node2;
    }
}
ListNode* merge2ListsIterative(ListNode* node1, ListNode* node2){
    if(!node1) return node2;
    if(!node2) return node1;
    ListNode* dummy = new ListNode();
    ///....some code.....
}

//TC
// n list nodes
// k per list
// n-1 times merge called 
// for last two lists n-1 times == 2k*(n-1)
// for last 3rd lists node n-2 times = k*(n-2)
// for first list node 1 times = k
// = k + k*2 + k*3 + k*4 + k*5 + ... + k*(n-1)
// = k(1+2+3+...+n-1)
// = kn^2 



// approach 2:
public static ListNode mergeKListsMergeSort(ListNode[] lists,int l,int r){
    if(l>r)return nullptr;
    if(l==r)  return lists[l];
    int mid=(l+r)/2;
    ListNode l1=mergeKListsMergeSort(lists,l,mid);
    ListNode l2=mergeKListsMergeSort(lists,mid+1,r);
    return merge2Lists(l1,l2);
}

// TC
// 2*t(n/2)+O(nk)
// 4*t(n/4)+2*o(nk/2)+O(nk)
// 8*t(n/8)+4*o(nk/4)+2*o(nk/2)+O(nk)
// O(nk) * log(n) times 
// O(nklogn)

//approach 3:

struct cmp {
    bool operator() (const ListNode* node1, const ListNode* node2) const {
        return node1->val < node2->val;
    }
};

class Solution {
public:

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        multiset<ListNode*,cmp> ss;
        int n = lists.size();
        ListNode* dummyNode = new ListNode();
        ListNode* prev = dummyNode;

        for(auto i=0;i<n;i++)if(lists[i])ss.insert(lists[i]);

        while(!ss.empty()) {
            auto tp = *(ss.begin());
            ss.erase(ss.begin());

            prev->next = tp;
            prev = prev->next;
            tp = tp->next;
            if(tp){
                ss.insert(tp);
            }
        }
        return dummyNode->next;
    }
};

//TC nklog(n)