#include<iostream>
#include<string>
#include<sstream>
#include<unordered_set>


using namespace std;

typedef vector<string> vs;

struct Business {
    public:
    string id = "",name = "",url = "",shdec = "",fuldesc = "",proddet = "";
    Business() = default;
    Business(string _id, string _n, string _url, string _shdec, string _fd, string _proddet) {
        id = trim(_id), name = trim(_n);
        url = trim(_url), shdec = trim(_shdec);
        fuldesc = trim(_fd), proddet = trim(_proddet);

    }
    bool isValid(){
        if(id.empty() || name.empty() || shdec.empty() || fuldesc.empty()
            || proddet.empty()) return false;
        if((fuldesc.size()<5) || (fuldesc.size()>31)) return false;
        return true;
    }

    string trim(string str){
        string ans = "";
        int n = str.size(), idx = 0;
        while((idx<n) && (str[idx] == ' ')) idx++;
        while(idx<n) ans.push_back(str[idx++]);
        while(ans.size() && (ans.back() == ' ')) ans.pop_back();
        return ans;
    }
};

vector<string> errorStrs = {"", "ERROR_MISSING_FIELDS,", "ERROR_INVALID_LENGTH", "ERROR_GENERIC_NAME", "ERROR_NAME_MISMATCH"};

class BusinessDataParser{
    public:
    BusinessDataParser(string _csvstring, vector<string> _blocked_words){
        csvstring = _csvstring;
    }
    void validate_businesses(vector<Business> arr){
        for(auto it : arr){
            if(it.isValid()) cout<<"VERIFIED: "<<it.name<<endl;
            else cout<<"NOT VERIFIED: "<<it.name<<endl;
        }
    }
    static vs parsehelper(string str, char del){
        vs ans;
        stringstream ss(str);
        string cur = "";
        while (getline(ss,cur,del))
        {
           ans.push_back(cur);
        }
        return ans;
    }

    private:
    string csvstring;
    unordered_set<string> blocked_words;

};

void testmethod1(){
    string csvstring = "col1,col2,col3,col4,col5,col6\n"
        "BIZ001,Pawsome Pets Inc.,pawsomepets.com,Pawsome,PAWSOME PETS INC,Premium pet supplies\n"
        "BIZ002,Bean Bliss Coffee,beanbliss.com,Bean,   Bean   ,Artisan coffee roasters\n"
        "BIZ003,Oakridge Furniture,oakridge.com,Oak,OAKRIDGE CUSTOM WOODWORKING AND FURNITURE EMPORIUM,Custom furniture\n"
        "BIZ004,Tech Solutions,techsol.io,Tech,IT    CS,Software consulting\n";
    vector<Business> arr;
    vs cols = BusinessDataParser::parsehelper(csvstring,'\n');
    for(auto i=1;i<cols.size();i++) {
        vs vals = BusinessDataParser::parsehelper(cols[i],',');
        arr.push_back(Business(vals[0],vals[1],vals[2],vals[3],vals[4],vals[5]));
    }
    vector<string> blockedwords = {"ONLINE STORE" , "ECOMMERCE",  "RETAIL" , "SHOP", "GENERAL MERCHANDISE"};
    BusinessDataParser bdp(csvstring,blockedwords);
    bdp.validate_businesses(arr);
}
int main(){
    testmethod1();
    return 0;
}

// lines of , seperated values 
// skip first line
// parse each next line 