#include<bits/stdc++.h>

using namespace std;

void setdate(int year,int month, int day){
    struct tm time = {}; // important, to stop risk of uninitiated fields
    time.tm_year = year-1900;
    time.tm_mon = month-1;
    time.tm_mday = day;
    time_t date1 = mktime(&time);
    cout<<time.tm_wday<<endl;
}

void setdate5dayago(int year,int month, int day){
    setdate(year,month,day-5);
}
    

int main(){
    setdate(2026,5,25);
    setdate5dayago(2026,5,25);
    return 0;
}