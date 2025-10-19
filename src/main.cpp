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

    const double total_dist = stations.at(dest_station_name).dist_from_departure,
        total_price = total_dist * price_per_km;

    vector<const string*> route_station_names {&dest_station_name};
    for (
        const string* prev_station_name = stations.at(*route_station_names.back()).prev_station_name;
        prev_station_name != nullptr;
        prev_station_name = stations.at(*route_station_names.back()).prev_station_name
    ) {
        route_station_names.push_back(prev_station_name);
    }

    cout << "Расстояние: " << total_dist << " км\nСтоимость: " << total_price << " р.\nСтанции: ";
    for (size_t i = route_station_names.size(); i > 0; i--) {
        cout << *route_station_names[i - 1];
        if (i > 1)
            cout << ", ";
    }
    cout << "\n";

    return 0;
}
