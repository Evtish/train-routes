#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "ticket.h"
#include "datetime.h"

using namespace std;

string ui_input(const string &message);
unsigned ui_choose_option(const vector<string> &options, const string &message);
unsigned ui_choose_option(const vector<Departure> &options, const string &message);
void ui_print(const string &val, const string &message);
void ui_print(const double &val, const string &message);
void ui_print_stations(const vector<string> &reversed_stations);
