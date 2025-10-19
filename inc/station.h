#pragma once

#include <cstdlib>
#include <string>
#include <unordered_map>

using namespace std;

typedef struct {
    double dist_from_departure;
    const string *prev_station_name;
} Station;

extern const double price_per_km;

extern const unordered_map<string, Station> stations;
