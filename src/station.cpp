#include "station.h"

const double price_per_km = 4; // in rubles

static const string station_names[] {
    "Москва",
    "Рязань", "Мичуринск", "Город грязи и говнища", "Придача", "Воронеж",
    "Ярославль", "Кострома", "Галич", "Киров", "Пермь", "Екатеринбург"
};

const unordered_map<string, Station> stations {
    {station_names[0],  {0,    nullptr}},
    // Воронеж direction
    {station_names[1],  {480,  station_names}},
    {station_names[2],  {1200, station_names + 1}},
    {station_names[3],  {1570, station_names + 2}},
    {station_names[4],  {1950, station_names + 3}},
    {station_names[5],  {2000, station_names + 4}},
    // Екатеринбург direction
    {station_names[6],  {250,  station_names + 0}},
    {station_names[7],  {280,  station_names + 6}},
    {station_names[8],  {560,  station_names + 7}},
    {station_names[9],  {700,  station_names + 8}},
    {station_names[10], {990,  station_names + 9}},
    {station_names[11], {1520, station_names + 10}},
};
