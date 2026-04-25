//LC : 755

// 16apr2026
// sev3: didnt get the exact output at start. but sev0 for optimal approach



// optimal.O(N) time..
class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vector<int> pourWater(vector<int>& heights, int volume, int k) {
        stack<int> st, leftfall, rightfall;
        int n = heights.size(),leftboundary = k, rightboundary = k;
        for(auto i=1;i<=volume;i++){
            while((leftboundary>0) && (heights[leftboundary-1] <= heights[leftboundary])) {
                leftboundary--;
                if(heights[leftboundary] < heights[leftboundary+1]) leftfall.push(leftboundary);
            }
            while((rightboundary<n-1) && (heights[rightboundary+1] <= heights[rightboundary])) {
                rightboundary++;
                if(heights[rightboundary] < heights[rightboundary-1]) rightfall.push(rightboundary);
            }
            if(!leftfall.empty()){
                auto idx = leftfall.top();
                heights[idx]++;
                if(heights[idx] == heights[idx+1]) leftfall.pop();
                if((idx>leftboundary) && (heights[idx] > heights[idx-1])) leftfall.push(idx-1);
            } else if(!rightfall.empty()){
                auto idx = rightfall.top();
                heights[idx]++;
                if(heights[idx] == heights[idx-1]) rightfall.pop();
                if((idx<rightboundary) && (heights[idx] > heights[idx+1])) rightfall.push(idx+1);
            } else {
                heights[k]++;
                if(k>leftboundary)leftfall.push(k-1);
                if(k<rightboundary)rightfall.push(k+1);
            }
        }
        return heights;
    }
};

//O(vn) time..not optimal
class Solution {
public:
    vector<int> pourWater(vector<int>& heights, int volume, int k) {
        for(auto i=1;i<=volume;i++){
            int leftidx = moveLeft(heights,k);
            if(leftidx != -1) {
                heights[leftidx]++;
                continue;
            }
            int rightidx = moveRight(heights,k);
            if(rightidx != -1) {
                heights[rightidx]++;
                continue;
            }
            heights[k]++;
        }
        return heights;
    }

    int moveLeft(vector<int>& heights, int idx){
        int height = heights[idx],  n = heights.size(), k = idx;
        while((idx>0) && (heights[idx] >= heights[idx-1])) idx--;
        while((idx<k) && (heights[idx] == heights[idx+1])) idx++;
        return heights[idx] < height ? idx : -1;
    }

    int moveRight(vector<int>& heights, int idx){
        int height = heights[idx],  n = heights.size(),  k = idx;
        while((idx<n-1) && (heights[idx] >= heights[idx+1])) idx++;
        while((idx>k) && (heights[idx] == heights[idx-1])) idx--;
        return heights[idx] < height ? idx : -1;
    }
};

// 2 1 1   (2) 2 1 2 2
// 1 1 1 1   (1) 2 2 2 2   // 3
//     *           
//                 *    