#pragma once

#include <ctime>
#include <cmath>

#define DATETIME_SIZE 20

void unix_to_datetime(char (&formatted_t)[DATETIME_SIZE], const time_t unix_time);
