#include<iostream>
#include<string>
#include<sstream>
#include<unordered_set>


using namespace std;


struct Business {
    public:
    string id = "",name = "",url = "",shdec = "",fuldesc = "",proddet = "";
    Business() = default;
};

vector<string> errorStrs = {"", "ERROR_MISSING_FIELDS,", "ERROR_INVALID_LENGTH", "ERROR_GENERIC_NAME", "ERROR_NAME_MISMATCH"};

class BusinessDataParser{
    public:
    BusinessDataParser(string _csvstring, vector<string> _blocked_words){
        csvstring = _csvstring;
        for(auto it : _blocked_words){
            auto lowercase = lower(it);
            blocked_words.insert(lowercase);
        }
    }
    void validate_businesses(){
        int cnt = 0, idx = 0, failed = 0;
        string line = "", val ="";
        stringstream ss(csvstring);
        while(getline(ss,line,'\n')){
            cnt++;
            Business b;
            if(cnt == 1) continue;
            stringstream ls(line);
            while(getline(ls,val,',')) {
                if(val.size() == 0) {
                    failed = 1;
                    break;
                }
                if(idx == 0)b.id = val;
                else if(idx == 1)b.name= val;
                else if(idx == 2)b.url= val;
                else if(idx == 3)b.shdec= val;
                else if(idx == 4){
                    auto str = pruneWhitespace(val);
                    if((str.size()<5) || (str.size()>31)) {
                        failed = 2;
                        break;
                    }
                    if(containsBlockedWords(val) ) {
                        failed = 3;
                        break;
                    }
                    b.fuldesc= val;
                    if(!halfNamecontainedInDesc(b.name,b.shdec,b.fuldesc)) {
                        failed = 4;
                        break;
                    }
                }
                else b.proddet= val;
                idx++;
            }
            idx = 0;
            if(failed) {
                cout<<errorStrs[failed] << ": " <<b.name<<endl;
            }
            else cout<<"VERIFIED: " << b.name<<endl;
            failed = 0;
        }
    }

    private:
    string csvstring;
    unordered_set<string> blocked_words;

    string pruneWhitespace(string& str){
        string ans = "";
        for(auto c:str){
            if(c ==' ') continue;
            ans.push_back(c);
        }
        return ans;
    }

    string lower(string word){
         for(auto &c : word){
            if(isupper(c)) c = tolower(c);
        }
        return word;
    }

    bool containsBlockedWords(string val){
        val = lower(val);
        for(auto &it : blocked_words){
            if(val.find(it) != string::npos) return true;
        }
        return false;
    }

    bool halfNamecontainedInDesc(string name, string sdesc, string ldesc){
        stringstream ss(name);
        string word = "";
        vector<string> namewords;
        unordered_set<string> descwords;
        //cout<<name<< "==="<<sdesc<<"==="<<ldesc<<endl;
        while(getline(ss,word, ' ')){
            if(word == "LLC" || (word == "Inc") || (word == "Inc.")) continue;
            word = lower(word);
            namewords.push_back(word);
        }
        stringstream ss1(sdesc);
        while(getline(ss1,word, ' ')){
            if(word == "LLC" || word == "Inc") continue;
            word = lower(word);
            descwords.insert(word);
        }
        stringstream ss2(ldesc);
        while(getline(ss2,word, ' ')){
            if(word == "LLC" || word == "Inc") continue;
            word = lower(word);
            descwords.insert(word);
        }
        int ans = 0;
        for(auto it : namewords){
            if(descwords.find(it) != descwords.end()) ans++;
        }
        double frac = 1.0 * (ans/namewords.size());
        return frac >= 0.5;
    }
};

void testmethod1(){
    string csvstring = "col1,col2,col3,col4,col5,col6\n"
                        "BIZ001,Pawsome Pets Inc.,pawsomepets.com,Pawsome,PAWSOME PETS INC,Premium pet supplies\n"
                        "BIZ002,Bean Bliss Coffee,beanbliss.com,,,Artisan coffee roasters\n"
                        "BIZ003,Short Name,short.com,Short,SHRT,Products\n"
                        "BIZ004,Generic Store,generic.com,Store,RETAIL,Various items\n"
                        "BIZ005,Mismatched Corp,mismatch.com,Wrong,DIFFERENT BUSINESS,Services";

    vector<string> blockedwords = {"ONLINE STORE" , "ECOMMERCE",  "RETAIL" , "SHOP", "GENERAL MERCHANDISE"};
    BusinessDataParser bdp(csvstring,blockedwords);
    bdp.validate_businesses();
}
int main(){
    testmethod1();
    return 0;
}

// lines of , seperated values 
// skip first line
// parse each next line 