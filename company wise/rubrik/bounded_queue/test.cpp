#include<bits/stdc++.h>
#include<semaphore>

using namespace std;

struct QueueState {
    public:
    int front = -1 , back = -1, type = 1;
    QueueState(int _t) : type(_t){}
    QueueState() = default;
    mutex mtx;
    counting_semaphore<> items{0};
};

template <typename T>
class BoundedTSQueue {
    public:
    explicit BoundedTSQueue(int _cap) : 
        items(_cap), buf(_cap), cap(_cap), next(_cap),curback(0) {
        for(auto i=0;i<cap-1;i++)next[i] = i+1;
        next[cap-1] = -1;
        q2.type = 2;
    }

    void stop(){
        stopped = true;
        items.release(cap);
        q1.items.release(cap);
        q2.items.release(cap);
    }
    bool push_q1(T item) {
        return push(q1,item);
    }
    bool push_q2(T item) {
        return push(q2,item);
    }
    bool pop_q1() {
        return pop(q1);
    }
    bool pop_q2() {
        return pop(q2);
    }
    bool push(QueueState& qs, T item){
        int idx = 0;
        items.acquire();
        if(stopped) return false;
        {
            unique_lock<mutex> ul(globalmtx1);
            idx = curback;
            curback = next[curback];
            next[idx] = -1;
        }
        {
            unique_lock<mutex> ul1(qs.mtx);
            if(qs.back == -1) qs.front = idx;
            else next[qs.back] = idx;
            qs.back = idx;
        }
        buf[idx] = item;
        qs.items.release();
        cout<<"pushed: "<<item<<" to queue: "<<qs.type<<endl;
        return true;
    }

    bool pop(QueueState& qs){
        int idx = 0;
        T item;
        qs.items.acquire();
        if(stopped) return false;
        {
            unique_lock<mutex> ul(qs.mtx);
            idx = qs.front;
            qs.front = next[idx];
            if(qs.front == -1) qs.back = -1;
        }
        {
            unique_lock<mutex> ul1(globalmtx1);
            next[idx] = curback;
            curback = idx;
        }

        item = move(buf[idx]);
        items.release();
        cout<<"popped: "<<item<<" from queue: "<<qs.type<<endl;
        return true;
    }

    private:
    atomic<bool> stopped{false};
    vector<T> buf;
    vector<int> next;
    mutex globalmtx1;
    int front, back,cap, curback;
    counting_semaphore<> items{0};
    QueueState q1, q2;
};

void testmethod(){
    BoundedTSQueue<int> bq(3);
    vector<thread> workers;
    for (auto i = 0; i < 10; i++) {
        int r = rand() % 2, qidx = rand()%2;
        cout<<(r?"pushing to ":"popping from")<<" queue: "<<qidx+1<<" val :"<<i<<endl;
        if(r){
            if(qidx) workers.emplace_back(&BoundedTSQueue<int>::push_q2 ,&bq,i);
            else workers.emplace_back(&BoundedTSQueue<int>::push_q1 ,&bq,i);
        } else {
            if(qidx) workers.emplace_back(&BoundedTSQueue<int>::pop_q2 ,&bq);
            else workers.emplace_back(&BoundedTSQueue<int>::pop_q1 ,&bq);
        }
    }
    this_thread::sleep_for(chrono::milliseconds(20000));
    bq.stop();
    for (auto &w : workers) {
        if (w.joinable()) w.join();
    }
}

int main(){
    testmethod();
    return 0;
}