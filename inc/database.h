#pragma once

#include <sqlite3.h>
#include <cstring>
#include <cstdarg>

#include <string>
#include <vector>
#include <iostream>

#include "encoding.h"

#define DB_RES_SIZE 128

using namespace std;

extern sqlite3 *route_db;

void db_open(const char * filename, sqlite3 * &db);
void db_get_station_id(char *station_id, const char *station_name);
void db_get_direction_name(char *direction_name, const char *station_id);
void db_get_schedule_records(vector<vector<wstring>> &schedule_record, const char *direction_name, const char *station_id);
void db_get_distance(unsigned &dist, const char *station_id);
void db_get_stations(vector<wstring> &stations, const char *direction_name, const char *station_id, const char *train_type);
