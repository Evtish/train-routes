#include "datetime.h"

void unix_to_datetime(char (&formatted_t)[DATETIME_SIZE], const time_t unix_time) {
    tm *tmp = localtime(&unix_time);
    strftime(formatted_t, DATETIME_SIZE, "%d %b %Y %H:%M", tmp);
}

// seconds to days, hours and minutes
void s_to_dhm(char (&dhm)[DHM_TIME_SIZE], const time_t seconds) {
    const time_t s_in_min = 60, s_in_h = 3600, s_in_day = 86400;
    time_t days, hours, minutes, seconds_cpy = seconds;

    days = seconds_cpy / s_in_day, seconds_cpy %= s_in_day;
    hours = seconds_cpy / s_in_h, seconds_cpy %= s_in_h;
    minutes = round((double) seconds_cpy / s_in_min);
    
    if (minutes == 60)
        hours++, minutes = 0;
    if (hours == 60)
        days++, hours = 0;
    
    sprintf(dhm, "%ld дн %ld ч %ld мин", days, hours, minutes);
}
