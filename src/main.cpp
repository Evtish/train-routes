#include <iostream>
#include <vector>

#include "station.h"
#include "ui.h"

using namespace std;

int main(void) {
    setlocale(LC_ALL, "");

    string passenger_name;
    input_val(passenger_name, "ФИО");

    string passenger_id_card;
    input_val(passenger_id_card, "Номер и серия паспорта (слитно)");

    string dest_station_name;
    input_val(dest_station_name, "Куда");

    if (!stations.count(dest_station_name)) {
        fprintf(stderr, "Ошибка: станция не найдена\n");
        exit(1);
    }

    const double total_dist = stations.at(dest_station_name).dist_from_departure,
        total_cost = total_dist * price_per_km;

    vector<const string*> route_stations {&dest_station_name};
    for (
        const string* prev_station_name = stations.at(*route_stations.back()).prev_station_name;
        prev_station_name != nullptr;
        prev_station_name = stations.at(*route_stations.back()).prev_station_name
    ) {
        route_stations.push_back(prev_station_name);
    }

    output_val(total_dist, "Расстояние, км");
    output_val(total_cost, "Стоимость, руб");
    output_val(passenger_name, "ФИО");
    output_val(passenger_id_card, "Номер и серия паспорта");

    output_stations(route_stations);

    return 0;
}
