//  7 jan 2025
// 5.30 mins
// complier error : method name wrong+long/int mistake
// verdict : FAIL

    int minEatingSpeed(vector<int>& piles, int h) {
        long l = 1, r = INT_MAX, mid = 0;
        while(l<r){
            if(l+1==r) {
                if(isValid(piles,h,l)) return l;
                return r;
            }
            mid = (l+r)/2;
            if(isValid(piles,h,mid)){
                r = mid;
            } else {
                l = mid+1;
            }
        }
        return l;
    }

    bool isValid(vector<int>& arr, int h, int rate){
        int totHrs = 0;
        for(auto& it : arr){
            totHrs += it/rate + (it%rate>0);
        }
        return totHrs <= h;
    }
};


