#pragma once

#include <string>
#include <vector>

// #include "train.h"

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
    time_t arrival_time; // in seconds
    time_t travel_time; // in seconds
    RailroadCarType railroad_car_type;
};
