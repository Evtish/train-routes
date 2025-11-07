#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

#include "ticket.h"
#include "datetime.h"

std::wstring ui_input(const std::wstring &message);
unsigned ui_choose_option(const std::vector<std::wstring> &options, const std::wstring &message);
unsigned ui_choose_option(const std::vector<Departure> &deps, const std::wstring &message);
void ui_print_ticket(const Ticket &ticket);
