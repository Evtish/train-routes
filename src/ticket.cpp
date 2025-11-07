#include "ticket.h"

const double
    rub_per_km = 4, // in rubles
    km_per_second = 16.67e-3; // 60 km/h

// long distance raiload car names
const vector<wstring> ld_railroad_car_names {
    L"плацкарт",
    L"купе",
    L"СВ"
};

const unordered_map<TrainType, wstring> train_name_ratio {
    {TRAIN_STANDARD,        L"стандарт"},
    {TRAIN_EXPRESS,         L"экспресс"},
    {TRAIN_LONG_DISTANCE,   L"дальний"}
};
const unordered_map<RailroadCarType, wstring> railroad_car_name_ratio {
    {CAR_STANDARD,  L"сидячее"},
    {CAR_PLACARD,   ld_railroad_car_names[0]},
    {CAR_COUPE,     ld_railroad_car_names[1]},
    {CAR_SLEEPER,   ld_railroad_car_names[2]}
};

const unordered_map<TrainType, double> train_speed_ratio {
    {TRAIN_STANDARD,        1.0},
    {TRAIN_EXPRESS,         1.25},
    {TRAIN_LONG_DISTANCE,   1.0}
};

const unordered_map<TrainType, double> train_cost_ratio {
    {TRAIN_STANDARD,        1.0},
    {TRAIN_EXPRESS,         1.7},
    {TRAIN_LONG_DISTANCE,   0.7}
};
const unordered_map<RailroadCarType, double> railroad_car_cost_ratio {
    {CAR_STANDARD,  1.0},
    {CAR_PLACARD,   1.0},
    {CAR_COUPE,     1.6},
    {CAR_SLEEPER,   5.2}
};
