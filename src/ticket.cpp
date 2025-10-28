#include "ticket.h"

void delete_above_lines(unsigned n) {
    cout << "\x1B[" << n << "A\x1B[0J\r"; // moves cursor up n lines, erase from cursor until end of screen, return the carriage
}

void ticket_input(string &val, const string &message) {
    cout << message << ": ";
    getline(cin, val);
    delete_above_lines(1);
}

void ticket_choose_option(string &key, double &val, const map_ratio &options, const string &message) {
    string input;

    for (map_ratio::const_iterator iter = options.begin(); iter != options.end(); iter++)
        cout << "- " << iter->first << "\n";
    cout << message << ": ";
    getline(cin, input);

    val *= options.at(input);
    key = input;

    delete_above_lines(options.size() + 1);
}

void ticket_print(const string &val, const string &message) {
    cout << message << ": " << val << "\n";
}
void ticket_print(const double &val, const string &message) {
    cout << message << ": " << val << "\n";
}

// in reversed order
void ticket_print_stations(const vector<const string*> &stations) {
    cout << "Станции: ";
    for (size_t i = stations.size(); i > 0; i--) {
        cout << *stations[i - 1];
        if (i > 1)
            cout << ", ";
    }
    cout << "\n";
}
