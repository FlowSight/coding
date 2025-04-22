
// 13 apr ..
// 7 mins..
// 1 silly complier mistake of ;..
// sev3
// didnt come up with O(1) space solution..I could not get the diff between up->down vs
// down->up...there is a diff..


// O(1) space solution
//  3 2 1 2 3 4
//  3 2 1 2 3 4

//  1 2 3 4 3 2
//  1 2 3 4 2 1

// the diif between incr->decr vs decr->incr is when we are incr->decr..the peak is fixed..so the peak
// should not be DOUBLY calculated by both slopes. BUT when decr->incr...both peaks have no limit to go to..sky
// is the limit..but the bottom is fixed at 1.

int candy(vector<int>& ratings) {
    int n = ratings.size(), ans = n, up = 0, down = 0;
    for(auto i=1;i<n;i++){
        up = down = 0;
        if(ratings[i] == ratings[i-1]) continue;
        while((i<n) && (ratings[i] > ratings[i-1])) {
            up++;
            ans += up;
            i++;
        }
        while ((i<n) && (ratings[i] < ratings[i-1])) {
            down++;
            ans += down;
            i++;
        }
        i--;
        ans -= min(up,down);
    }
    return ans;
}



class Solution {
    public:
        int candy(vector<int>& ratings) {
            int n = ratings.size(), ans = 0;
            vector<int> arr(n,1);
            for(auto i=1;i<n;i++){
                if(ratings[i] > ratings[i-1]) {
                    arr[i] =  max(arr[i],arr[i-1]+1);
                }
            }
            for(auto i=n-2;i>=0;i--){
                if(ratings[i] > ratings[i+1]) {
                    arr[i] =  max(arr[i],arr[i+1]+1);
                }
                ans += arr[i];
            }
            return ans + arr.back();
        }
    };
    
    