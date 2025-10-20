#include <iostream>
#include <vector>
#include <ctime>

#include "station.h"
#include "ui.h"
#include "datetime.h"

using namespace std;

int main(void) {
    setlocale(LC_ALL, "");

    string passenger_name, passenger_id_card, dest_station_name;
    input_val(passenger_name, "ФИО");
    input_val(passenger_id_card, "Серия и номер паспорта (слитно)");
    input_val(dest_station_name, "Куда");

    if (!stations.count(dest_station_name)) {
        fprintf(stderr, "Ошибка: станция не найдена\n");
        exit(1);
    }

    vector<const string*> route_stations {&dest_station_name};
    for (
        const string* prev_station_name = stations.at(*route_stations.back()).prev_station_name;
        prev_station_name != nullptr;
        prev_station_name = stations.at(*route_stations.back()).prev_station_name
    ) {
        route_stations.push_back(prev_station_name);
    }

    const double
        total_dist = stations.at(dest_station_name).dist_from_departure,
        total_cost = total_dist * rub_per_km,
        total_time_s = total_dist / km_per_second;

    char
        departure_time[DATETIME_SIZE],
        arrival_time[DATETIME_SIZE];

    time_t t = time(NULL);
    unix_to_datetime(departure_time, t);
    unix_to_datetime(arrival_time, t + total_time_s);

    cout << "\n-------------------------\n\n";

    output_val(departure_time, "Время отправления");
    output_val(arrival_time, "Время прибытия");
    output_val(total_dist, "Расстояние, км");
    output_val(total_cost, "Стоимость, руб");
    output_val(passenger_name, "ФИО");
    output_val(passenger_id_card, "Серия и номер паспорта");

    output_stations(route_stations);

    return 0;
}
