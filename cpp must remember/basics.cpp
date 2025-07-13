#include <bits/stdc++.h>
using namespace std;


labs for long abs

// locking unlocking
std::mutex mtx;
std::lock_guard<std::mutex> lock(mtx); // unlocks the mutex automatically when it goes out of scope // locks the mutex automatically when it goes out of scope

always init a class constructor with explicit  arg 
when storing in an index arr[i] = arr[j]*mult + arr[i].. this mod > max(arr[j],arr[i])


digit dp/sum :
if digit has to be considered only once 
    for (auto d: digits){
        for(auto i=1;i<=sum;i++){
            ...
        }
    }

// right shift of signed negative number in 2s compliment is implementation defined...dont try this 
// while coding..always convert to unsigned first
2s compliment = 
msb 1 : negative number
msb 0 : positive number

take rest bits + flip + add 1
-7 = 
7 is 111 -backtrack-> 110 --flip-> 001
then -7 = 1001 = 9
same -9 =  7 = 

how to get 2s compliment?
1s compliment + 1
to denote a positive number, write in proper binary format
then take 1s compliment
then add 1 to it
e.g. for 4 bit system 
int num = 9; // 1001
1s compliment = 0110
+1 = 0111
2^4 - num = 16 - 9 = 7 = 0111



priority_queue basic is REVERSE ORDER


this is must..without vector<int> declaration it wont understand how to compare..
priority_queue<int, vector<int>,greater<int>> pq; 

array/SET/MAP
    upper_bound : >
    lower_bound : >=
vector of pair : 
    upper_bound : (=,>) or (>,?)
    lower_bound : (=,>=) or (>,?)

MAP 
// lower bound code
int getLowerBound(int key){
    if(mm.size() == 0) return -1;
    auto it = mm.lower_bound(key);
    if(it ==mm.end() || it->first > key) it--;
    if(it->first > key) return -1;
    return it->second;
}

// upper bound code..
int getUpperBound(int key){
    if(mm.size() == 0) return -1;
    auto it = mm.lower_bound(key);
    if(it ==mm.end()) return -1;
    return it->second;
}

/////////////////////////////comparators///////////////////////

 //if you HAVE TO use given STRUCT :
    struct cmp {
        bool operator() (const ListNode* node1, const ListNode* node2) const {
            return node1->val < node2->val;
        }
    };
    // works for:pq, sets 
    // pq needs vector and opp comparator

// if you HAVE TO use given CLASS :
    struct cmp {
        bool operator< (const ListNode* node1) const {
            return this->val < node1->val;
        }
    };

// if you are flexible, choose struct over class..

// if you have to get multiple bounds in a sorted set (e.g. array or other)..
// use lower bound or upper bound but not both 
// how?
// lets say in an array you need to find (l..r) where arr[l]>= num1 and arr[r]<=num2..
// basically a bounded range
// you can do  l= lower_bound(num1); r =lower_bound(num2+1);
// OR 
// l= upper_bound(num1-1); r =upper_bound(num2);
// THIS WILL WORK FOR DUPLICATES ALSO.


// string :
// find : s1.find(s2)
// susbtr : s1.substr(start, len) // len is optional

// parsing
string str = "hello world", tmp = "";
char delim = ';';
stringstream ss(str);
while (getline(ss,tmp,delim))
{
    /* code */
}


// when in a mtrix or grid, traversal can happen L-R-U-D all dirs, then its 
// possible to have a path that like a U and invered u. Hence if 
// you traverse the matrix in a strict order, i.e. for all x in 0 to n-1 , 
// for all y in 0 to m-1, then your current cells ans is dependent on a cell 
// that you have not YET TRAVERSED. REMEMBER THIS KEY.