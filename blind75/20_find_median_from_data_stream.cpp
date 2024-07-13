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