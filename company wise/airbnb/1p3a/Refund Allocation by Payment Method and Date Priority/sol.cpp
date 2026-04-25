

#include<bits/stdc++.h>
using namespace std;

// ============================================================
// DATE HANDLING CHEAT SHEET (interview-ready, no external libs)
// ============================================================
// Option 1: string compare  — works if format is "YYYY-MM-DD"
//   "2023-01-15" > "2023-01-10"  ← lexicographic = chronological
//
// Option 2: parse to tuple<int,int,int> for arithmetic
//   auto [y,m,d] = parseDate("2023-01-15");
//
// Option 3: convert to days-since-epoch for diff/add
//   int days = toDays("2023-01-15");
//   int diff = toDays(d2) - toDays(d1);
// ============================================================

// --- Parse "YYYY-MM-DD" → {year, month, day} -----------------
vector<int> parseDate(const string& s) {
    // sscanf approach — works in any C++ interview
    int y, m, d;
    vector<int> ans;
    stringstream ss(s);
    string cur = "";
    while(getline(ss,cur,'-')){
        ans.push_back(stoi(cur));
    }
    return ans;
}


int toDays(const string& s) {
    auto tmp = parseDate(s);
    struct tm t = {};       // zero-init all fields
    t.tm_year = tmp[0] - 1900;  // tm_year = years since 1900
    t.tm_mon  = tmp[1] - 1;     // tm_mon  = 0-based month
    t.tm_mday = tmp[2];
    time_t epoch = mktime(&t);           // seconds since 1970
    return (int)(epoch / 86400);         // convert to days
}

// --- Compare two date strings (returns -1, 0, 1) ---
int cmpDate(const string& a, const string& b) {
    // For "YYYY-MM-DD", lexicographic == chronological
    return a < b ? -1 : (a > b ? 1 : 0);
}

// --- Difference in days between two dates ---
int daysBetween(const string& a, const string& b) {
    return abs(toDays(b) - toDays(a));
}

// --- Add N days to a date string → new date string ---
string addDays(const string& s, int n) {
    auto tmp = parseDate(s);
    struct tm t = {};
    t.tm_year = tmp[0] - 1900;
    t.tm_mon  = tmp[1] - 1;
    t.tm_mday = tmp[2] + n;     // mktime normalizes overflow
    mktime(&t);
    string yymmdd = to_string(t.tm_year+1900) + "-" + to_string(t.tm_mon+1) + "-" + to_string(t.tm_mday);
    return yymmdd;
}

int getday (string date){
    auto tmp = parseDate(date);
    struct tm time;
    time.tm_year = tmp[0]-1900;
    time.tm_mon = tmp[1] -1;
    time.tm_mday = tmp[2];
    time_t epoch = mktime(&time);
    return epoch/86400;
}

int main() {
    // --- Test date utilities ---
    cout << "=== Date Utils ===" << endl;
    cout << "Parse: ";
    auto tmp = parseDate("2023-01-15");
    cout << tmp[0] << "/" << tmp[1] << "/" << tmp[2] << endl;

    cout << "Days between 2023-01-10 and 2023-01-15: "
         << daysBetween("2023-01-10", "2023-01-15") << endl;

    cout << "Add 45 days to 2023-01-10: "
         << addDays("2023-01-10", 45) << endl;

    cout << "Compare: " << cmpDate("2023-01-10", "2023-01-15")
         << " (expect -1)" << endl;

    return 0;
}
