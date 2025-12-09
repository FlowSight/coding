// You are given n randomly generated connected graphs. You need to merge these n graphs into a single graph by randomly picking one graph and connecting with the another. Each graph has to be equally likely to be picked up.

// Example: if there are three graphs x, y, z - then each time your function is called, it should return one of the following connected single graph equally likely:

// x -- y -- z
// or
// x -- z -- y
// or
// y -- x -- z

// Each graph x, y, z can have any number of nodes and x, y, z are themselves connected. You need to decide how to represent the graph.

// Every time the function is called, it has to randomly return one of the possible connected graphs.

//fisher yates shuffle

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

// Fisher-Yates Shuffle Algorithm
// Time Complexity: O(n)
// Space Complexity: O(1) - in-place shuffle


// Alternative implementation with explicit swap
void fisherYatesShuffleExplicit(vector<int>& arr) {
    int n = arr.size();
    srand(time(0));
    
    for (int i = n - 1; i > 0; i--) {
        // Random index from 0 to i
        int j = rand() % (i + 1);
        
        // Swap
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

int main() {
    // Test with another shuffle
    vector<int> arr2 = {1, 2, 3, 4, 5};
    cout << "\nOriginal array 2: ";
    for (int x : arr2) cout << x << " ";
    cout << endl;
    
    fisherYatesShuffleExplicit(arr2);
    
    cout << "Shuffled array 2: ";
    for (int x : arr2) cout << x << " ";
    cout << endl;
    
    return 0;
}