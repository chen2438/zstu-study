#include "head.h"

#ifndef DATE_H
#define DATE_H

class CDate {
    int d, m, y;
    const string df_s;
    const string df_l;

   public:
    CDate(int dd, int mm = 1, int yy = 1999);
    CDate();
    void add_year(int n);
    void add_month(int n);
    void add_day(int n);
    string format(string df);
    int get_day() const;
    int get_month() const;
    int get_year() const;
};
#endif
