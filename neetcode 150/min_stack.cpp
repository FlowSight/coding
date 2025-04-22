// 14 apr 2025
// did 2 stack approach easily..6 min..clean
// 1 stack approach..didnt push through..saw in sols some sols did it..
// then tried to brainstorm..but 1 mistake : for same numbers its a tricky case..
// sev2

class MinStack {
    public:
        vector<int> st;
        int minVal;
        MinStack() {
            st = vector<int>();
            minVal = INT_MAX;
        }
        
        void push(int val) {
            if(val <= minVal){
                st.push_back(minVal);
                minVal = val;
            }
            st.push_back(val);
        }
        
        void pop() {
            if(st.back() == minVal){
                st.pop_back();
                minVal = st.back();
                
            }
            st.pop_back();
        }
        
        int top() {
            return st.back();
        }
        
        int getMin() {
            return minVal;
        }
    };
    

class MinStack {
    public:
        vector<int> st, minSt;
        MinStack() {
            st = vector<int>();
            minSt = vector<int>();
        }
        
        void push(int val) {
            st.push_back(val);
            minSt.push_back(minSt.empty()?val : min(minSt.back(),val));
        }
        
        void pop() {
            st.pop_back();
            minSt.pop_back();
        }
        
        int top() {
            return st.back();
        }
        
        int getMin() {
            return minSt.back();
        }
    };
    