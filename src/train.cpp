#include "train.h"

/*
speed:
standard - 1.0
express - 1.25
long distance - 1.0
*/

const map_ratio train_ratio {
    {"стандарт", 1.0},
    {"экспресс", 1.7},
    {"дальнего следования", 0.7}
};

const map_ratio railroad_car_ratio {
    {"плацкарт", 1.0},
    {"купе",     1.6},
    {"СВ",       5.2}
};
