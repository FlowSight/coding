/// Severity: Sev0..sev0..sev0.. Sev0..sev0..sev0.. Sev0..sev0..sev0..
// Date: 25Nov26
// LC: 1206
// Where I failed: learnt the algorithm..
// Pattern: pattern_name
// Notes: additional_notes



class Skipnode {
    public:
    int val;
    Skipnode* next = nullptr;
    Skipnode* down = nullptr;
    Skipnode(int _val, Skipnode* _next, Skipnode* _down){
        down = _down;
        next = _next;
        val = _val;
    }
};

class Skiplist {
public:
    Skipnode* root;
    Skiplist() {
        root = new Skipnode(-1,nullptr, nullptr);
    }
    
    bool search(int target) {
        auto cur = root;
        while(cur){
            while(cur->next && (cur->next->val < target)) {
                cur = cur->next;
            }
            if(cur->next && (cur->next->val == target)) return true;
            cur = cur->down;
        }
        return false;

    }
    
    void add(int num) {
        auto cur = root;
        stack<Skipnode*> st;
        while(cur){
            while(cur->next && (cur->next->val < num)) {
                cur = cur->next;
            }
            st.push(cur);
            cur = cur->down;
        }
        bool insert = true;
        cur = root;
        Skipnode* down = nullptr;
        while(insert && !st.empty()) {
            auto node = st.top();
            st.pop();
            node->next = new Skipnode(num,node->next,down);
            down = node->next;
            if(rand()%100 < 50) insert = false;
        }
        if(insert) cur = new Skipnode(-1,nullptr,root);
    }
    
    bool erase(int num) {
        auto cur = root;
        bool found = false;
        while(cur){
            while(cur->next && (cur->next->val < num)) {
                cur = cur->next;
            }
            if(cur->next && (cur->next->val == num)){
                found = true;
                cur->next = cur->next->next;
            }
            cur = cur->down;
        }
        return found;
    }
};