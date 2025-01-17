

// 29 oct 2024

class MedianFinder {
public:
    multiset<int> ss;
    multiset<int>::iterator it;
    MedianFinder() {
        ss = multiset<int>();
        ss.insert(INT_MIN);
        ss.insert(INT_MAX);
        it = next(ss.begin());
    }
    
    void addNum(int num) {
        ss.insert(num);
        if(ss.size()%2 == 0){
            if(num >= *(it)) {
                it++;
            }
        } else {
            if(num < *(it)) {
                it--;
            }
        }
    }
    
    double findMedian() {
        return ss.size()%2 ? *(it) : ((*it) + (*prev(it)))/2.0;
    }
};

// forgot to use multiset

class MedianFinder {
public:
    int sz, middle;
    priority_queue<int> left;
    priority_queue<int,vector<int>,greater<int>> right;
    MedianFinder() {
        sz = 0;
        left = priority_queue<int>();
        right = priority_queue<int,vector<int>,greater<int>> ();
        middle = INT_MIN;
    }
    
    void addNum(int num) {
        if(sz%2){
            if(middle <= num) {
                left.push(middle);
                right.push(num);
            } else {
                left.push(num);
                right.push(middle);
            }
            middle = INT_MIN;
        } else {
            auto l = left.size() ? left.top() : INT_MIN, r = right.size() ? right.top() :  INT_MAX;
            vector<int> tmp = {l,num,r};
            sort(tmp.begin(),tmp.end());
            if(left.size()) left.pop();
            if(right.size()) right.pop();
            if(tmp[0] != INT_MIN) left.push(tmp[0]);
            if(tmp[2] != INT_MAX) right.push(tmp[2]);
            middle = tmp[1];
        }
        sz++;
    }
    
    double findMedian() {
        if(sz%2) return middle;
        return (double)(left.top()+right.top())/2.0;
    }
};


//  forgot pq structure
//  forgot pq insert vs push
//  missed case..
//  mistake in logic