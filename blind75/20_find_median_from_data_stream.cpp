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


    // another approach
    class MedianFinder {
public:
    
    priority_queue<double> maxpq;
    priority_queue<double, vector<double>, greater<double>> minpq;
    bool even;
    
    MedianFinder() {
       even = true;
    }
    
    void addNum(int num) {
        if(even) {
            maxpq.push(num);
            minpq.push(maxpq.top());
            maxpq.pop();
        } else {
            minpq.push(num);
            maxpq.push(minpq.top());
            minpq.pop();
        }
        even = !even;
    }
    
    double findMedian() {
         if(even) {
             return (maxpq.top() + minpq.top())/2;
         } else {
             return minpq.top();
         }
    }
};


//  2 3 4* 5 6

//   2 3 4 4* 5 6
//   2 3 4 4* 4 5 6

//  2 3 4 5 6 7 // even = med++
//  2 3 4 5* 6 7 8 // odd : 
 
//  make rule : new index go towards left,
//  same no : 
//     even : dont move
//     odd : --med