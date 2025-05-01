// 22 apr 2025
// 5 min clean 
// but this is not the best approach O(sqrt(n)*log(n))/O(1) --can be improved to--> O(sqrt(n))/O(n)
// other approaches are  : hashset = O(sqrt(n))/O(n) or two pointers = O(sqrt(n))/O(1)
// didnt think of 2 pointer + hashset approach
// sev3

class Solution {
    public:
        bool judgeSquareSum(int c) {
            int root = sqrt(c), rem = 0;
            for(auto i=0;i<=root;i++) {
                rem = c-i*i;
                if(isSquare(rem)) return true;
            }
            return false;
        }
    
         bool isSquare(int& n){
            int root = sqrt(n);
            return root*root == n;
         }
    };
    
    // c = 5
    // root = 2
    // i=1
    // isSquare(c-i*i) = isSquare(4)