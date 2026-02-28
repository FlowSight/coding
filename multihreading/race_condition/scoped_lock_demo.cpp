// // Thread 1:                    Thread 2:
// lock_guard<mutex> a(mtxA);     lock_guard<mutex> b(mtxB);
// lock_guard<mutex> b(mtxB);     lock_guard<mutex> a(mtxA);
// // ↑ DEADLOCK — each holds one lock and waits for the other

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

struct BankAccount {
    string name;
    int balance;
    mutex mtx;

    BankAccount(string n, int b) : name(n), balance(b) {}
};

// Transfer money between two accounts
// Without scoped_lock: if thread1 does transfer(A,B) and thread2 does transfer(B,A)
// → DEADLOCK (each locks one account, waits for the other)
//
// scoped_lock locks BOTH mutexes atomically → no deadlock
void transfer(BankAccount& from, BankAccount& to, int amount) {
    // Locks both mutexes — deadlock-free regardless of argument order
    scoped_lock lk(from.mtx, to.mtx);

    if (from.balance >= amount) {
        from.balance -= amount;
        to.balance   += amount;
        cout << from.name << " → " << to.name << ": $" << amount << endl;
        this_thread::sleep_for(chrono::milliseconds(rand()%1000));  // simulate real work
    }
    // both mutexes unlocked here automatically (RAII)
}

int main() {
    BankAccount alice("Alice", 1000);
    BankAccount bob("Bob", 1000);

    // Two threads transferring in OPPOSITE directions — would deadlock with lock_guard
    thread t1([&]() {
        for (int i = 0; i < 5; i++) transfer(alice, bob, 50);
    });
    thread t2([&]() {
        for (int i = 0; i < 5; i++) transfer(bob, alice, 30);
    });

    t1.join();
    t2.join();

    cout << "Alice: $" << alice.balance << endl;
    cout << "Bob:   $" << bob.balance << endl;
    // Should always total $2000

    return 0;
}
