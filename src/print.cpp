// #include <iostream>

// using namespace std;

// void printTicket(const Ticket& ticket) {
//     cout << "┌─────────────────────────────────────────────────────────┐" << endl;
//     cout << "│ ЖЕЛЕЗНОДОРОЖНЫЙ БИЛЕТ │" << endl;
//     cout << "├─────────────────────────────────────────────────────────┤" << endl;
//     cout << "│ ФИО пассажира: " << left << setw(40) << ticket.fullName << "│" << endl;
//     cout << "│ Паспорт: " << setw(45) << ticket.passportNumber << "│" << endl;
//     cout << "├─────────────────────────────────────────────────────────┤" << endl;
//     cout << "│ Тип поезда: " << setw(42) << ticket.trainType << "│" << endl;
//     cout << "│ Тип места: " << setw(43) << ticket.seatType << "│" << endl;
//     cout << "│ Протяженность маршрута: " << setw(29) << to_string(ticket.distance) + " км" << "│" << endl;
//     cout << "│ Стоимость: " << setw(41) << to_string((int)ticket.price) + " руб" << "│" << endl;
//     cout << "├─────────────────────────────────────────────────────────┤" << endl;
//     cout << "│ Отправление: " << setw(40) << ticket.departureTime << "│" << endl;
//     cout << "│ Прибытие: " << setw(43) << ticket.arrivalTime << "│" << endl;
//     cout << "│ Время в пути: " << setw(39) << ticket.travelDuration << "│" << endl;
//     cout << "├─────────────────────────────────────────────────────────┤" << endl;
//     cout << "│ Станции: " << setw(45) << ticket.stations << "│" << endl;
//     cout << "└─────────────────────────────────────────────────────────┘" << endl;
// }
