
//minimax
/**
 * // This is the Master's API interface.
 * // You should not implement it, or speculate about its implementation
 * class Master {
 *   public:
 *     int guess(string word);
 * };
 */
class Solution {
public:
    void findSecretWord(vector<string>& words, Master& master) {
        for(auto i=0;i<10;i++){
            int n = words.size(), minCount = n, minDist = 6;
            string word = words[0];
            unordered_map<string,int> mm;
            for(auto j=0;j<n;j++){
                for(auto k=0;k<n;k++){
                    if(j==k)continue;
                    auto curDist = dist(words[j],words[k]);
                    if(curDist < minDist) {
                        minDist = curDist;
                        mm.clear();
                    } else if(curDist > minDist) continue;
                    mm[words[j]]++;
                }
            }
            for(auto it : mm){
                if(it.second < minCount) {
                    minCount = it.second;
                    word = it.first;
                }
            }
            auto curDist = master.guess(word);
            //cout<<word<<" "<<curDist<<endl;
            if(curDist == 6)break;
            vector<string> newList;
            for(auto it : words){
                //if(it == word)continue;
                if(dist(it,word) == curDist) newList.push_back(it);
            }
            words = newList;
        }
    }

    int dist(string str1, string str2){
        int ans = 0;
        for(auto i=0;i<6;i++) ans += (str1[i] == str2[i]);
        return ans;
    }
};

// approach2 : random pick
/**
 * // This is the Master's API interface.
 * // You should not implement it, or speculate about its implementation
 * class Master {
 *   public:
 *     int guess(string word);
 * };
 */
class Solution {
public:
    void findSecretWord(vector<string>& wordlist, Master& master) {
        for (int i = 0, x = 0; i < 10 && x < 6; ++i) {
            shuffle(wordlist);
            int n = wordlist.size();
            string word = wordlist[rand()%n];
            x = master.guess(word);
            vector<string> wordlist2;
            for (string w : wordlist)
                if (match(word, w) == x)
                    wordlist2.push_back(w);
            wordlist = wordlist2;
        }
    }

    void shuffle(vector<string>& arr){
        int n = arr.size();
        for(auto i=n-1;i;i--){
            int idx = rand()%i;
            swap(arr[i],arr[idx]);
        }
    }

    int match(string str1, string str2){
        int ans = 0;
        for(auto i=0;i<6;i++) ans += (str1[i] == str2[i]);
        return ans;
    }
};