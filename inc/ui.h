#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "ticket.h"
#include "datetime.h"

using namespace std;

void ui_input(string &val, const string &message);
unsigned ui_choose_option(const vector<string> &options, const string &message);
unsigned ui_choose_option(const vector<Departure> &options, const string &message);
void ui_print_ticket(const Ticket &ticket);
