#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "ticket.h"
#include "datetime.h"

using namespace std;

void ui_input(wstring &val, const wstring &message);
unsigned ui_choose_option(const vector<wstring> &options, const wstring &message);
unsigned ui_choose_option(const vector<Departure> &options, const wstring &message);
void ui_print_ticket(const Ticket &ticket);
