#include "datetime.h"

#define DATETIME_SIZE 32
#define DHM_TIME_SIZE 32

const time_t datetime_offset = 60; // 1 minute

string unix_to_datetime(const time_t &unix_time) {
    char datetime[DATETIME_SIZE];
    tm *tmp = localtime(&unix_time);
    strftime(datetime, DATETIME_SIZE, "%d %b %Y %H:%M", tmp);
    return string(datetime);
}

// https://stackoverflow.com/questions/1002542/how-to-convert-datetime-to-unix-timestamp-in-c#1002631
time_t date_to_unix(const char *timestamp) {
    int day, month, year;
    struct tm tm = {};
    tm.tm_isdst = -1;

    if (sscanf(timestamp, "%d.%d.%d", &day, &month, &year) != 3) {
        cerr << "Ошибка: неверный формат даты" << endl;
        exit(1);
    }

    tm.tm_mday = day;
    tm.tm_mon = month - 1;
    tm.tm_year = year - 1900;

    return mktime(&tm);
}

// seconds to days, hours and minutes
string s_to_dhm(const time_t seconds) {
    char dhm[DHM_TIME_SIZE];
    const time_t s_in_min = 60, s_in_h = 3600, s_in_day = 86400;
    time_t days, hours, minutes, seconds_cpy = seconds;

    // TODO: fix 1 minute offset
    days = seconds_cpy / s_in_day, seconds_cpy %= s_in_day;
    hours = seconds_cpy / s_in_h, seconds_cpy %= s_in_h;
    minutes = round((double) seconds_cpy / s_in_min);
    
    if (minutes == 60)
        hours++, minutes = 0;
    if (hours == 60)
        days++, hours = 0;
    
    sprintf(dhm, "%lu д %lu ч %lu мин", days, hours, minutes);
    return string(dhm);
}
