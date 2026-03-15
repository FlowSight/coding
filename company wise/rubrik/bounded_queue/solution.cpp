
#include<iostream>
#include<thread>
#include<algorithm>
#include<functional>
#include<queue>
#include<mutex>
#include<future>

using namespace std;


template<typename T>
class BoundedQueue {
public:
    explicit BoundedQueue(int capacity,int _numpt, int _numct) {
        cap = capacity;
        numPt = _numpt;
        numCt = _numct;
        front = cap-1;
        back = cap-1;
        items = vector<T>(cap);
        for(auto i=0;i<numPt;i++) producers.emplace_back(&BoundedQueue::producerloop, this);
        for(auto i=0;i<numCt;i++) consumers.emplace_back(&BoundedQueue::consumerloop, this);
    }
    void enqueue(T item){
        {
            unique_lock<mutex> ul1(mtxQ);
            prodqueue.push(item);
            cvprod.notify_one();
        }
    }   

    T dequeue(){
        promise<T> item;
        future<T> fut = item.get_future();
        {
            unique_lock<mutex> ul1(mtxQ);
            consqueue.push(move(item));
            cvcons.notify_one();
        }
        T val = fut.get();
        return val;
    }

    void shutdown(){
        stopped.store(1);
        cvprod.notify_all();
        cvcons.notify_all();
        for(auto &th : producers) {
            if(th.joinable()) th.join();
        }
        for(auto &th : consumers) {
            if(th.joinable()) th.join();
        }
    }
    // unblock all

    private:
    int numPt, numCt, cap, front, back;
    vector<T> items;
    condition_variable cvprod, cvcons;
    vector<thread> producers,consumers;
    atomic<int> stopped{0}; // pop at front, insert AT back
    queue<T> prodqueue;
    queue<promise<T>> consqueue;
    mutex mtxprdq,mtxconq, mtxitems, mtxQ;
    

    void producerloop (){
        int backIdx;
        T item;
        while(true) {
            {
                {
                    unique_lock<mutex> ul1(mtxQ);
                    cvprod.wait(ul1,[this]{
                        if(stopped) return true;
                        if(prodqueue.empty()) return false;
                        return !((front+1)%cap == back);
                    });
                    if(stopped) return;

                    item = prodqueue.front();
                    prodqueue.pop();
                    backIdx = back;
                    back = (back - 1 + cap)%cap;
                
                    items[backIdx] = item;
                    cout<<" item : "<< "inserted at index: "<<backIdx<<endl;
                    cvcons.notify_one();
                }                
            }
        }
    }

    void consumerloop (){
        int frontIdx;
        T item;
        promise<T> consitem;
        while(true) {
            {
               { 
                    unique_lock<mutex> ul1(mtxQ);
                        cvcons.wait(ul1,[this]{
                            if(stopped) return true;
                            if(consqueue.empty()) return false;
                            return !(front == back);
                        });
                    if(stopped) return;
                    frontIdx = front;
                    front = (front - 1 + cap)%cap;
                    // get the task item
                    consitem = move(consqueue.front());
                    consqueue.pop();
                    cout<<" item : "<< "popped at index: "<<frontIdx<<endl;

                    
                    consitem.set_value(items[frontIdx]);
                    cvprod.notify_one();
                }

            }
        }
    }
};

void testmethod1(){
    BoundedQueue<int> bq(5,3,3);
    for(auto i=0;i<10;i++)bq.enqueue(i);
    for(auto i=0;i<10;i++){
        int val = bq.dequeue();
        cout<<"dequeued : "<<val<<endl;
    }
    bq.shutdown();
}

int main(){
    testmethod1();
    return 0;
}