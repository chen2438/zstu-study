#include "date.h"

CDate::CDate(int dd, int mm, int yy) : df_s("ddd"), df_l("DDD") {  //初始化
    if ((mm >= 1 && mm <= 12) && (dd >= 1 && dd <= 31)) {
        m = mm;
        d = dd;
        y = yy;
    } else {
        m = 0;
        d = 0;
        y = 0;
        cout << "the date created is wrong" << endl;
    }
}

CDate::CDate() : df_s("ddd"), df_l("DDD") {  //初始化
    time_t now;
    time(&now);
    struct tm *t_now;
    t_now = localtime(&now);
    y = t_now->tm_year + 1900;
    m = t_now->tm_mon + 1;
    d = t_now->tm_mday;
}

void CDate::add_year(int n) { y += n; }

void CDate::add_month(int n) { m += n; }

void CDate::add_day(int n) { d += n; }

string CDate::format(string df) {
    char c_df[20];
    if (df == df_s) {
        // sprintf(c_df, "%d-%d-%d", y, m, d);
        snprintf(c_df, 20, "%d-%d-%d", y, m, d);
        return string(c_df);
    }
    if (df == df_l) {
        // sprintf(c_df, "%d年%d月%d日", y, m, d);
        snprintf(c_df, 20, "%d年%d月%d日", y, m, d);
        return string(c_df);
    }
    return string("");
}

int CDate::get_day() const { return d; }

int CDate::get_month() const { return m; }

int CDate::get_year() const { return y; }
