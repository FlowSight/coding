#include<iostream>
#include<algorithm>
#include<ctime>

using namespace std;


// Build a time_t from components
time_t makeTime(int yy, int mon, int dd, int hh, int mm, int ss) {
    tm t = {};          // zero-init all fields
    t.tm_year = yy - 1900;
    t.tm_mon = mon - 1;
    t.tm_mday = dd;
    t.tm_hour = hh;
    t.tm_min = mm;
    t.tm_sec = ss;
    return mktime(&t);
}

// Get next day: just add 86400 seconds
time_t nextDay(time_t t) {
    return t + 86400;
}

// Compare: just use < > == on integers
time_t start = makeTime(2025, 4, 7, 0, 0, 0);
time_t endtime  = makeTime(2025, 4, 13, 11, 59, 59);

int main(){
    for (time_t t = start; t <= endtime; t = nextDay(t)) {
        tm* d = localtime(&t);
        cout << (d->tm_year + 1900) << "-" << (d->tm_mon + 1) << "-" << d->tm_mday << endl;
    }
    return 1;
}