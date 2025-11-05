#include "database.h"

sqlite3 *route_db;

// void escape_quotes(wstring &s) {
//     for (size_t i = 0; i < s.length(); i++)
//         if (s[i] == '\'') {
//             s.replace(i, 1, L"''");
//             i++;
//         }
// }

void db_exec_station_name(string &res, sqlite3 * &db, const char *query, const char *station_name) {
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Ошибка подготовки запроса: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        exit(1);
    }
    sqlite3_bind_text(stmt, 1, station_name, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        res = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
    }

    sqlite3_finalize(stmt);
}
void db_exec_station_name(vector<string> &res, sqlite3 * &db, const char *query, const int amount_of_binds, ...) {
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Ошибка подготовки запроса: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        exit(1);
    }

    va_list text_bind;
    va_start(text_bind, amount_of_binds);
    for (int i = 0; i < amount_of_binds; i++)
        sqlite3_bind_text(stmt, i + 1, va_arg(text_bind, const char *), -1, SQLITE_STATIC);
    va_end(text_bind);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int col_count = sqlite3_column_count(stmt);
        for (int i = 0; i < col_count; i++)
            res.push_back(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)));
    }

    sqlite3_finalize(stmt);
}

// void db_print_error(const char *errmsg) {
//     if (errmsg != nullptr) {
//         printf("%s\n", errmsg);
//         sqlite3_free((void *) errmsg);
//         errmsg = nullptr;
//     }
// }

// int db_print_stmt(void *, int, char **stmt_res, char **) {
//     printf("%s\n", *stmt_res);
//     return 0;
// }

// int db_assign_to_str(void *p_str, int, char **stmt_res, char **) {
//     *(string *) p_str = *stmt_res;
//     return 0;
// }

// int db_assign_to_vec(void *p_vec, int, char **stmt_res, char **) {
//     ((vector<string> *) p_vec)->push_back(*stmt_res);
//     return 0;
// }
