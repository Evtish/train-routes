#include "datetime.h"

void unix_to_datetime(char (&formatted_t)[DATETIME_SIZE], const time_t unix_time) {
    tm *tmp = localtime(&unix_time);
    strftime(formatted_t, DATETIME_SIZE, "%d %b %Y %H:%M", tmp);
}
