#include <bits/stdc++.h>
using namespace std;



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