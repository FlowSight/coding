
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;


// When an expression was evaluated in left-hand mode, it yielded an address, and when it was evaluated in right-hand mode, it yielded a “rule for the computation of a value”. 

struct myStruct { 
    myStruct(int v) : value(v) {}
    int value; 
    void operator++() { // prefix increment
        value++;
    }
    void operator+(myStruct ms) { // prefix increment
        value += ms.value;
    }
};

class myClass {
    public:
    vector<int> bigBuffer; // imagine this is a really big buffer
    myClass() {
        bigBuffer.resize(10000000, 10);
    }
    myClass(const myClass& other) {
        // Usually in here we would use `new` and `memcpy` or `std::copy(...)`
        // to copy contents large buffers from clref to this object.
        // We simulate that with a long sleep.
        int startTime = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        this->bigBuffer = other.bigBuffer;
        //std::this_thread::sleep_for(std::chrono::seconds(1));
        int endTime = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        std::cout << "Copy constructor took " << (endTime - startTime) << endl;
    }

    myClass(myClass&& other) {
        // Usually in here we would rip out the contents from rref and leave rref in
        // a valid but unspecified state.
        // This is as simple as a pointer assignment.
        // It's on the order of nanoseconds.
        int startTime = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        this->bigBuffer = std::move(other.bigBuffer);
        //std::this_thread::sleep_for(std::chrono::nanoseconds(1));
        int endTime = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        std::cout << "Move constructor took " << (endTime - startTime) <<endl;
    }
};

// wont go with rvalue references
// myStruct operator+(myStruct& i1, myStruct& i2) {
//     return myStruct(i1.value + i2.value);
// }



void testRvalue() {
    int x = 5;
    int y = 10;
    // below line : copies x's val in a register, adds y's val to it, and copies the result back to z's memory location
    int z = x + y; // x and y are rvalues here
    // int& a = 1 // wrong, l is not lvalue

    myStruct s(10); // s is lvalue
    ++s; // s is lvalue here
    cout<<s.value<<endl; // prints 11
    myStruct t(20);
    //s = s + t; // both s and t are lvalues here
    cout<<s.value<<endl; // prints 31
    // auto result2 = myStruct(10) + myStruct(20); // wont compile, both rhs is rvalue
    //but it(above) would have worked if the code was like
    // myStruct operator+(const myStruct& i1,const myStruct& i2)
    // because then, it would case myStruct(10) to a lvalue
    //s = 4; // `4` is an rvalue, and implicitly converted to `myStruct(4)`, also rvalue.
    s + s; // `s`is lvalues, and converted to rvalues (prvalues)
    myStruct(2) + myStruct(3); // `myStruct(2)` is a prvalue, and it is materialized as an xvalue

}

// copy ellision
// std::string createString() {
//     std::string s = "hello";  // 1. Construct s
//     return s;                  // 2. Copy s to a temporary
// }                              // 3. Destroy s

// std::string result = createString();  // 4. Copy temporary to result
//                                        // 5. Destroy temporary
//with copy ellision, Compiler constructs "hello" directly into result's memory
// No copies at all!
//types of copy elision:
// 1. Return Value Optimization (RVO) : return myStruct()
// 2. Named Return Value Optimization (NRVO) : return s;
// 3. Copy elision in throw and catch

void moveTest(){
    myClass d;
    // Copying
    std::cout << "Copying is slow..." << std::endl;
    myClass cd(d);
    // Moving
    std::cout << "Moving is fast!" << std::endl;
    // when we move, d although is lvalue, its turned into 'rvalue reference' ie. T&&
    // when we allow the lvalue reference’s contents to be moved, 
    // it usually should be considered expired as it’s left in a valid but unspecified state.
    myClass md(std::move(d));
}


// vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
//         vector<vector<string>> ans;
//         unordered_set<string> valid, visited;
//         for(auto &it : wordList)valid.insert(it);
//         if(valid.find(endWord) == valid.end()) return ans;
//         if(beginWord == endWord) {
//             ans.push_back({endWord});
//             return ans;
//         }
//         int len = beginWord.size();

//         deque<vector<string>> q;
//         q.push_back({beginWord});
//         int minLen = INT_MAX, level = 0;

//         while(!q.empty() && (minLen == INT_MAX)){
//             auto sz = q.size();
//             level++;
//             for(auto& it : visited) valid.erase(it);
//             visited.clear();
//             while(sz--){
//                 auto curList = q.front();
//                 q.pop_front();
//                 auto word = curList.back();
//                 for(auto i=0;i<len;i++) {
//                     auto tmp = word[i];
//                     for(auto c='a';c<='z';c++){
//                         word[i] = c;
//                         if(valid.find(word) == valid.end()) continue;
//                         visited.insert(word);
//                         curList.push_back(word);
//                         if(word == endWord) {
//                             ans.push_back(curList);
//                             minLen = level;
//                         }
//                         else {
//                             q.push_back(curList);
//                         }
//                         curList.pop_back();
//                     }
//                     word[i] = tmp;
//                 }
//             }
//         }
//         return ans;
//     }



    int main(){
    //testRvalue();
    moveTest();
    return 0;
}