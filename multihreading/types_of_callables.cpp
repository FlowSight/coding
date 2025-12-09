#include <iostream>
#include <thread>
using namespace std;

class MyClass
{
public:
    void func1(int num)
    {
        cout << "func1: " << num << endl;
    }

    static void func2(int num)
    {
        cout << "func2: " << num << endl;
    }
};

struct MyStruct {
    void func(int num) {
        cout << "MyStruct func: " << num << endl;
    }
};

int main() {
    thread t1(&MyClass::func1, MyClass(), 10); // Using member function
    thread t2(&MyClass::func2, 20); // Using static member function

    MyStruct obj;
    thread t3(&MyStruct::func, &obj, 30); // Using struct member function
    thread t4([](int num) { cout << "Lambda: " << num << endl; }, 40); // Using lambda
    
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    return 0;
}