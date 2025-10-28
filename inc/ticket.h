#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

#include "passenger.h"
#include "train.h"

using namespace std;

typedef struct {
    Passenger passenger;
    vector<const string*> stations;
    TrainSeat train_seat;
    double distance; // in km
    double cost; // in rubles
    time_t travel_time; // in seconds
} Ticket;

void ticket_input(string &str, const string &message);
void ticket_choose_option(string &key, double &val, const map_ratio &options, const string &message);
void ticket_print(const string &val, const string &message);
void ticket_print(const double &val, const string &message);
void ticket_print_stations(const vector<const string*> &reversed_stations);
