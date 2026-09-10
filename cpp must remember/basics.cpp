#include <bits/stdc++.h>
using namespace std;

// how to set precision:
ostringstream oss;
oss << fixed << std::setprecision(3) << ans;
return oss.c_str();

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

map : dont dp mm[key], do mm.find(key)
becareful : mm[key] is 0 if not present

explicit: forces compiler to match types in constructor..doesnt assume anything


/////////
CAS
//////////
atomic<int> val{0};
int expected = 0, desired = 42;
if(val.compare_exchange_strong(expected,desired)) {
    // set
} else{
    // expected = val
}
    ==== is same as==
    if(val == expected) {
        val = desired
    } else {
        expected = val
    }

/////////////////////////////memset / fill gotchas/////////////////////////////
// VERIFIED via compiled test -- these are not theoretical, all reproduced directly:

// GOTCHA 1: memset fills BYTE BY BYTE, not value by value. Only safe for 0 and -1.
int arr[5];
memset(arr, 1, sizeof(arr));
// arr[0] == 16843009, NOT 1!! memset(arr,1,...) writes the byte 0x01 into EVERY byte
// of every int, so a 4-byte int becomes 0x01010101 = 16843009.
memset(arr, 0, sizeof(arr));  // arr[0] == 0   -- SAFE (all-zero-bytes == int 0)
memset(arr, -1, sizeof(arr)); // arr[0] == -1  -- SAFE (all-1-bits == int -1, two's complement)
// RULE: only ever memset with 0 or -1 for int/long arrays. For ANY other value, use fill().

// GOTCHA 2: memset on a function parameter (decayed array = pointer) uses the WRONG size.
void setWrong(int* p) {
    memset(p, 0, sizeof(p)); // sizeof(p) == 8 (pointer size), NOT the array's real byte size!
    // compiler even warns: "memset call operates on objects of type 'int' while the size
    // is based on a different type 'int *'" -- only the first ~2 ints get zeroed, rest untouched.
}
// RULE: never memset inside a function using sizeof() on a pointer parameter. Pass the
// element count explicitly instead: memset(p, 0, n * sizeof(int));

// GOTCHA 3: raw pointer-array "fill" can alias rows (all rows = same memory).
int** rows = new int*[3];
int* shared = new int[4]{0,0,0,0};
fill(rows, rows+3, shared);   // all 3 row pointers now point to the SAME int[4]!
rows[0][0] = 99;              // rows[1][0] is ALSO now 99 -- not independent rows.
// RULE: never fill() an array of raw pointers with one shared buffer if you need independent rows.

// SAFE alternatives (verified correct):
vector<int> v(5);
fill(v.begin(), v.end(), 1);              // v[0]==1, correct -- fill does real assignment, not byte-copy
vector<vector<int>> vv(3, vector<int>(4, 0));  // independent inner vectors, no aliasing, vv[1][0]==0 always
// std::fill and the (n, vector<T>(m,val)) constructor are always safe for ANY value/type --
// prefer these over memset unless you specifically need memset's raw-byte speed for 0/-1 fills.