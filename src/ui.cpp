#include "ui.h"

void delete_above_lines(unsigned n) {
    std::wcout << "\x1B[" << n << "A\x1B[0J\r"; // moves cursor up n lines, erase from cursor until end of screen, return the carriage
}

void ui_input(std::wstring &s, const std::wstring &message) {
    std::wcout << message << L": ";
    std::getline(std::wcin, s);
    delete_above_lines(1);
}
// void ui_input(char *s, const int &size_limit, const wstring &message) {
//     wcout << message << ": ";
//     fgets(s, size_limit, stdin);
//     delete_above_lines(1);
// }

unsigned ui_choose_option(const std::vector<std::wstring> &options, const std::wstring &message) {
    std::wstring s;
    size_t amount_of_options = options.size();

    for (size_t i = 0; i < amount_of_options; i++)
        std::wcout << i + 1 << L". " << options[i] << "\n";
    std::wcout << message << L": ";
    std::getline(std::wcin, s);

    unsigned index = stoi(s) - 1;

    delete_above_lines(amount_of_options + 1);

    return index;
}
unsigned ui_choose_option(const std::vector<Departure> &options, const std::wstring &message) {
    std::wstring s;
    size_t amount_of_options = options.size();

    std::wcout << L"   отправление       конечная          тип поезда\n";
    for (size_t i = 0; i < amount_of_options; i++) {
        Departure dep = options[i];
        std::wcout << i + 1 << L". " << unix_to_datetime(dep.departure_datetime) << L" " << dep.term_station_name << L"      " << train_name_ratio.at(dep.train_type) << "\n";
    }
    std::wcout << message << L": ";
    std::getline(std::wcin, s);

    unsigned index = stoi(s) - 1;

    delete_above_lines(amount_of_options + 2);

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
