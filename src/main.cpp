#include <iostream>
#include <vector>
#include <ctime>

#include "station.h"
#include "ticket.h"
#include "datetime.h"
#include "train.h"
#include "ui.h"
#include "database.h"

using namespace std;

int main(void) {
    setlocale(LC_ALL, "");

    db_open("route.db", route_db);

    // vector<vector<string>> tmp;
    // db_exec(
    //     tmp, route_db,
    //     "SELECT hours, minutes\
    //     FROM schedule",
    //     0
    // );
    // for (auto &hm : tmp) {
    //     time_t h = stoul(hm[0]), m = stoul(hm[1]);
    //     cout << h * 3600 + m * 60 << "\n";
    // }

    Ticket ticket;

    string departure_date = ui_input("Дата отправления (дд.мм.гггг)");
    // time_t unix_departure_date = date_to_unix(departure_date.c_str());
    // const char *c_departure_date = departure_date.c_str();

    string dest_station_name = ui_input("Куда");

    char dest_station_id[DB_RES_BUFFER_SIZE] = "\0";
    db_get_station_id(dest_station_id, dest_station_name.c_str());
    if (dest_station_id[0] == '\0') {
        cerr << "Ошибка: станция не найдена\n" << endl;
        exit(1);
    }

    char direction_name[DB_RES_BUFFER_SIZE];
    db_get_direction_name(direction_name, dest_station_id);
    
    vector<vector<string>> schedule_records;
    db_get_schedule_records(schedule_records, direction_name, dest_station_id);

    vector<Departure> departures;
    for (vector<string> &rec : schedule_records) {
        time_t departure_datetime = date_to_unix(departure_date.c_str()) + stol(rec[1]);
        if (departure_datetime - time(nullptr) >= datetime_offset) {
            departures.push_back(Departure{
                .term_station_name = rec[2],
                .departure_datetime = departure_datetime,
                .train_type = static_cast<TrainType>(stoi(rec[3])),
                .id = static_cast<unsigned>(stoi(rec[0]))
            });
        }
    }

    unsigned departure_idx = ui_choose_option(departures, "Выберите отправление");
    Departure departure = departures[departure_idx];

    
    if (departure.train_type == TRAIN_LONG_DISTANCE) {

    }
    
    ticket.distance = 0;
    db_get_distance(ticket.distance, dest_station_id);
    ticket.cost = ticket.distance * rub_per_km;
    ticket.travel_time = ticket.distance / km_per_second;

    ticket.passenger.full_name = ui_input("ФИО");
    ticket.passenger.id_card = ui_input("Серия и номер паспорта (слитно)");
    // ui_choose_option(ticket.train_seat.train_type, ticket.cost, train_ratio, "Тип поезда");
    // ui_choose_option(ticket.train_seat.railroad_car_type, ticket.cost, railroad_car_ratio, "Тип пассажирского места");

    string travel_time = s_to_dhm(ticket.travel_time), arrival_time = unix_to_datetime(time(nullptr) + ticket.travel_time);

    db_get_stations(ticket.stations, direction_name, dest_station_id);

    ui_print(ticket.passenger.full_name, "ФИО");
    ui_print(ticket.passenger.id_card, "Серия и номер паспорта");
    ui_print(ticket.train_seat.train_type, "Тип поезда");
    ui_print(ticket.train_seat.railroad_car_type, "Тип пассажирского места");
    ui_print(ticket.distance, "Расстояние, км");
    ui_print(ticket.cost, "Стоимость, руб");
    ui_print(departure_date, "Время отравления");
    ui_print(arrival_time, "Время прибытия");
    ui_print(travel_time, "Время в пути");
    ui_print_stations(ticket.stations);

    sqlite3_close(route_db);

    return 0;
}
