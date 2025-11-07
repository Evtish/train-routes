#include "ui.h"

#define ANSI_RESET      L"\x1B[0m"
#define ANSI_BLACK      L"\x1B[0;30m"
#define ANSI_RED        L"\x1B[0;31m"
#define ANSI_GREEN      L"\x1B[0;32m"
#define ANSI_YELLOW     L"\x1B[0;33m"
#define ANSI_BLUE       L"\x1B[0;34m"
#define ANSI_PURPLE     L"\x1B[0;35m"
#define ANSI_CYAN       L"\x1B[0;36m"
#define ANSI_WHITE      L"\x1B[0;37m"

void delete_above_lines(const unsigned n) {
    std::wcout << "\x1B[" << n << "A\x1B[0J\r"; // moves cursor up n lines, erase from cursor until end of screen, return the carriage
}

std::wstring ui_input(const std::wstring &message) {
    std::wstring s;
    std::wcout << message << L": ";
    std::getline(std::wcin, s);
    delete_above_lines(1);
    return s;
}

unsigned ui_choose_option(const std::vector<std::wstring> &options, const std::wstring &message) {
    std::wstring s;
    const size_t amount_of_options = options.size();

    for (size_t i = 0; i < amount_of_options; i++)
        std::wcout << i + 1 << L". " << options[i] << "\n";
    std::wcout << message << L": ";
    std::getline(std::wcin, s);

    unsigned index = stoi(s) - 1;

    delete_above_lines(amount_of_options + 1);

    return index;
}
// unsigned ui_choose_option(const std::vector<Departure> &options, const std::wstring &message) {
//     std::wstring s;
//     size_t amount_of_options = options.size();

//     std::wcout << L"   отправление       конечная          тип поезда\n";
//     for (size_t i = 0; i < amount_of_options; i++) {
//         Departure dep = options[i];
//         std::wcout << i + 1 << L". " << unix_to_datetime(dep.departure_datetime) << L" " << dep.term_station_name << L"      " << train_name_ratio.at(dep.train_type) << "\n";
//     }
//     std::wcout << message << L": ";
//     std::getline(std::wcin, s);

//     unsigned index = stoi(s) - 1;

//     delete_above_lines(amount_of_options + 2);

//     return index;
// }

unsigned ui_choose_option(const std::vector<Departure> &deps, const std::wstring &message) {
    std::wstring s;
    const size_t amount_of_deps = deps.size();

    const int col_num_w = 4;
    const int col_time_w = 16;
    const int col_station_w = 20;
    const int col_type_w = 10;

    const std::wstring top_border =
        L"+" + std::wstring(col_num_w + 2, '-') +
        L"+" + std::wstring(col_time_w + 2, '-') +
        L"+" + std::wstring(col_station_w + 2, '-') +
        L"+" + std::wstring(col_type_w + 2, '-') + L"+";

    std::wcout << ANSI_GREEN << top_border << ANSI_RESET << L"\n";

    // title
    std::wcout << ANSI_GREEN << L"| " << ANSI_YELLOW
               << std::left << std::setw(col_num_w) << L"№" << ANSI_GREEN << L" | "
               << ANSI_YELLOW << std::left << std::setw(col_time_w) << L"Отправление" << ANSI_GREEN << L" | "
               << ANSI_YELLOW << std::left << std::setw(col_station_w) << L"Конечная станция" << ANSI_GREEN << L" | "
               << ANSI_YELLOW << std::left << std::setw(col_type_w) << L"Поезд" << ANSI_GREEN << L" |"
               << ANSI_RESET << L"\n";

    std::wcout << ANSI_GREEN << top_border << ANSI_RESET << L"\n";
    
    // contain
    for (size_t i = 0; i < amount_of_deps; ++i) {
        const Departure &d = deps[i];
        std::wcout << ANSI_GREEN << L"| " << ANSI_WHITE
                   << std::setw(col_num_w) << std::left << (i + 1)
                   << ANSI_GREEN << L" | " << ANSI_WHITE
                   << std::setw(col_time_w) << std::left << unix_to_datetime(d.departure_datetime)
                   << ANSI_GREEN << L" | " << ANSI_WHITE
                   << std::setw(col_station_w) << std::left << d.term_station_name
                   << ANSI_GREEN << L" | " << ANSI_WHITE
                   << std::setw(col_type_w) << std::left << train_name_ratio.at(d.train_type)
                   << ANSI_GREEN << L" |" << ANSI_RESET << L"\n";
    }

    std::wcout << ANSI_GREEN << top_border << ANSI_RESET << L"\n";

    std::wcout << message << L": ";
    std::getline(std::wcin, s);

    unsigned index = stoi(s) - 1;

    delete_above_lines(amount_of_deps + 5);

    return index;
}

void ui_print(const std::wstring &s, const std::wstring &message) {
    std::wcout << message << L": " << s << "\n";
}
void ui_print(const double &s, const std::wstring &message) {
    std::wcout << message << L": " << s << "\n";
}

void ui_print_stations(const std::vector<std::wstring> &stations) {
    std::wcout << L"Станции:\n";
    for (const std::wstring &station : stations) {
        std::wcout << L"- " << station << "\n";
    }
}

void ui_print_ticket(const Ticket &ticket) {
    std::wstring unix_departure_datetime = unix_to_datetime(ticket.departure.departure_datetime);
    std::wstring unix_travel_datetime = s_to_dhm(ticket.travel_datetime);
    std::wstring unix_arrival_datetime = unix_to_datetime(ticket.departure.departure_datetime + ticket.travel_datetime);
    
    ui_print(ticket.passenger.full_name, L"ФИО");
    ui_print(ticket.passenger.id_card, L"Серия и номер паспорта");
    ui_print(train_name_ratio.at(ticket.departure.train_type), L"Тип поезда");
    ui_print(railroad_car_name_ratio.at(ticket.railroad_car_type), L"Тип пассажирского места");
    ui_print(ticket.distance, L"Расстояние, км");
    ui_print(ticket.cost, L"Стоимость, руб");
    ui_print(unix_departure_datetime, L"Время отравления");
    ui_print(unix_travel_datetime, L"Время в пути");
    ui_print(unix_arrival_datetime, L"Время прибытия");
    ui_print_stations(ticket.stations);
}
