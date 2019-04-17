//
// Created by student on 10.11.2018.
//

#ifndef PROJECT2_PASSENGER_H
#define PROJECT2_PASSENGER_H
#include <string>
using namespace std;

class Passenger{
public:
    int arrivalTime, boardingTime, luggageTimeNeeded, securityTimeNeeded;
    string id, isVip, hasLuggage;
    Passenger();
    bool operator<(Passenger &other)const;
    bool operator<(const Passenger &other)const;
};


#endif //PROJECT2_PASSENGER_H
