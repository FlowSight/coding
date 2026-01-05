// #include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

diff_one={0:'A', 3:'B'}, 
diff_two={0:'C', 4:'D'}, 
orig={0:'z', 1:'z', 2:'z'} == z-z-z 
after applying diff_one = A-z-z-B-z
after applying diff_two = C-A-z-z-D-B-z
..just do dll..??
// Key insight: The indices in diff_one and diff_two represent INSERTION positions
// Apply diff_one first, then diff_two. When inserting, indices shift subsequent elements.
// 
// Example walkthrough:
// orig = [z, z, z]
// diff_one = {0: 'A', 3: 'B'}
//   Insert 'A' at 0: [A, z, z, z]
//   Insert 'B' at 3: [A, z, z, B, z]
// 
// diff_two = {0: 'C', 4: 'D'}
//   Insert 'C' at 0: [C, A, z, z, B, z]
//   Insert 'D' at 4: [C, A, z, z, D, B, z]
//
// Result: {0: 'C', 1: 'A', 2: 'z', 3: 'z', 4: 'D', 5: 'B', 6: 'z'} ✓

vector<char> merge_diffs(map<int, char>& diff_one, map<int, char>& diff_two, vector<char>& original) {
    // Merge both diffs: diff_two takes precedence where indices overlap
    map<int, char> merged_diff = diff_one;
    for (auto& [index, ch] : diff_two) {
        merged_diff[index] = ch;
    }
    
    // Optimization: Use list for O(1) insertions instead of vector's O(n) insert
    list<char> result(original.begin(), original.end());
    
    // Insert in REVERSE order to avoid index shifting issues
    for (auto it = merged_diff.rbegin(); it != merged_diff.rend(); ++it) {
        auto pos = result.begin();
        advance(pos, it->first);
        result.insert(pos, it->second);
    }
    
    return vector<char>(result.begin(), result.end());
}

int main() {
    // Test with the provided example
    map<int, char> diff_one = {{0, 'A'}, {3, 'B'}};
    map<int, char> diff_two = {{0, 'C'}, {4, 'D'}};
    vector<char> orig = {'z', 'z', 'z'};
    
    vector<char> result = merge_diffs(diff_one, diff_two, orig);
    
    cout << "Result: ";
    for (int i = 0; i < result.size(); i++) {
        cout << i << ":'" << result[i] << "' ";
    }
    cout << endl;
    
    // Expected: 0:'C' 1:'A' 2:'z' 3:'z' 4:'D' 5:'B' 6:'z'
    
    return 0;
}