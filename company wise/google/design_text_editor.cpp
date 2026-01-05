15/12/25 ... sev2..implementation mistake
28/12/25 ... sev2..implementation mistake


class TextEditor {
public:
    vector<char> left,right;
    TextEditor() {
        
    }
    
    void addText(string text) {
        for(auto c : text) left.push_back(c);
    }
    
    int deleteText(int k) {
        int cnt = 0;
        while(k && !left.empty()){
            k--;
            left.pop_back();
            cnt++;
        }
        return cnt;
    }
    
    string cursorLeft(int k) {
        int cnt = 0;
        string ans = "";
        while(k && !left.empty()){
            k--;
            right.push_back(left.back());
            left.pop_back();
        }
        int len = left.size(), leftIdx = max(len-10,0);
        for(int i=leftIdx;i<len;i++) ans.push_back(left[i]);
        return ans;
    }
    
    string cursorRight(int k) {
        int cnt = 0;
        string ans = "";
        while(k && !right.empty()){
            k--;
            left.push_back(right.back());
            right.pop_back();
        }
        int len = left.size(), leftIdx = max(len-10,0);
        for(int i=leftIdx;i<len;i++) ans.push_back(left[i]);
        return ans;
    }
};

struct DLL {
    public:
    char c;
    DLL* prev;
    DLL* next;
    DLL(char _c){
        c = _c;
        prev = nullptr;
        next = nullptr;
    }
};

class TextEditor {
public:
    DLL* dummy;
    DLL* last;
    DLL* cursor;
    TextEditor() {
        dummy = new DLL('*');
        cursor = last = dummy;
    }
    
    void addText(string text) {
        for(auto c : text){
            auto newNode = new DLL(c);
            auto next = cursor->next;
            auto prev = cursor->prev;
            cursor->next = newNode;
            newNode->next = next;
            if(next) next->prev = newNode;
            newNode->prev = cursor;
            cursor = cursor->next;
        }
    }
    
    int deleteText(int k) {
        int ans = 0;
        for(auto i=1;i<=k;i++){
            if(cursor->c ==  '*') break;
            auto next = cursor->next;
            auto prev = cursor->prev;
            if(prev) prev->next = next;
            if(next) next->prev = prev;
            cursor = prev;
            ans++;
        }
        return ans;
    }
    
    string cursorLeft(int k) {
        for(auto i=1;i<=k;i++){
            if(cursor->c == '*')break;
            cursor = cursor->prev;
        }
        string ans = "";
        auto cur = cursor;
        for(auto i=0;i<10;i++){
            if(cur->c == '*') break;
            ans.push_back(cur->c);
            cur = cur->prev;
        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
    
    string cursorRight(int k) {
        for(auto i=1;i<=k;i++){
            if(!cursor->next) break;
            cursor = cursor->next;
        }
        string ans = "";
        auto cur = cursor;
        for(auto i=0;i<10;i++){
            if(cur->c == '*') break;
            ans.push_back(cur->c);
            cur = cur->prev;
        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
};
