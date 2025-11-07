#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "ticket.h"
#include "datetime.h"

// using namespace std;

void ui_input(std::wstring &val, const std::wstring &message);
unsigned ui_choose_option(const std::vector<std::wstring> &options, const std::wstring &message);
unsigned ui_choose_option(const std::vector<Departure> &options, const std::wstring &message);
void ui_print_ticket(const Ticket &ticket);
