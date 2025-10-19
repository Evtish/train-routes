#include <iostream>
#include <vector>

#include "station.h"

using namespace std;

int main(void) {
    setlocale(LC_ALL, "");

    string dest_station_name;
    cout << "Куда: ";
    getline(cin, dest_station_name);

    if (!stations.count(dest_station_name)) {
        fprintf(stderr, "Ошибка: станция не найдена\n");
        exit(1);
    }

    const Station &dest_station = stations.at(dest_station_name);
    const double total_dist = dest_station.dist_from_departure,
        total_price = total_dist * price_per_km;

    vector<string> route_station_names {dest_station_name};
    for (
        string prev_station_name = stations.at(route_station_names.back()).prev_station_name;
        prev_station_name != "";
        prev_station_name = stations.at(route_station_names.back()).prev_station_name
    ) {
        route_station_names.push_back(prev_station_name);
    }

    cout << "Расстояние: " << total_dist << " км\nСтоимость: " << total_price << " р.\nСтанции: ";
    for (size_t i = route_station_names.size(); i > 0; i--) {
        cout << route_station_names[i - 1];
        if (i > 1)
            cout << ", ";
    }
    cout << "\n";

    return 0;
}
