#pragma once

#include <ctime>
#include <cmath>
#include <cstdio>

#include <string>

using namespace std;

#define DATETIME_SIZE 20
#define DHM_TIME_SIZE 25

extern const time_t datetime_offset;

string unix_to_datetime(const time_t &unix_time);
time_t date_to_unix(const char *timestamp);
string s_to_dhm(const time_t seconds);
