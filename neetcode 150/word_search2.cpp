// 20 feb 25
// coming off as TLE..although code is correct
// Issue : 2-3 compiler errror in first version of code..
// sev2

class Trie {
    public:
        vector<Trie*> children;
        int eow;
        Trie() {
            children = vector<Trie*>(26,nullptr);
            eow = 0;
        }
        void addWord(string& word, int idx){
            if(idx == word.size()){
                eow = 1;
                return;
            }
            int cIdx = word[idx]-'a';
            if(!children[cIdx]) {
                children[cIdx] = new Trie();
            }
            children[cIdx]->addWord(word,idx+1);
        }

};


class Solution {
public:
    vector<string> ans;
    vector<vector<int>> dirs = {{1,0},{0,1},{-1,0},{0,-1}};
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        Trie* trie = new Trie();
        for(auto &it : words){
            trie->addWord(it,0);
        }
        int m = board.size(), n = board[0].size();
        string word = "";
        for(auto i=0;i<m;i++){
            for(auto j=0;j<n;j++){
                word = "";
                helper(board,i,j,trie,word,m,n);
            }
        }
        return ans;
    }

    void helper(vector<vector<char>>& board, int r, int c, Trie* root, string& cur, int& m , int& n){
        if((r<0) ||  (c<0) || (r>=m) || (c>=n) || (board[r][c] == '#')) return;
        auto cIdx = board[r][c]-'a';

        if(!root->children[cIdx]) return;
        root = root->children[cIdx];

        cur.push_back(board[r][c]);
        board[r][c] = '#';

        if(root->eow){
            root->eow = false;
            ans.push_back(cur);
        }

        for(auto d: dirs){
            auto xx = d[0] + r, yy = d[1]+c;
            if((xx<0) ||  (yy<0) || (xx>=m) || (yy>=n) || (board[xx][yy] == '#')) continue;
            helper(board,xx,yy,root,cur,m,n);
        }

        board[r][c] = 'a'+cIdx;
        cur.pop_back();
    }
};

// median of median algorithm in cpp
int findMedian(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return -1; // Handle empty array case
    if (n == 1) return nums[0]; // Handle single element case

    // Step 1: Divide the array into groups of 5
    vector<int> medians;
    for (int i = 0; i < n; i += 5) {
        int end = min(i + 5, n);
        sort(nums.begin() + i, nums.begin() + end); // Sort each group
        medians.push_back(nums[i + (end - i) / 2]); // Add the median of the group
    }

    // Step 2: Recursively find the median of the medians
    return findMedian(medians);
}
// Step 3: Partition the original array around the median of medians
int pivot = findMedian(nums);
    vector<int> left, right;
    for (int num : nums) {
        if (num < pivot) left.push_back(num);
        else if (num > pivot) right.push_back(num);
    }

    // Step 4: Determine the median based on the size of the left and right partitions
    int k = n / 2;
    if (k < left.size()) return findMedian(left); // Median is in the left partition
    else if (k > n - right.size()) return findMedian(right); // Median is in the right partition
    else return pivot; // Pivot is the median
}