#include <iostream>
// #include <algorithm>
#include <codecvt>
#include <locale>
#include <vector>
#include <ctime>

#include "station.h"
#include "ticket.h"
#include "datetime.h"
#include "train.h"
#include "database.h"

using namespace std;

int main(void) {
    setlocale(LC_ALL, "");

    if (sqlite3_open("route.db", &route_db) != SQLITE_OK) {
        cerr << "Ошибка при открытии БД: " << sqlite3_errmsg(route_db) << endl;
        sqlite3_close(route_db);
        exit(1);
    }

    // char *db_errmsg = nullptr;
    // char stmt[256];
    string query_res;
    // db_exec_station_name(
    //     query_res, route_db, "Суходрев", "Суходрев",
    //     "SELECT name FROM station WHERE direction_name = (SELECT direction_name FROM station WHERE name = ?) AND id <= (SELECT id FROM station WHERE name = ?);"
    // );
    // for (auto &s : query_res)
    //     cout << s << "\n";

    Ticket ticket;
    string dest_station_name;

    ticket_input(dest_station_name, "Куда");
    const char *c_dest_station_name = dest_station_name.c_str();

    db_exec_station_name(
        query_res, route_db,
        "SELECT id\
        FROM station\
        WHERE name = ?;",
        c_dest_station_name
    );
    // sprintf(stmt, "SELECT id FROM station WHERE name = '%s';", c_dest_station_name);
    // sqlite3_exec(route_db, stmt, db_assign_to_str, &query_res, &db_errmsg);
    // db_print_error(db_errmsg);

    if (query_res.empty()) {
        cerr << "Ошибка: станция не найдена\n" << endl;
        exit(1);
    }
    
    db_exec_station_name(
        ticket.stations, route_db,
        "SELECT name\
        FROM station\
        WHERE direction_name = (\
            SELECT direction_name\
            FROM station\
            WHERE name = ?\
        ) AND\
        id <= (\
            SELECT id\
            FROM station\
            WHERE name = ?\
        )\
        ORDER BY id DESC;",
        2, c_dest_station_name, c_dest_station_name
    );
    // sprintf(
    //     stmt,
    //     "SELECT name FROM station WHERE direction_name = (SELECT direction_name FROM station WHERE name = '%s') AND id <= (SELECT id FROM station WHERE name = '%s');",
    //     c_dest_station_name, c_dest_station_name
    // );
    // cout << stmt << "\n";
    // sqlite3_exec(route_db, stmt, db_assign_to_vec, &ticket.stations, &db_errmsg);
    // db_print_error(db_errmsg);

    // sprintf(stmt, "SELECT dist_from_departure FROM station WHERE name = '%s';", c_dest_station_name);
    // sqlite3_exec(route_db, stmt, db_assign_to_str, &query_res, &db_errmsg);
    // db_print_error(db_errmsg);
    db_exec_station_name(
        query_res, route_db,
        "SELECT dist_from_departure\
        FROM station\
        WHERE name = ?;",
        c_dest_station_name
    );
    ticket.distance = stoi(query_res);
    ticket.cost = ticket.distance * rub_per_km;
    ticket.travel_time = ticket.distance / km_per_second;

    ticket_input(ticket.passenger.full_name, "ФИО");
    ticket_input(ticket.passenger.id_card, "Серия и номер паспорта (слитно)");
    ticket_choose_option(ticket.train_seat.train_type, ticket.cost, train_ratio, "Тип поезда");
    ticket_choose_option(ticket.train_seat.railroad_car_type, ticket.cost, railroad_car_ratio, "Тип пассажирского места");

    char
        departure_time[DATETIME_SIZE],
        arrival_time[DATETIME_SIZE],
        formatted_travel_time[DHM_TIME_SIZE];
    
    time_t t = time(nullptr);
    unix_to_datetime(departure_time, t);
    unix_to_datetime(arrival_time, t + ticket.travel_time);
    s_to_dhm(formatted_travel_time, ticket.travel_time);

    ticket_print(ticket.passenger.full_name, "ФИО");
    ticket_print(ticket.passenger.id_card, "Серия и номер паспорта");
    ticket_print(ticket.train_seat.train_type, "Тип поезда");
    ticket_print(ticket.train_seat.railroad_car_type, "Тип пассажирского места");
    ticket_print(ticket.distance, "Расстояние, км");
    ticket_print(ticket.cost, "Стоимость, руб");
    ticket_print(departure_time, "Время отравления");
    ticket_print(arrival_time, "Время прибытия");
    ticket_print(formatted_travel_time, "Время в пути");
    ticket_print_stations(ticket.stations);

    sqlite3_close(route_db);

    return 0;
}
