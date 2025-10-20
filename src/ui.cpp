#include "ui.h"

void input_val(string &val, const string &message) {
    cout << message << ": ";
    getline(cin, val);
}

void output_val(const string &val, const string &message) {
    cout << message << ": " << val << "\n";
}
void output_val(const double &val, const string &message) {
    cout << message << ": " << val << "\n";
}

void output_stations(const vector<const string*> &reversed_stations) {
    cout << "Станции: ";
    for (size_t i = reversed_stations.size(); i > 0; i--) {
        cout << *reversed_stations[i - 1];
        if (i > 1)
            cout << ", ";
    }
    cout << "\n";
}
