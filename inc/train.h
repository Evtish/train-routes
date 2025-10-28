#pragma once

#include <map>
#include <string>

using namespace std;

// typedef enum {
//     TRAIN_STANDARD,
//     TRAIN_EXPRESS
// } TrainType;

// typedef enum {
//     CAR_COACH,
//     CAR_PLACARD,
//     CAR_COUPE,
//     CAR_SLEEPER
// } RailroadCarType;

typedef struct {
    string train_type;
    string railroad_car_type;
} TrainSeat;

typedef map<string, double> map_ratio;

extern const map_ratio train_ratio;
extern const map_ratio railroad_car_ratio;
