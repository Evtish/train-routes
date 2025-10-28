#include <iostream>
#include <vector>
#include <ctime>

#include "station.h"
#include "ticket.h"
#include "datetime.h"
#include "train.h"

using namespace std;

int main(void) {
    setlocale(LC_ALL, "");

    Ticket ticket;
    string dest_station_name;

    ticket_input(dest_station_name, "Куда");

    if (!all_stations.count(dest_station_name)) {
        fprintf(stderr, "Ошибка: станция не найдена\n");
        exit(1);
    }

    ticket.stations = {&dest_station_name};
    for (
        const string* prev_station_name = all_stations.at(*ticket.stations.back()).prev_station_name;
        prev_station_name != nullptr;
        prev_station_name = all_stations.at(*ticket.stations.back()).prev_station_name
    ) {
        ticket.stations.push_back(prev_station_name);
    }

    ticket.distance = all_stations.at(dest_station_name).dist_from_departure,
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
    
    time_t t = time(NULL);
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

    return 0;
}
