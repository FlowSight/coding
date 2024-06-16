#include <bitset>

using namespace std;

/// this technique can be used for subset sum or any other sum of numbers techniques
// basically, a bitset's ith bit if i can be acheived by sum of numbers (as per req)
int subsetSum(vector<int>& arr, int sum){
    bitset<10000> p(1);
    for (auto r : arr) {
        int tmp = 0;
        tmp |= (p << r);
        p |= tmp;
    }
    return p[sum];
}

