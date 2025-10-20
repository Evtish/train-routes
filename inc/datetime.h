#pragma once

#include <ctime>
#include <cmath>
#include <cstdio>

#define DATETIME_SIZE 20
#define DHM_TIME_SIZE 25

void unix_to_datetime(char (&formatted_t)[DATETIME_SIZE], const time_t unix_time);
void s_to_dhm(char (&dhm)[DHM_TIME_SIZE], const time_t seconds);
