#pragma once

#include <iostream>
#include <vector>

#include "passenger.h"
#include "train.h"

using namespace std;

typedef struct {
    Passenger passenger;
    vector<string> stations;
    TrainSeat train_seat;
    unsigned distance; // in km
    double cost; // in rubles
    time_t travel_time; // in seconds
} Ticket;

void ticket_input(string &val, const string &message);
void ticket_choose_option(unsigned &index, const vector<string> &options, const string &message);
void ticket_choose_option(unsigned &index, const vector<vector<string>> &options, const string &message);
void ticket_print(const string &val, const string &message);
void ticket_print(const double &val, const string &message);
void ticket_print_stations(const vector<string> &reversed_stations);
