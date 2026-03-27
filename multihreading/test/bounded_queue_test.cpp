

#include<iostream>
#include<thread>
#include<future>
#include<functional>
#include<mutex>
#include<condition_variable>
#include<queue>
#include<atomic>

using namespace std;


template <typename T>
class BoundedQueue {
    public:
    using Task = function<T(void)>;
    explicit BoundedQueue() = default;
    explicit BoundedQueue(int _sz, int numprod, int numcon) {
        len = _sz;
        front = len-1;
        back = len-1;
        stopped = 0;
        arr = vector<T>(len);
        for(auto i=0;i<numprod;i++) prod.emplace_back(&BoundedQueue::produce,this);
        for(auto i=0;i<numcon;i++) con.emplace_back(&BoundedQueue::consume,this);
    }

    void add(T item){
        unique_lock<mutex> ul1(mtxprod);
        if(stopped) return;
        prodqueue.push(item);
        
        cvprod.notify_one();
        cvarr.notify_all();
    }

    T get(){
        T item;
        promise<T> prom;
        future<T> fut = prom.get_future();
        {
            unique_lock<mutex> ul1(mtxcon);
            if(stopped) return item;
            // Task task = [this]{
            //     return ;
            // };
            consumertasks.push(std::move(prom));
            cvcons.notify_all();
        }
        // promise<T> prom = future(launch::async,task);
        item = fut.get();
        //cout<<item<<endl;
        return item;
    }

    void stop() {
        stopped = true;
        cvprod.notify_all();
        cvcons.notify_all();
        cvarr.notify_all();
        for(auto& th: prod){
            if(th.joinable()) th.join();
        }
         for(auto& th: con){
            if(th.joinable()) th.join();
        }
    }

    private:

    void produce() {
        while(true) {
            T item;
            {
                unique_lock<mutex> ul1(mtxprod);
                cvprod.wait(ul1,[this] {
                    return stopped || !prodqueue.empty();
                });
                if(stopped) return;
                item = prodqueue.front();
                prodqueue.pop();
            }
            {
                unique_lock<mutex> ul2(mtxarr);
                cvarr.wait(ul2,[this] {
                    return stopped || !isFull();
                });
                
                if(stopped) return;
                arr[back] = item;
                cout<<"Pushed : "<<item<<endl;
                //cout<<front<<"^^"<<back<<endl;
                back = (back -1 + len)%len;
                cvarr.notify_all();
            }
        }
    }

    // [f....b]
    // [b.....f]
    bool isFull(){
        if((front+1)%len == back) return true;
        return false;
    }

    bool isEmpty(){
        return front == back;
    }

    void consume () {
        promise<T> task;
        while(true) {
            {
                unique_lock<mutex> ul1(mtxcon);
                cvcons.wait(ul1,[this] {
                    return stopped || !consumertasks.empty();
                });
                if(stopped) return;
                task = move(consumertasks.front());
                consumertasks.pop();
                cvcons.notify_all();
            }
            {
                unique_lock<mutex> ul2(mtxarr);
                cvarr.wait(ul2,[this] {
                    return stopped || !isEmpty();
                });
                if(stopped) return ;
                T item = arr[front];
                task.set_value(item);
                cout<<"popped" <<item<<endl;
                //cout<<front<<"**"<<back<<endl;
                front = (front -1 + len)%len;
                cvarr.notify_all();
            }
        }
    }
    vector<thread> prod, con;
    int len;
    mutex mtxarr, mtxprod, mtxcon;
    condition_variable cvarr, cvcons, cvprod;
    vector<T> arr;
    queue<promise<T>> consumertasks;
    queue<T> prodqueue;
    atomic<bool> stopped;
    int front, back;
};

void testmed() {
    BoundedQueue<int> bq(5,2,2);
    for(auto i=0;i<10;i++){
        bq.add(i);
    }
    for(auto i=0;i<10;i++) bq.get();
    this_thread::sleep_for(chrono::milliseconds(1000));
    bq.stop();
}

int main(){
    testmed();
    return 0;
}