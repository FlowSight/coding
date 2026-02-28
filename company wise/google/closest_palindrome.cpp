/// Severity: Sev0
// Date: 23Feb26
// LC: 564
// Where I failed: algo
// Pattern: greedy,string
// Notes: na



class Solution {
public:
    string nearestPalindromic(string str) {
        int len = str.size();
        long long num = stol(str), ansGap = LONG_MAX;
        // 1-9 case
        if(len==1) return to_string(num-1); 
        if((str[0] == '1') && (str.substr(1) == string(len-1,'0'))) return to_string(num-1); // 10,100 case

        // 999 case
        if(str == string(len,'9')) return to_string(num+2);
        // 101, 1001 case
        if((str[0] == '1') && (str[len-1] == '1') && (str.substr(1,len-2) == string(len-2,'0'))) return to_string(num-2); 

        string half = str.substr(0,(len+1)/2), anssmall = half, anslarge = half, anseq = half, rev = half, ans = "0";
        long long halfNum = stol(half);

        rev = to_string(halfNum-1);
        anssmall = to_string(halfNum-1);
        for(int i=rev.size()-1 - (len%2);i>=0;i--) anssmall.push_back(rev[i]);
        ans = anssmall;
        ansGap = abs(stol(anssmall) - num);

        rev = to_string(halfNum+1);
        anslarge = to_string(halfNum+1);
        for(int i=rev.size()-1 - (len%2);i>=0;i--) anslarge.push_back(rev[i]);
        if((abs(stol(anslarge) - num) < ansGap) ||
             (((abs(stol(anslarge)- num)) == ansGap) && (stol(anslarge) < stol(ans)))) {
            ans = anslarge;
            ansGap = abs(stol(anslarge) - num);
        }

        rev = to_string(halfNum);
        anseq = to_string(halfNum);
        for(int i=rev.size()-1 - (len%2);i>=0;i--) anseq.push_back(rev[i]);
        if(anseq != str) {
            if((abs(stol(anseq) - num) < ansGap) ||
                (((abs(stol(anseq)- num)) == ansGap) && (stol(anseq) < stol(ans))))   {
                ans = anseq;
            }
        }

        return ans;

    }
};