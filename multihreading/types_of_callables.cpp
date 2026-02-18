#include <iostream>
#include <thread>
using namespace std;


// learnings
// &: just ref, dangerous if object ges out o scope
// thread copies all arguments internally, then passes them to the function.

class MyClass
{
public:
    int value = 39;
    void func1(int num)
    {
        cout << "func1: " << num << endl;
    }

    static void func2(int num)
    {
        cout << "func2: " << num << endl;
    }
    
    void printValue() {
        // Simulate some work
        this_thread::sleep_for(chrono::milliseconds(100));
        cout << "Value: " << value << endl;  // ⚠️ CRASH or garbage!
    }
};

thread createThread() {
    MyClass obj;  // obj is LOCAL to this functio
    obj.value = 43;
    // ❌ DANGEROUS: passing pointer to local object
    thread t(&MyClass::printValue, &obj);
    return t;  // obj goes out of scope HERE, but thread still running!
}

void simpleMethod(const string& str){
    cout<<str<<endl;
}
struct MyStruct {
    void func(int num) {
        cout << "MyStruct func: " << num << endl;
    }
};

int main() {
    thread t1(&MyClass::func1, MyClass(), 10); // Using member function
    thread t2(&MyClass::func2, 20); // Using static member function

    MyStruct obj;
    thread t3(&MyStruct::func, obj, 30); // Using struct member function
    thread t4([](int num) { cout << "Lambda: " << num << endl; }, 40); // Using lambda
    
    t1.join();
    t2.join();
    t3.join();
    t4.join();

    // before this
    //obj was on the stack with value = 43
    // createThread() returned → obj's memory is now "available" but not zeroed
    // Other code (function calls, joins, etc.) reused that stack memory
    // uncomment below block to see behaviour
    // auto th = createThread();    
    // // Do some stack operations that will overwrite obj's old memory
    // int x = 999;
    // int y = 888;
    // cout << "Stack vars: " << x << ", " << y << endl;
    // th.join();  // Now value might show 999, 888, or something else!


    thread th5(simpleMethod,"test constant ref");
    th5.join();

    
    return 0;
}