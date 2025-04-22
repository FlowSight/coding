// 15 apr 2025
// did it correct..remembered cpp remainder issue..but dry run fucked up..missed silly issue..
// also missed a corner case..2 corner case in total..

//19/2/25
//  same issue : forgot that cpp mod does actually give SIGNED CORRECT REMAINDER
// sev0 ... 


// 27dec 2024..
// missed many cases here..
// didnt know cpp mod results...its not same as python..so didnt rely on it..
// took lot of time to do...this is not ideal..
// sev0
// verdict : FAIL

    int reverse(int x) {
        int res = 0, tmp = x;
        while(x){
            if((INT_MAX/10 < res) || (INT_MIN/10 > res)) return 0; 
            res = (res*10) + (x%10);
            x/=10;
        }
        return res;
    }
};
