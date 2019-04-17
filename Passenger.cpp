//
// Created by student on 10.11.2018.
//

#include "Passenger.h"
using namespace std;

Passenger::Passenger() {
    arrivalTime = boardingTime = luggageTimeNeeded = securityTimeNeeded = 0;
    id = isVip = hasLuggage = "";
}

bool Passenger::operator<(Passenger &other)const {
    if(this->boardingTime != other.boardingTime)
        return this->boardingTime > other.boardingTime;

    else
        return this->arrivalTime > other.arrivalTime;
}

bool Passenger::operator<(const Passenger &other)const{
    if(this->boardingTime == other.boardingTime){
        return this->arrivalTime > other.arrivalTime;
    }
    else
        return this->boardingTime > other.boardingTime;
}