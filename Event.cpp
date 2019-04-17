//
// Created by student on 11.11.2018.
//

#include "Event.h"

bool Event::operator<(const Event& other)const {
    if(this->time != other.time){
        return this->time > other.time;
    }
    if(this->time == other.time){
        if(this->eventType != other.eventType){
            return this->eventType < other.eventType;
        }
        else{
            return this->executor.arrivalTime > other.executor.arrivalTime;
        }
    }
}

Event::Event() {
    this->time = 0;
    this->eventType = 1;
    this->executor = *new Passenger();
}

Event& Event::operator=(const Event& event){
    this->time = event.time;
    this->eventType = event.eventType;
    this->executor = event.executor;
    return *this;
}

Event::Event(Passenger passenger, int eventType, int time) {
    this->executor = passenger;
    this->eventType = eventType;
    this->time = time;
}