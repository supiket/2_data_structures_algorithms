//
// Created by student on 11.11.2018.
//

#ifndef PROJECT2_EVENT_H
#define PROJECT2_EVENT_H
#include "Passenger.h"


class Event {
public:
    int time;
    Passenger executor;
    int eventType;

    bool operator<(const Event &other)const;

    Event();

    Event(Passenger passenger, int eventType, int time);

    Event& operator=(const Event &event);
};
#endif //PROJECT2_EVENT_H
