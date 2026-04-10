#include<bits/stdc++.h>
using namespace std;

// Trie node
struct TrieNode {
    unordered_map<char, TrieNode*> children;
    string tag; // non-empty if this node is end of a tag key
};

void insert(TrieNode* root, const string& key, const string& tag) {
    TrieNode* cur = root;
    for (char c : key) {
        c = tolower(c);
        if (!cur->children.count(c))
            cur->children[c] = new TrieNode();
        cur = cur->children[c];
    }
    cur->tag = tag;
}

// At position i in review, find longest tag match via trie
// Returns {length_matched, tag_value} or {0, ""} if no match
// Only match at word boundary: char before i is non-alnum (or i==0)
// and char after match end is non-alnum (or end==review.size())
pair<int,string> longestMatch(TrieNode* root, const string& review, int i) {
    int bestLen = 0;
    string bestTag;
    TrieNode* cur = root;
    for (int j = i; j < (int)review.size(); j++) {
        char c = tolower(review[j]);
        if (!cur->children.count(c)) break;
        cur = cur->children[c];
        if (!cur->tag.empty()) {
            // check word boundary after match
            int after = j + 1;
            bool endOk = (after >= (int)review.size()) || !isalpha(review[after]);
            if (endOk) {
                bestLen = j - i + 1;
                bestTag = cur->tag;
            }
        }
    }
    return {bestLen, bestTag};
}

string tagReview(const string& review, const unordered_map<string,string>& tags) {
    TrieNode* root = new TrieNode();
    for (auto& [key, val] : tags)
        insert(root, key, val);

    string result;
    int n = review.size();
    int i = 0;
    while (i < n) {
        // only try matching at word-start (prev char is non-alpha or i==0)
        bool wordStart = (i == 0) || !isalpha(review[i - 1]);
        if (wordStart) {
            auto [len, tag] = longestMatch(root, review, i);
            if (len > 0) {
                result += "[" + tag + "]{" + review.substr(i, len) + "}";
                i += len;
                continue;
            }
        }
        result += review[i];
        i++;
    }
    return result;
}

int main() {
    // Test 1
    {
        string review = "I visited San Francisco for work and stayed at Airbnb.\n"
                         "I really loved the city and the home where I stayed.";
        unordered_map<string,string> tags = {
            {"airbnb", "business"},
            {"san francisco", "city"}
        };
        cout << "Test 1:\n" << tagReview(review, tags) << "\n\n";
    }
    // Test 2
    {
        string review = "I travelled to San Francisco for work and stayed at Airbnb.\n"
                         "I really loved the city and the home where I stayed.\n"
                         "I stayed with San and Francisco.\n"
                         "They both were really good and san's hospitality was outstanding.";
        unordered_map<string,string> tags = {
            {"san", "person"},
            {"francisco", "person"},
            {"san francisco", "city"},
            {"Airbnb", "business"},
            {"city", "location"}
        };
        cout << "Test 2:\n" << tagReview(review, tags) << "\n";
    }
    return 0;
}