#include<bits/stdc++.h>

using namespace std;


// search any no of concur
// insert concur with search, but one insert at a time
// delete no concur with any
struct DLL {
    public:
    DLL() = default;
    DLL(int _key , int _val){
        key = _key;
        val = _val;
        prev = nullptr;
        next = nullptr;
    }
    int val,key;
    DLL* prev;
    DLL* next;

};

class LLCrud {
    public:

    explicit LLCrud(){
        dummy = new DLL(-1,-1);
        last = dummy;
    }

    void insert(int key, int val){
        {
            unique_lock<mutex> ul(mtx);
            cv.wait(ul, [this]{ return !writer_active && !inserter_active; });
            if(stopped) return;
            active_readers++;
            inserter_active = true;
        }
        auto node = new DLL(key,val);
        last->next = node;
        node->prev = last;
        last = last->next;
        cout<<"inserted key: "<<key<<" val: "<<val<<endl;
        {
            lock_guard<mutex> lg(mtx);
            active_readers--;
            inserter_active = false;
        }
        cv.notify_all();
    }

    void search(int num){
        {
            unique_lock<mutex> ul(mtx);
            cv.wait(ul, [this]{ return !writer_active; });
            if(stopped) return;
            active_readers++;
        }
        auto head = dummy;
        while(head && (head->key != num)){
            head = head->next;
        }
        if(head && (head->key == num)){
            cout<<"found key :"<<num<<" val: "<<head->val<<endl;
        } else {
            cout<<"could not find key :"<<num<<endl;
        }
        {
            lock_guard<mutex> lg(mtx);
            active_readers--;
        }
        cv.notify_all();
    }

    void deleteNum(int num){
        {
            unique_lock<mutex> ul(mtx);
            cv.wait(ul, [this]{ return active_readers == 0 && !writer_active; });
            if(stopped) return;
            writer_active = true;
        }
        auto head = dummy;
        while(head && (head->key != num)){
            head = head->next;
        }
        if(head && (head->key == num)){
            auto prev = head->prev;
            auto next = head->next;
            prev->next = next;
            if(next) next->prev = prev;
            if(head == last) last = prev;
            cout<<"deleted key :"<<num<<" val: "<<head->val<<endl;
            delete head;
        } else {
            cout<<"could not delete key :"<<num<<endl;
        }
        {
            lock_guard<mutex> lg(mtx);
            writer_active = false;
        }
        cv.notify_all();
    }

    void shutdown(){
        {
            lock_guard<mutex> lg(mtx);
            stopped = true;
        }
        cv.notify_all();
    }

    private:
    DLL* dummy;
    DLL* last;
    mutex mtx;
    condition_variable cv;
    int active_readers = 0;
    bool writer_active = false;
    bool inserter_active = false;
    bool stopped = false;
};


void testmethod1(){
    LLCrud llcrud;
    vector<thread> workers;
    for(auto i=0;i<10;i++){
        int r = rand() % 3;
        if(r == 0)
            workers.emplace_back(&LLCrud::insert, &llcrud, i, i*10);
        else if(r == 1)
            workers.emplace_back(&LLCrud::search, &llcrud, i/2);
        else
            workers.emplace_back(&LLCrud::deleteNum, &llcrud, i/2);
    }
    this_thread::sleep_for(chrono::milliseconds(5000));
    llcrud.shutdown();
    for(auto &w : workers){
        if(w.joinable()) w.join();
    }
}

int main(){
    testmethod1();
    return 0;
}
