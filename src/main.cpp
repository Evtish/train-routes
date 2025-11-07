#include <iostream>
#include <vector>

#include "ticket.h"
#include "datetime.h"
#include "ui.h"
#include "database.h"
#include "encoding.h"

using namespace std;

int main(void) {
    setlocale(LC_ALL, "en_US.utf8");

    db_open("route.db", route_db);

    Ticket ticket;

    wstring w_dest_station_name;
    ui_input(w_dest_station_name, L"Куда");
    string dest_station_name = wstring_to_string(w_dest_station_name);

    char dest_station_id[DB_RES_SIZE] = "\0";
    db_get_station_id(dest_station_id, dest_station_name.c_str());
    if (dest_station_id[0] == '\0') {
        wcerr << L"Станция не найдена" << endl;
        exit(1);
    }

    char direction_name[DB_RES_SIZE];
    db_get_direction_name(direction_name, dest_station_id);
    
    vector<vector<wstring>> schedule_records;
    db_get_schedule_records(schedule_records, direction_name, dest_station_id);

    wstring w_departure_date;
    ui_input(w_departure_date, L"Дата отправления (дд.мм.гггг)");
    string departure_date = wstring_to_string(w_departure_date);
    
    // TODO: make choosing on-going, wo/ creating the departures vector
    vector<Departure> departures;
    for (vector<wstring> &rec : schedule_records) {
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

    unsigned departure_idx = ui_choose_option(departures, L"Отправление");
    ticket.departure = departures[departure_idx];

    ticket.railroad_car_type = CAR_STANDARD;
    if (ticket.departure.train_type == TRAIN_LONG_DISTANCE)
        ticket.railroad_car_type = static_cast<RailroadCarType>(ui_choose_option(ld_railroad_car_names, L"Тип пассажирского места") + 1);
    
    ticket.distance = 0;
    db_get_distance(ticket.distance, dest_station_id);

    ticket.cost = ticket.distance * rub_per_km * train_cost_ratio.at(ticket.departure.train_type) * railroad_car_cost_ratio.at(ticket.railroad_car_type);
    ticket.travel_datetime = ticket.distance / km_per_second / train_speed_ratio.at(ticket.departure.train_type);

    ui_input(ticket.passenger.full_name, L"ФИО");
    ui_input(ticket.passenger.id_card, L"Серия и номер паспорта (слитно)");

    db_get_stations(ticket.stations, direction_name, dest_station_id, to_string(ticket.departure.train_type == TRAIN_STANDARD).c_str());

    ui_print_ticket(ticket);

    sqlite3_close(route_db);

    return 0;
}
