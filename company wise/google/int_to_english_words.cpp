class Solution {
public:
    unordered_map<int,string> keyword;
    int billion = 1e9, million = 1e6, thousand = 1e3;
    string numberToWords(int num) {
        if(num == 0) return "Zero";
        keyword[1] = "One";
        keyword[2] = "Two";
        keyword[3] = "Three";
        keyword[4] = "Four";
        keyword[5] = "Five";
        keyword[6] = "Six";
        keyword[7] = "Seven";
        keyword[8] = "Eight";
        keyword[9] = "Nine";
        keyword[10] = "Ten";
        keyword[11] = "Eleven";
        keyword[12] = "Twelve";
        keyword[13] = "Thirteen";
        keyword[14] = "Fourteen";
        keyword[15] = "Fifteen";
        keyword[16] = "Sixteen";
        keyword[17] = "Seventeen";
        keyword[18] = "Eighteen";
        keyword[19] = "Nineteen";
        keyword[20] = "Twenty";
        keyword[30] = "Thirty";
        keyword[40] = "Forty";
        keyword[50] = "Fifty";
        keyword[60] = "Sixty";
        keyword[70] = "Seventy";
        keyword[80] = "Eighty";
        keyword[90] = "Ninety";
        vector<string> ans;
        string res = "";
        while(num){
            if(num>=billion) {
                auto val = num/billion;
                subThousand(val,ans);
                ans.push_back("Billion");
                num%=billion;
            } else  if(num>=million) {
                auto val = num/million;
                subThousand(val,ans);
                ans.push_back("Million");
                num%=million;
            } else  if(num>=thousand) {
                auto val = num/thousand;
                subThousand(val,ans);
                ans.push_back("Thousand");
                num%=thousand;
            } else {
                subThousand(num,ans);
                num = 0;
            } 
        }
        for(auto it : ans){
            res += it;
            res.push_back(' ');
        }
        if(res.back() == ' ') res.pop_back();
        return res;
    }

    void subThousand(int& num,vector<string>& ans){
        while(num){
            if(num>=100) {
                auto val = num/100;
                ans.push_back(keyword[val]);
                ans.push_back("Hundred");
                num%=100;
            } else if(num>20) {
                auto val = num/10;
                ans.push_back(keyword[val*10]);
                num%=10;
            } else {
                ans.push_back(keyword[num]);
                num = 0;
            }
        }
    }
};