#pragma once

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

enum TrainType {
    TRAIN_STANDARD,
    TRAIN_EXPRESS,
    TRAIN_LONG_DISTANCE
};

enum RailroadCarType {
    CAR_STANDARD,
    CAR_PLACARD,
    CAR_COUPE,
    CAR_SLEEPER
};

struct Passenger {
    string full_name;
    string id_card;
};

struct Departure {
    string term_station_name;
    time_t departure_datetime; // unix time
    TrainType train_type;
    unsigned id;
};

struct Ticket {
    vector<string> stations;
    Passenger passenger;
    Departure departure;
    unsigned distance; // in km
    double cost; // in rubles
    time_t travel_datetime; // in seconds
    RailroadCarType railroad_car_type;
};

extern const double rub_per_km, km_per_second;

extern const vector<string> ld_railroad_car_names;

extern const unordered_map<TrainType, string> train_name_ratio;
extern const unordered_map<RailroadCarType, string> railroad_car_name_ratio;

extern const unordered_map<TrainType, double> train_speed_ratio;

extern const unordered_map<TrainType, double> train_cost_ratio;
extern const unordered_map<RailroadCarType, double> railroad_car_cost_ratio;
