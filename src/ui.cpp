#include "ui.h"

// https://stackoverflow.com/questions/5689003/how-to-implode-a-vector-of-strings-into-a-string-the-elegant-way
static string & implode(const vector<string> &elems, const string &delim, string &s) {
    for (vector<string>::const_iterator ii = elems.begin(); ii != elems.end(); ++ii)
    {
        s += (*ii);
        if (ii + 1 != elems.end())
            s += delim;
    }

    return s;
}
static string implode(const vector<string> &elems, const string &delim) {
    string s;
    return implode(elems, delim, s);
}

void delete_above_lines(unsigned n) {
    cout << "\x1B[" << n << "A\x1B[0J\r"; // moves cursor up n lines, erase from cursor until end of screen, return the carriage
}

string ui_input(const string &message) {
    string val;

    cout << message << ": ";
    getline(cin, val);
    delete_above_lines(1);

    return val;
}

unsigned ui_choose_option(const vector<string> &options, const string &message) {
    string input;
    size_t amount_of_options = options.size();

    for (size_t i = 0; i < amount_of_options; i++)
        cout << i + 1 << ". " << options[i] << "\n";
    cout << message << ": ";
    cin >> input;

    unsigned index = stoi(input) - 1;

    delete_above_lines(amount_of_options + 1);

    return index;
}
unsigned ui_choose_option(const vector<Departure> &options, const string &message) {
    string input;
    size_t amount_of_options = options.size();

    cout << "   отправление       конечная        тип поезда\n";
    for (size_t i = 0; i < amount_of_options; i++) {
        Departure dep = options[i];
        cout << i + 1 << ". " << unix_to_datetime(dep.departure_datetime) << " " << dep.term_station_name << " " << dep.train_type << "\n";
    }
    cout << message << ": ";
    cin >> input;

    unsigned index = stoi(input) - 1;

    delete_above_lines(amount_of_options + 2);

    return index;
}

void ui_print(const string &val, const string &message) {
    cout << message << ": " << val << "\n";
}
void ui_print(const double &val, const string &message) {
    cout << message << ": " << val << "\n";
}

void ui_print_stations(const vector<string> &stations) {
    cout << "Станции: ";
    for (const string &station : stations) {
        cout << "- " << station << "\n";
    }
}
