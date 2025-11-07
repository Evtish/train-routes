#include "database.h"

sqlite3 *route_db;

void db_open(const char * filename, sqlite3 * &p_db) {
    if (sqlite3_open(filename, &p_db) != SQLITE_OK) {
        std::wcerr << L"Ошибка при открытии БД: " << sqlite3_errmsg(p_db) << std::endl;
        sqlite3_close(p_db);
        exit(1);
    }
}

void db_exec(char *res, sqlite3 * &db, const char *query, const char *station_name) {
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        std::wcerr << L"Ошибка подготовки запроса: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        exit(1);
    }
    sqlite3_bind_text(stmt, 1, station_name, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        memcpy(res, sqlite3_column_text(stmt, 0), DB_RES_SIZE);
    }

    sqlite3_finalize(stmt);
}
void db_exec(std::vector<std::wstring> &res, sqlite3 * &db, const char *query, const int amount_of_binds, ...) {
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        std::wcerr << L"Ошибка подготовки запроса: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        exit(1);
    }

    va_list text_bind;
    va_start(text_bind, amount_of_binds);
    for (int i = 0; i < amount_of_binds; i++)
        sqlite3_bind_text(stmt, i + 1, va_arg(text_bind, const char *), -1, SQLITE_STATIC);
    va_end(text_bind);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        res.push_back(enc_char_to_wstring(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0))));
    }

    sqlite3_finalize(stmt);
}
void db_exec(std::vector<std::vector<std::wstring>> &res, sqlite3 * &db, const char *query, const int amount_of_binds, ...) {
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        std::wcerr << L"Ошибка подготовки запроса: " << sqlite3_errmsg(db) << std::endl;
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
        res.push_back({});
        for (int i = 0; i < col_count; i++) {
            std::vector<std::wstring> &line = res.back();
            line.push_back(enc_char_to_wstring(reinterpret_cast<const char *>(sqlite3_column_text(stmt, i))));
        }
    }

    sqlite3_finalize(stmt);
}

void db_get_station_id(char *station_id, const char *station_name) {
    db_exec(
        station_id, route_db,
        "SELECT id\
        FROM station\
        WHERE name = ?;",
        station_name
    );
}

void db_get_direction_name(char *direction_name, const char *station_id) {
    db_exec(
        direction_name, route_db,
        "SELECT direction_name\
        FROM station\
        WHERE id = ?;",
        station_id
    );
}

void db_get_schedule_records(std::vector<std::vector<std::wstring>> &schedule_record, const char *direction_name, const char *station_id) {
    db_exec(
        schedule_record, route_db,
        "SELECT id, unix_time, term_station_name, train_type\
        FROM schedule\
        WHERE direction_name = ? AND term_station_id >= ? AND (train_type = 0 OR (SELECT standard_train_only FROM station WHERE id = ?) = 0);",
        3, direction_name, station_id, station_id
    );
}

void db_get_distance(unsigned &dist, const char *station_id) {
    char query_res[DB_RES_SIZE];
    db_exec(
        query_res, route_db,
        "SELECT dist_from_departure\
        FROM station\
        WHERE id = ?;",
        station_id
    );
    dist = std::stoi(query_res);
}

void db_get_stations(std::vector<std::wstring> &stations, const char *direction_name, const char *station_id, const char *train_type) {
    db_exec(
        stations, route_db,
        "SELECT name\
        FROM station\
        WHERE (direction_name = ? OR direction_name IS NULL) AND id <= ? AND (? OR standard_train_only = 0);",
        3, direction_name, station_id, train_type
    );
}
