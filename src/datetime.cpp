#include "datetime.h"

const time_t datetime_offset = 60; // 1 minute

string unix_to_datetime(const time_t &unix_time) {
    char datetime[DATETIME_SIZE];
    tm *tmp = localtime(&unix_time);
    strftime(datetime, DATETIME_SIZE, "%d %b %Y %H:%M", tmp);
    return string(datetime);
}

// https://stackoverflow.com/questions/1002542/how-to-convert-datetime-to-unix-timestamp-in-c#1002631
time_t date_to_unix(const char *timestamp) {
    struct tm tm = {};
    if (strptime(timestamp, "%d.%m.%Y", &tm) != NULL)
        return mktime(&tm);
    else
        return 0;
}

string s_to_dhm(const time_t seconds) {
    char dhm[DHM_TIME_SIZE];
    const time_t s_in_min = 60, s_in_h = 3600, s_in_day = 86400;
    time_t days, hours, minutes, seconds_cpy = seconds;

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
