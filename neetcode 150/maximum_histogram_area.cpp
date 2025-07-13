// 14 apr 2025
// fucked up next min cal..named it as next max..took too much time..
// then fucked up index cal..
// also one silly mistake..
// sev0 sev0

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size(), ans = 0;
        vector<int> leftMax(n,-1), rightMax(n,n),st;
        for(auto i=n-1;i>=0;i--){
            while(!st.empty() && (heights[i] < heights[st.back()])) {
                leftMax[st.back()] = i;
                st.pop_back();
            }
            st.push_back(i);
        }
        st = vector<int>();
        for(auto i=0;i<n;i++){
            ans = max(ans,heights[i]);
            while(!st.empty() && (heights[i] < heights[st.back()])) {
                rightMax[st.back()] = i;
                st.pop_back();
            }
            st.push_back(i);
        }

        for(auto i=0;i<n;i++){
            ans = max(ans,(rightMax[i]-leftMax[i]-1)*heights[i]);
        }
        return ans;
    }
};


// only stack
// basically when some element is popped, its left is either the next element on stack, or 0, right is the current index
int largestRectangleArea(vector < int > & histo) {
      stack < int > st;
      int maxA = 0;
      int n = histo.size();
      for (int i = 0; i <= n; i++) {
        while (!st.empty() && (i == n || histo[st.top()] >= histo[i])) {
          int height = histo[st.top()];
          st.pop();
          int width;
          if (st.empty())
            width = i;
          else
            width = i - st.top() - 1;
          maxA = max(maxA, width * height);
        }
        st.push(i);
      }
      return maxA;
    }