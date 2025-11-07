#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "encoding.h"

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
    std::wstring full_name;
    std::wstring id_card;
};

struct Departure {
    std::wstring term_station_name;
    time_t departure_datetime; // unix time
    TrainType train_type;
    unsigned id;
};

struct Ticket {
    std::vector<std::wstring> stations;
    Passenger passenger;
    Departure departure;
    double cost; // in rubles
    unsigned distance; // in km
    time_t travel_datetime; // in seconds
    RailroadCarType railroad_car_type;
};

// extern const std::string dep_station_id;
extern const double rub_per_km, km_per_second;

extern const std::vector<std::wstring> ld_railroad_car_names;

extern const std::unordered_map<TrainType, std::wstring> train_name_ratio;
extern const std::unordered_map<RailroadCarType, std::wstring> railroad_car_name_ratio;

extern const std::unordered_map<TrainType, double> train_speed_ratio;

extern const std::unordered_map<TrainType, double> train_cost_ratio;
extern const std::unordered_map<RailroadCarType, double> railroad_car_cost_ratio;
