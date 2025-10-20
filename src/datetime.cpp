#include "datetime.h"

void unix_to_datetime(char (&formatted_t)[DATETIME_SIZE], const time_t unix_time) {
    tm *tmp = localtime(&unix_time);
    strftime(formatted_t, DATETIME_SIZE, "%d %b %Y %H:%M", tmp);
}

// seconds to days, hours and minutes
void s_to_dhm(char (&dhm)[DHM_TIME_SIZE], const time_t seconds) {
    time_t days, hours, minutes, seconds_cpy = seconds;

    // fix
    minutes = seconds_cpy % 60, seconds_cpy /= 60;
    hours = seconds_cpy % 3600, seconds_cpy /= 3600;
    days = seconds_cpy % 86400;
    
    if (minutes == 60)
        hours++, minutes = 0;
    if (hours == 60)
        days++, hours = 0;
    
    sprintf(dhm, "%ld дн %ld ч %ld мин", days, hours, minutes);
}
