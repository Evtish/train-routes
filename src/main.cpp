#include <iostream>
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
    string query_res;

    Ticket ticket;
    string dest_station_name, dest_station_id, direction_name; // TODO: -> const char *

    ticket_input(dest_station_name, "Куда");
    const char *c_dest_station_name = dest_station_name.c_str();

    db_exec_station_name(
        dest_station_id, route_db,
        "SELECT id\
        FROM station\
        WHERE name = ?;",
        c_dest_station_name
    );

    if (dest_station_id.empty()) {
        cerr << "Ошибка: станция не найдена\n" << endl;
        exit(1);
    }
    const char *c_dest_station_id = dest_station_id.c_str();

    db_exec_station_name(
        direction_name, route_db,
        "SELECT direction_name\
        FROM station\
        WHERE id = ?;",
        c_dest_station_id
    );
    const char *c_direction_name = direction_name.c_str();

    vector<vector<string>> departures;
    db_exec_station_name(
        departures, route_db,
        "SELECT hours, minutes, term_station_name, train_type\
        FROM schedule\
        WHERE direction_name = ? AND term_station_id >= ?;",
        2, c_direction_name, c_dest_station_id
    );
    unsigned departure_idx = 0;
    ticket_choose_option(departure_idx, departures, "Выберите отправление");

    db_exec_station_name(
        query_res, route_db,
        "SELECT dist_from_departure\
        FROM station\
        WHERE id = ?;",
        c_dest_station_id
    );
    ticket.distance = stoi(query_res);
    ticket.cost = ticket.distance * rub_per_km;
    ticket.travel_time = ticket.distance / km_per_second;

    ticket_input(ticket.passenger.full_name, "ФИО");
    ticket_input(ticket.passenger.id_card, "Серия и номер паспорта (слитно)");
    // ticket_choose_option(ticket.train_seat.train_type, ticket.cost, train_ratio, "Тип поезда");
    // ticket_choose_option(ticket.train_seat.railroad_car_type, ticket.cost, railroad_car_ratio, "Тип пассажирского места");

    char
        departure_time[DATETIME_SIZE],
        arrival_time[DATETIME_SIZE],
        formatted_travel_time[DHM_TIME_SIZE];
    
    time_t t = time(nullptr);
    unix_to_datetime(departure_time, t);
    unix_to_datetime(arrival_time, t + ticket.travel_time);
    s_to_dhm(formatted_travel_time, ticket.travel_time);

    db_exec_station_name(
        ticket.stations, route_db,
        "SELECT name\
        FROM station\
        WHERE direction_name = ? AND id <= ?\
        ORDER BY id DESC;",
        2, c_direction_name, c_dest_station_id
    );

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
