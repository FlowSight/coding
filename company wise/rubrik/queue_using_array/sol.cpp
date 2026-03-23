// Severity: Sev2
// Date: 16Mar26
// Pattern: circular array, free list

#include<iostream>
#include<stdexcept>
using namespace std;

// Part 1: Fixed-size queue using circular array
// One sentinel slot wasted to distinguish full from empty
class CircularQueue {
    int* arr;
    int front, back, cap;
public:
    explicit CircularQueue(int n) : cap(n + 1), front(0), back(0) {
        arr = new int[cap];
    }
    ~CircularQueue() { delete[] arr; }

    bool isEmpty() { return front == back; }
    bool isFull()  { return (back + 1) % cap == front; }

    void enqueue(int val) {
        if (isFull()) throw runtime_error("full");
        arr[back] = val;
        back = (back + 1) % cap;
    }

    int dequeue() {
        if (isEmpty()) throw runtime_error("empty");
        int val = arr[front];
        front = (front + 1) % cap;
        return val;
    }
};

// Part 2: Two queues in one fixed array, 99% utilization
// Uses a free list so any slot can be used by either queue
// Extra space: next[] array (N ints for pointers)
class TwoQueues {
    int* val;
    int* next;
    int cap;
    int free;
    int f1, b1;
    int f2, b2;

public:
    explicit TwoQueues(int n) : cap(n), f1(-1), b1(-1), f2(-1), b2(-1), free(0) {
        val = new int[n];
        next = new int[n];
        for (int i = 0; i < n - 1; i++) next[i] = i + 1;
        next[n - 1] = -1;
    }
    ~TwoQueues() { delete[] val; delete[] next; }

    int allocSlot() {
        if (free == -1) throw runtime_error("full");
        int slot = free;
        free = next[free];
        next[slot] = -1;
        return slot;
    }
    void freeSlot(int slot) {
        next[slot] = free;
        free = slot;
    }

    void enqueue1(int v) {
        int slot = allocSlot();
        val[slot] = v;
        if (b1 != -1) next[b1] = slot;
        b1 = slot;
        if (f1 == -1) f1 = slot;
    }
    int dequeue1() {
        if (f1 == -1) throw runtime_error("Q1 empty");
        int slot = f1, v = val[slot];
        f1 = next[slot];
        if (f1 == -1) b1 = -1;
        freeSlot(slot);
        return v;
    }

    void enqueue2(int v) {
        int slot = allocSlot();
        val[slot] = v;
        if (b2 != -1) next[b2] = slot;
        b2 = slot;
        if (f2 == -1) f2 = slot;
    }
    int dequeue2() {
        if (f2 == -1) throw runtime_error("Q2 empty");
        int slot = f2, v = val[slot];
        f2 = next[slot];
        if (f2 == -1) b2 = -1;
        freeSlot(slot);
        return v;
    }
};

int main() {
    // Test Part 1
    cout << "=== Part 1: Circular Queue ===" << endl;
    CircularQueue cq(5);
    for (int i = 0; i < 5; i++) cq.enqueue(i * 10);
    while (!cq.isEmpty()) cout << cq.dequeue() << " ";
    cout << endl;

    // Test Part 2
    cout << "=== Part 2: Two Queues ===" << endl;
    TwoQueues tq(8);
    for (int i = 0; i < 5; i++) tq.enqueue1(i);
    for (int i = 10; i < 13; i++) tq.enqueue2(i);
    // total 8 items in 8 slots = 100% utilization

    cout << "Q1: ";
    while (true) {
        try { cout << tq.dequeue1() << " "; }
        catch (...) { break; }
    }
    cout << endl;

    cout << "Q2: ";
    while (true) {
        try { cout << tq.dequeue2() << " "; }
        catch (...) { break; }
    }
    cout << endl;

    return 0;
}
