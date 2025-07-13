//stephan pochman approach is better .
//sev2
class NestedIterator {
public:
    deque<NestedInteger> q;
    NestedIterator(vector<NestedInteger> &nestedList) {
        for(auto it : nestedList) {
            q.push_back(it);
        }
    }
    
    int next(bool pop = true) {
        if(q.empty()) return -1;
        auto tp = q.front();
        while(!tp.isInteger()){
            q.pop_front();
            auto list = tp.getList();
            int n = list.size();
            for(auto i=n-1;i>=0;i--){
                q.push_front(list[i]);
            }
            if(q.empty()) break;
            tp = q.front();
        }
        if(pop && q.size()) q.pop_front();
        return tp.isInteger() ? tp.getInteger() : -1;
    }
    
    bool hasNext() {
        next(false);
        return !q.empty();
    }
};
