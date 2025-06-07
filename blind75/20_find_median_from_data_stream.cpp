// 31 may 2025
// while speaking forgot the approach..messsed up..sev0

// 30 apr 2025
// compiler error..iterator..sev2

// 11 mar 2025
// 15 mins..did during call..
// fucked up the base case of size 1
// sev1

class MedianFinder {
    public:
        multiset<pair<int,int>> ss;
        multiset<pair<int,int>>::iterator it;
        int ts;
        MedianFinder() {
            ss.clear();
            it = ss.begin();
            ts = 0;
        }
        
        void addNum(int num) {
            ss.insert({num,ts++});
            if(ss.size() == 1){
                it = ss.begin();
                return;
            }
    
            if(ss.size()%2) {
                // was even
                if(it->first<=num) {
                    it++;
                }
    
            } else {
                // was odd
                if(it->first>num) {
                    it--;
                }
            }
        }
        
        double findMedian() {
            auto one = it->first, two = (ss.size()%2)?one : next(it)->first;
            return (one+two)/2.0;
        }
    };
    
    /**
     * Your MedianFinder object will be instantiated and called as such:
     * MedianFinder* obj = new MedianFinder();
     * obj->addNum(num);
     * double param_2 = obj->findMedian();
     */



struct node{
    int idx;
    double num;
    node(int _idx, double _num){
        idx = _idx;
        num = _num;
    }  
    bool operator< (const node& n) const {
        return n.num == num ? idx > n.idx : num < n.num;
    }
};

class MedianFinder {
public:
    set<node> ss;
    int idx;
    set<node>::iterator med;
    MedianFinder() {
        ss.clear();
        idx = 0;
        med = ss.end();
    }
    
    void addNum(int num) {
        ss.insert(node(idx++,num));
        if(ss.size() == 1)med = ss.begin();
        else {
            if((num > med->num) && (ss.size() % 2 == 0)) {
                med++;
            } else if((num <= med->num) && (ss.size() % 2)){
                med--;
            }
        }
    }
    
    double findMedian() {
        double res = med->num;
        if(ss.size() % 2 == 0){
            res = (res + prev(med)->num)/2.0;
        }
        return res;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */


//  2 3 4* 5 6

//   2 3 4 4* 5 6
//   2 3 4 4* 4 5 6

//  2 3 4 5 6 7 // even = med++
//  2 3 4 5* 6 7 8 // odd : 
 
//  make rule : new index go towards left,
//  same no : 
//     even : dont move
//     odd : --med