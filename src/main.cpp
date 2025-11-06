#include <iostream>
#include <vector>
#include <ctime>

#include "ticket.h"
#include "datetime.h"
#include "ui.h"
#include "database.h"

using namespace std;

int main(void) {
    setlocale(LC_ALL, "");

    db_open("route.db", route_db);

    Ticket ticket;

    ui_input(ticket.passenger.full_name, "ФИО");

    string departure_date;
    ui_input(departure_date, "Дата отправления (дд.мм.гггг)");

    string dest_station_name;
    ui_input(dest_station_name, "Куда");

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
    
    // TODO: make choosing on-going, wo/ creating the departures vector
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

    unsigned departure_idx = ui_choose_option(departures, "Отправление");
    ticket.departure = departures[departure_idx];

    ticket.railroad_car_type = CAR_STANDARD;
    if (ticket.departure.train_type == TRAIN_LONG_DISTANCE)
        ticket.railroad_car_type = static_cast<RailroadCarType>(ui_choose_option(ld_railroad_car_names, "Тип пассажирского места") + 1);
    
    ticket.distance = 0;
    db_get_distance(ticket.distance, dest_station_id);

    ticket.cost = ticket.distance * rub_per_km * train_cost_ratio.at(ticket.departure.train_type) * railroad_car_cost_ratio.at(ticket.railroad_car_type);
    ticket.travel_datetime = ticket.distance / km_per_second / train_speed_ratio.at(ticket.departure.train_type);

    // TODO: fix
    cout << "Серия и номер паспорта (слитно): ";
    cin >> ticket.passenger.id_card;
    delete_above_lines(1);
    // ui_input(ticket.passenger.id_card, "Серия и номер паспорта (слитно)");

    char c_train_type[2] = { static_cast<char>(ticket.departure.train_type + '0'), '\0' };
    db_get_stations(ticket.stations, direction_name, dest_station_id, c_train_type);

    ui_print_ticket(ticket);

    sqlite3_close(route_db);

    return 0;
}
