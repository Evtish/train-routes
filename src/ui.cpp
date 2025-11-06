#include "ui.h"

void delete_above_lines(unsigned n) {
    cout << "\x1B[" << n << "A\x1B[0J\r"; // moves cursor up n lines, erase from cursor until end of screen, return the carriage
}

void ui_input(string &s, const string &message) {
    cout << message << ": ";
    getline(cin, s);
    delete_above_lines(1);
}
// void ui_input(char *s, const int &size_limit, const string &message) {
//     cout << message << ": ";
//     fgets(s, size_limit, stdin);
//     delete_above_lines(1);
// }

unsigned ui_choose_option(const vector<string> &options, const string &message) {
    string s;
    size_t amount_of_options = options.size();

    for (size_t i = 0; i < amount_of_options; i++)
        cout << i + 1 << ". " << options[i] << "\n";
    cout << message << ": ";
    getline(cin, s);

    unsigned index = stoi(s) - 1;

    delete_above_lines(amount_of_options + 1);

    return index;
}
unsigned ui_choose_option(const vector<Departure> &options, const string &message) {
    string s;
    size_t amount_of_options = options.size();

    cout << "   отправление       конечная          тип поезда\n";
    for (size_t i = 0; i < amount_of_options; i++) {
        Departure dep = options[i];
        cout << i + 1 << ". " << unix_to_datetime(dep.departure_datetime) << " " << dep.term_station_name << "      " << train_name_ratio.at(dep.train_type) << "\n";
    }
    cout << message << ": ";
    getline(cin, s);

    unsigned index = stoi(s) - 1;

    delete_above_lines(amount_of_options + 2);

    return index;
}

void ui_print(const string &s, const string &message) {
    cout << message << ": " << s << "\n";
}
void ui_print(const double &s, const string &message) {
    cout << message << ": " << s << "\n";
}

void ui_print_stations(const vector<string> &stations) {
    cout << "Станции:\n";
    for (const string &station : stations) {
        cout << "- " << station << "\n";
    }
}

void ui_print_ticket(const Ticket &ticket) {
    string unix_departure_datetime = unix_to_datetime(ticket.departure.departure_datetime);
    string unix_travel_datetime = s_to_dhm(ticket.travel_datetime);
    string unix_arrival_datetime = unix_to_datetime(ticket.departure.departure_datetime + ticket.travel_datetime);
    
    ui_print(ticket.passenger.full_name, "ФИО");
    ui_print(ticket.passenger.id_card, "Серия и номер паспорта");
    ui_print(train_name_ratio.at(ticket.departure.train_type), "Тип поезда");
    ui_print(railroad_car_name_ratio.at(ticket.railroad_car_type), "Тип пассажирского места");
    ui_print(ticket.distance, "Расстояние, км");
    ui_print(ticket.cost, "Стоимость, руб");
    ui_print(unix_departure_datetime, "Время отравления");
    ui_print(unix_travel_datetime, "Время в пути");
    ui_print(unix_arrival_datetime, "Время прибытия");
    ui_print_stations(ticket.stations);
}
