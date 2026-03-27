#include<iostream>

using namespace std;

typedef vector<char> vc;
typedef vector<string> vs;
typedef vector<vc> vvc;


struct Font {
    string name;
    unordered_map<char,vs> charmap;
    Font(string _n , unordered_map<char,vs> _chm){
        name = _n;
        charmap = _chm;
    }
};

class BitFontHelper {
    public:
    vs render_character(vs grid){
        vs ans;
        for(auto it : grid){
            for(auto &it1 : it){
                if(it1 == '0') it1 = '.';
                else it1 = '#';
            }
            ans.push_back(it);
        }
        return ans;
    }
    vs render_character(string text, Font font ){
        vs ans;
        for(auto ch : text){
            for(auto i=0;i< font.charmap[ch].size();i++) {
                if(ans.size() == i) {
                    ans.push_back(font.charmap[ch][i]);
                } else {
                    ans[i] += font.charmap[ch][i];
                }
            }
        }
        return render_character(ans);
    }
    vs render_word_rle(string text, Font font ){
        vs ans;
        for(auto ch : text){
            for(auto i=0;i< font.charmap[ch].size();i++) {
                if(ans.size() == i) {
                    ans.push_back(font.charmap[ch][i]);
                } else {
                    ans[i] += font.charmap[ch][i];
                }
            }
        }
        ans = decoder(ans);
        return render_character(ans);
    }

    vs decoder(vs arr){
        vs ans;
        string cur = "";
        int curDig = 0;
        for(auto it : arr){
            cur = "";
            curDig = 0;
            for(auto ch : it){
                if(isDigit(ch)){
                    int cnt = (ch-'0');
                    for(auto i=1;i<=cnt;i++) cur.push_back((curDig+'0'));
                } else {
                    int cnt = 10 + (ch-'a');
                    for(auto i=1;i<=cnt;i++) cur.push_back((curDig+'0'));
                }
                curDig ^= 1;
            }
            ans.push_back(cur);
        }
        return ans;
    }
    bool isDigit(char c){
        return (c>='0') && (c<='9');
    }
};
// dim might be diff 
// char will be in map?yes

void testmethod1(){
    vs grid = {
        "0000000",
        "0001000",
        "0001000",
        "0101000",
        "0010000"
    };
    BitFontHelper bfh;
    vs ans = bfh.render_character(grid);
    for(auto it : ans)cout<<it<<endl;
}

void testmethod2(){
    BitFontHelper bfh;
    unordered_map<char,vs> charmap;
    charmap['H'] = {
            "10001",
            "10001",
            "1111",
            "10001",
            "10001"
    };
    charmap['I'] = {
            "111",
            "010",
            "010",
            "010",
            "111"
    };
    charmap['U'] = {
            "111",
            "01",
            "010",
            "010",
            "111"
    };
    charmap['A'] = {
            "212", "11111", "05", "0131", "0131"
    };
    Font font("RLE Font",charmap);
    vs ans = bfh.render_word_rle("A",font);
    for(auto it : ans)cout<<it<<endl;
}

int main(){
    testmethod2();
    return 0;
}



// O(mn) /O(1)