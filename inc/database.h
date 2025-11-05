#pragma once

#include <sqlite3.h>
#include <cstdio>
#include <string>
#include <vector>

#include "ticket.h"

using namespace std;

extern sqlite3 *route_db;

// void escape_quotes(wstring &s);
void db_exec_station_name(string &res, sqlite3 * &db, const string &station_name, const char *query);
void db_exec_station_name(vector<string> &res, sqlite3 * &db, const string &station_name1, const string &station_name2, const char *query);
// void db_print_error(const char *errmsg);
int db_print_stmt(void *, int, char **stmt_res, char **);
int db_assign_to_str(void *p_str, int, char **stmt_res, char **);
int db_assign_to_vec(void *p_vec, int, char **stmt_res, char **);
