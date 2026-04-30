
//Build a queue class with the enqueue and dequeue methods. 
//The queue can store an UNLIMITED number of elements. 
//However, the language you are using has a bug which does not allow arrays to 
//store more than 5 elements, how would you build that?


// typedef vi vector<int>(5);



// {a b c d poiner} -> { e f g h pointer}

// head                 tail 
// 0  0 0 0 0
// t.       h 

#include<bits/stdc++.h>

using namespace std;


struct  ArrayNode
{
    vector<int> arr = {-1,-1,-1,-1,-1};
    int head, tail;
    ArrayNode* next;
    ArrayNode(){
        head = tail = -1;
        next = nullptr;
    }
    bool isfull(){
        return (head + 1)%5 == tail;
    }
    bool isempty(){
        return (head == tail) && (head == -1);
    }
    int getpushidx(){
        if(isfull()) return -1;
        return (head+1)%5;
    }
    int getpopidx(){
        if(isempty()) return -1;
        return tail;
    }
    void push(int num){
        int idx = getpushidx();
        if(idx == -1) return;
        cout<<"pushing "<<num<<" at "<<idx<<endl;
        arr[idx] = num;
        head = idx;
        if(tail == -1) tail = idx;
    }
    int pop(){
        int idx = getpopidx();
        if(idx == -1) return -1;
        if(isempty()) {
            head = tail = -1;
        } else {
            tail = (idx+1)%5;
        }
        int res = arr[idx];
        cout<<"pop "<<res<<" at "<<idx<<endl;
        return res;
    }
};

class QueueWithArr {
    public:
    QueueWithArr() {
        head = tail = new ArrayNode();
    }
    void push(int num){
        if(tail->isfull()) {
            tail->next = new ArrayNode();
            tail = tail->next;
        }
        tail->push(num);
    }
    int pop(){
        if(!head) return -1;
        if(head->isempty()) {
            return -1 ;
        }
        int num = head->pop();
        if(head->isempty()) head = head->next;
        return num;
    }

    private:
    ArrayNode* head;
    ArrayNode* tail;
};


int main(){
    QueueWithArr qwa;
    for(auto i=1;i<=9;i++)qwa.push(i);
    for(auto i=1;i<=8;i++) cout<<qwa.pop()<<endl;
    return 0;
}

