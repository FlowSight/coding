
    int eraseOverlapIntervals(vector<vector<int>>& arr) {
        sort(arr.begin(),arr.end(),[](const vector<int>& v1, const vector<int>& v2){
            return v1[0] == v2[0] ? v1[1]<v2[1] : v1[0] <v2[0];
        });
        int n = arr.size(), ans = 0;
        vector<int> last = arr[0];
        for(auto i=1;i<n;i++){
            if(arr[i][0] == last[0]){
                ans++;
            } else {
                if(arr[i][0] >= last[1]){
                    last = arr[i];
                    continue;
                }
                if(arr[i][1] <= last[1]){
                    last = arr[i];
                    ans++;
                } else {
                    ans++;
                }
            }
        }
        return ans;
    }




class Solution {
public:
    bool comp(vector<int> &a,vector<int> &b) {
	    return a[1]<b[1];
    }
	int eraseOverlapIntervals(vector<vector<int>>& intervals) {
		int ans=-1;      
		if(intervals.size()==0) return 0;       
		sort(intervals.begin(),intervals.end(),comp);      //custom comperator is used.
		vector<int> prev= intervals[0];

		for(vector<int> i: intervals) {
			if(prev[1]>i[0]) {
				ans++;                //we dont update previous, because i[1] will be grater then prev[1]
			}else prev=i;           // we want the end point to be minimum
		}
		return ans;                 //ans was initially made -1 because our prev and intervals[0] will always match
	}
};

////////

// lets explain the thought process...
// i initially thought..it has to be sorted by start time..because..if we dont have..meaning later start time before earlier start time..then i would not know if current end time is less than the start time as well...
// so to keep things sane i decided to just sort by start time as well as end time.......
// but...
// actually sorting by end time is sufficient...
// why....
// start time doesnt matter??
// if its like [10,20] [9,21] ...
// if current start time is less than so far end time....then we have a overlap...and we need to remove current...why?
// because we want to keep the one with least end time...until we find a new start time thats more than current end time....
