#include "datetime.h"

#define DATETIME_SIZE 32
#define DHM_TIME_SIZE 32

const time_t datetime_offset = 60; // 1 minute

std::wstring unix_to_datetime(const time_t &unix_time) {
    char datetime[DATETIME_SIZE];
    tm *tmp = localtime(&unix_time);
    strftime(datetime, DATETIME_SIZE, "%d.%m.%Y %H:%M", tmp);
    return enc_char_to_wstring(datetime);
}

time_t date_to_unix(const char *timestamp) {
    struct tm tm = {};
    tm.tm_isdst = -1;
    #ifdef _WIN32
    int day, month, year;

    if (sscanf(timestamp, "%d.%d.%d", &day, &month, &year) != 3) {
        std::wcerr << L"Неверный формат даты" << std::endl;
        exit(1);
    }

    tm.tm_mday = day;
    tm.tm_mon = month - 1;
    tm.tm_year = year - 1900;

    return mktime(&tm);
    #else
    if (strptime(timestamp, "%d.%m.%Y", &tm) != NULL)
        return mktime(&tm);
    else {
        std::wcerr << L"Неверный формат даты" << std::endl;
        exit(1);
    }
    #endif
}

// seconds to days, hours and minutes
std::wstring s_to_dhm(const time_t seconds) {
    char dhm[DHM_TIME_SIZE];
    const time_t s_in_min = 60, s_in_h = 3600, s_in_day = 86400;
    time_t days, hours, minutes, seconds_cpy = seconds;

    days = seconds_cpy / s_in_day, seconds_cpy %= s_in_day;
    hours = seconds_cpy / s_in_h, seconds_cpy %= s_in_h;
    minutes = seconds_cpy / s_in_min;
    
    if (minutes == 60)
        hours++, minutes = 0;
    if (hours == 60)
        days++, hours = 0;
    
    #ifdef _WIN32
    const char *format = "%lld d %lld h %lld min";
    #else
    const char *format = "%lu d %lu h %lu min";
    #endif
    sprintf(dhm, format, days, hours, minutes);
    return enc_char_to_wstring(dhm);
}
