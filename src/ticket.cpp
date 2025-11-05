#include "ticket.h"

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

void ticket_input(string &val, const string &message) {
    cout << message << ": ";
    getline(cin, val);
    delete_above_lines(1);
}

void ticket_choose_option(unsigned &index, const vector<string> &options, const string &message) {
    string input;
    size_t amount_of_options = options.size();

    for (size_t i = 0; i < amount_of_options; i++)
        cout << i + 1 << ". " << options[i] << "\n";
    cout << message << ": ";
    cin >> input;

    index = stoi(input) - 1;

    delete_above_lines(amount_of_options + 1);
}
void ticket_choose_option(unsigned &index, const vector<vector<string>> &options, const string &message) {
    string input;
    size_t amount_of_options = options.size();

    for (size_t i = 0; i < amount_of_options; i++) {
        cout << i + 1 << ". " << implode(options[i], ", ") << "\n";
    }
    cout << message << ": ";
    cin >> input;

    index = stoi(input) - 1;

    delete_above_lines(amount_of_options + 1);
}

void ticket_print(const string &val, const string &message) {
    cout << message << ": " << val << "\n";
}
void ticket_print(const double &val, const string &message) {
    cout << message << ": " << val << "\n";
}

// in reversed order
void ticket_print_stations(const vector<string> &stations) {
    cout << "Станции: ";
    for (size_t i = stations.size(); i > 0; i--) {
        cout << stations[i - 1];
        if (i > 1)
            cout << ", ";
    }
    cout << "\n";
}
