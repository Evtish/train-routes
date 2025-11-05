#pragma once

#include <sqlite3.h>
#include <cstdarg>
#include <cstdio>
#include <string>
#include <vector>

#include "ticket.h"

using namespace std;

extern sqlite3 *route_db;

// void escape_quotes(wstring &s);
void db_exec_station_name(string &res, sqlite3 * &db, const char *query, const char *station_name);
void db_exec_station_name(vector<string> &res, sqlite3 * &db, const char *query, const int amount_of_binds, ...);
void db_exec_station_name(vector<vector<string>> &res, sqlite3 * &db, const char *query, const int amount_of_binds, ...);
// void db_print_error(const char *errmsg);
// int db_print_stmt(void *, int, char **stmt_res, char **);
// int db_assign_to_str(void *p_str, int, char **stmt_res, char **);
// int db_assign_to_vec(void *p_vec, int, char **stmt_res, char **);
