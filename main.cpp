#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <iterator>
#include <queue>
#include "Passenger.h"
#include "Event.h"
using namespace std;

template <class Container>
void split1(const string& str, Container& cont)
{
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(cont));
}

void printIntoFile(double avgWait, int missedFlights, char* argv[]){
    ofstream myfile;
    myfile.open (argv[2], fstream::app);
    myfile << avgWait << " " << missedFlights << endl;
    myfile.close();
}


void case1(Passenger *passengers, int P, int L, int S, char* argv[]){
    priority_queue<Event> eventQ;
    for(int i = 0; i < P; i++){
        eventQ.push(*new Event(passengers[i], 1, passengers[i].arrivalTime));
    }
    queue<Passenger> luggageQ;
    queue<Passenger> securityQ;
    int globalTime = 0;
    double averageWait = 0;
    int missedFlights = 0;
    while(!eventQ.empty()){
        Event currentEvent = eventQ.top();
        eventQ.pop();
        globalTime = currentEvent.time;
        if(currentEvent.eventType == 1){
            luggageQ.push(currentEvent.executor);
            if(L > 0 && !luggageQ.empty()){
                Event e1(luggageQ.front(), 2, globalTime + luggageQ.front().luggageTimeNeeded);
                luggageQ.pop();
                eventQ.push(e1);
                L--;
            }
        }
        if(currentEvent.eventType == 2){
            L++;
            if(!luggageQ.empty()){
                Event e2(luggageQ.front(), 2, globalTime + luggageQ.front().luggageTimeNeeded);
                luggageQ.pop();
                eventQ.push(e2);
                L--;
            }
            securityQ.push(currentEvent.executor);
            if(S > 0 && !securityQ.empty()){
                Event e3(securityQ.front(), 3, globalTime + securityQ.front().securityTimeNeeded);
                securityQ.pop();
                eventQ.push(e3);
                S--;
            }
        }
        if(currentEvent.eventType == 3){
            S++;
            if(!securityQ.empty()){
                Event e4(securityQ.front(), 3, globalTime + securityQ.front().securityTimeNeeded);
                securityQ.pop();
                eventQ.push(e4);
                S--;
            }
            if(currentEvent.executor.boardingTime < globalTime){
                missedFlights++;
            }
            averageWait += globalTime - currentEvent.executor.arrivalTime;
        }
    }
    averageWait = averageWait / P;
    printIntoFile(averageWait, missedFlights, argv);
}

void case2(Passenger *passengers, int P, int L, int S, char* argv[]) {
    priority_queue<Event> eventQ;
    for(int i = 0; i < P; i++){
        eventQ.push(*new Event(passengers[i], 1, passengers[i].arrivalTime));
    }
    priority_queue<Passenger> luggageQ;
    priority_queue<Passenger> securityQ;
    int globalTime = 0;
    double averageWait = 0;
    int missedFlights = 0;
    while(!eventQ.empty()){
        Event currentEvent = eventQ.top();
        eventQ.pop();
        globalTime = currentEvent.time;
        if(currentEvent.eventType == 1){
            luggageQ.push(currentEvent.executor);
            if(L > 0 && !luggageQ.empty()){
                Passenger temp1 = luggageQ.top();
                Event e1(temp1, 2, globalTime + luggageQ.top().luggageTimeNeeded);
                luggageQ.pop();
                eventQ.push(e1);
                L--;
            }
        }
        else if(currentEvent.eventType == 2){
            L++;
            if(!luggageQ.empty()){
                Passenger temp2 = luggageQ.top();
                Event e2(temp2, 2, globalTime + luggageQ.top().luggageTimeNeeded);
                luggageQ.pop();
                eventQ.push(e2);
                L--;
            }
            securityQ.push(currentEvent.executor);
            if(S > 0 && !securityQ.empty()){
                Passenger temp3 = securityQ.top();
                Event e3(temp3, 3, globalTime + securityQ.top().securityTimeNeeded);
                securityQ.pop();
                eventQ.push(e3);
                S--;
            }
        }
        else if(currentEvent.eventType == 3){
            S++;
            if(!securityQ.empty()){
                Passenger temp4 = securityQ.top();
                Event e4(temp4, 3, globalTime + securityQ.top().securityTimeNeeded);
                securityQ.pop();
                eventQ.push(e4);
                S--;
            }
            if(currentEvent.executor.boardingTime < globalTime){
                missedFlights++;
            }
            averageWait += globalTime - currentEvent.executor.arrivalTime;
        }
    }
    averageWait = averageWait / P;
    printIntoFile(averageWait, missedFlights, argv);
}

void case3(Passenger *passengers, int P, int L, int S, char* argv[]){
    priority_queue<Event> eventQ;
    for(int i = 0; i < P; i++){
        eventQ.push(*new Event(passengers[i], 1, passengers[i].arrivalTime));
    }
    queue<Passenger> luggageQ;
    queue<Passenger> securityQ;
    int globalTime = 0;
    double averageWait = 0;
    int missedFlights = 0;
    while(!eventQ.empty()){
        Event currentEvent = eventQ.top();
        eventQ.pop();
        globalTime = currentEvent.time;
        if(currentEvent.eventType == 1){
            luggageQ.push(currentEvent.executor);
            if(L > 0 && !luggageQ.empty()){
                Event e1(luggageQ.front(), 2, globalTime + luggageQ.front().luggageTimeNeeded);
                luggageQ.pop();
                eventQ.push(e1);
                L--;
            }
        }
        else if(currentEvent.eventType == 2){
            L++;
            if(!luggageQ.empty()){
                Event e2(luggageQ.front(), 2, globalTime + luggageQ.front().luggageTimeNeeded);
                luggageQ.pop();
                eventQ.push(e2);
                L--;
            }
            if(currentEvent.executor.isVip == "N"){
                securityQ.push(currentEvent.executor);
            }
            else{
                currentEvent.eventType = 3;
            }
            if(S > 0 && !securityQ.empty()){
                Event e3(securityQ.front(), 3, globalTime + securityQ.front().securityTimeNeeded);
                securityQ.pop();
                eventQ.push(e3);
                S--;
            }
        }
        if(currentEvent.eventType == 3){
            if(currentEvent.executor.isVip == "N"){
                S++;
                if(!securityQ.empty()){
                    Event e4(securityQ.front(), 3, globalTime + securityQ.front().securityTimeNeeded);
                    securityQ.pop();
                    eventQ.push(e4);
                    S--;
                }
            }
            if(currentEvent.executor.boardingTime < globalTime){
                missedFlights++;
            }
            averageWait += globalTime - currentEvent.executor.arrivalTime;
        }
    }
    averageWait = averageWait / P;
    printIntoFile(averageWait, missedFlights, argv);
}
void case4(Passenger *passengers, int P, int L, int S, char* argv[]){
    priority_queue<Event> eventQ;
    for(int i = 0; i < P; i++){
        eventQ.push(*new Event(passengers[i], 1, passengers[i].arrivalTime));
    }
    priority_queue<Passenger> luggageQ;
    priority_queue<Passenger> securityQ;
    int globalTime = 0;
    double averageWait = 0;
    int missedFlights = 0;
    while(!eventQ.empty()){
        Event currentEvent = eventQ.top();
        eventQ.pop();
        globalTime = currentEvent.time;
        if(currentEvent.eventType == 1){
            luggageQ.push(currentEvent.executor);
            if(L > 0 && !luggageQ.empty()){
                Event e1(luggageQ.top(), 2, globalTime + luggageQ.top().luggageTimeNeeded);
                luggageQ.pop();
                eventQ.push(e1);
                L--;
            }
        }
        else if(currentEvent.eventType == 2){
            L++;
            if(!luggageQ.empty()){
                Event e2(luggageQ.top(), 2, globalTime + luggageQ.top().luggageTimeNeeded);
                luggageQ.pop();
                eventQ.push(e2);
                L--;
            }
            if(currentEvent.executor.isVip == "N"){
                securityQ.push(currentEvent.executor);
            }
            else{
                currentEvent.eventType = 3;
            }
            if(S > 0 && !securityQ.empty()){
                Event e3(securityQ.top(), 3, globalTime + securityQ.top().securityTimeNeeded);
                securityQ.pop();
                eventQ.push(e3);
                S--;
            }
        }
        if(currentEvent.eventType == 3){
            if(currentEvent.executor.isVip == "N"){
                S++;
                if(!securityQ.empty()){
                    Event e4(securityQ.top(), 3, globalTime + securityQ.top().securityTimeNeeded);
                    securityQ.pop();
                    eventQ.push(e4);
                    S--;
                }
            }
            if(currentEvent.executor.boardingTime < globalTime){
                missedFlights++;
            }
            averageWait += globalTime - currentEvent.executor.arrivalTime;
        }
    }
    averageWait = averageWait / P;
    printIntoFile(averageWait, missedFlights, argv);
}

void case5(Passenger *passengers, int P, int L, int S, char* argv[]){
    priority_queue<Event> eventQ;
    for(int i = 0; i < P; i++){
        eventQ.push(*new Event(passengers[i], 1, passengers[i].arrivalTime));
    }
    queue<Passenger> luggageQ;
    queue<Passenger> securityQ;
    int globalTime = 0;
    double averageWait = 0;
    int missedFlights = 0;
    while(!eventQ.empty()){
        Event currentEvent = eventQ.top();
        eventQ.pop();
        globalTime = currentEvent.time;
        if(currentEvent.eventType == 1){
            if(currentEvent.executor.hasLuggage == "L"){
                luggageQ.push(currentEvent.executor);
            } else{
                currentEvent.eventType = 2;
            }
            if(L > 0 && !luggageQ.empty()){
                Event e1(luggageQ.front(), 2, globalTime + luggageQ.front().luggageTimeNeeded);
                luggageQ.pop();
                eventQ.push(e1);
                L--;
            }
        }  if(currentEvent.eventType == 1){
            if(currentEvent.executor.hasLuggage == "L"){
                luggageQ.push(currentEvent.executor);
            } else{
                currentEvent.eventType = 2;
            }
            if(L > 0 && !luggageQ.empty()){
                Event e1(luggageQ.front(), 2, globalTime + luggageQ.front().luggageTimeNeeded);
                luggageQ.pop();
                eventQ.push(e1);
                L--;
            }
        }
        if(currentEvent.eventType == 2){
            if(currentEvent.executor.hasLuggage == "L"){
                L++;
                if(!luggageQ.empty()){
                    Event e2(luggageQ.front(), 2, globalTime + luggageQ.front().luggageTimeNeeded);
                    luggageQ.pop();
                    eventQ.push(e2);
                    L--;
                }
            }
            securityQ.push(currentEvent.executor);
            if(S > 0 && !securityQ.empty()){
                Event e3(securityQ.front(), 3, globalTime + securityQ.front().securityTimeNeeded);
                securityQ.pop();
                eventQ.push(e3);
                S--;
            }
        }
        if(currentEvent.eventType == 3){
            S++;
            if(!securityQ.empty()){
                Event e4(securityQ.front(), 3, globalTime + securityQ.front().securityTimeNeeded);
                securityQ.pop();
                eventQ.push(e4);
                S--;
            }
            if(currentEvent.executor.boardingTime < globalTime){
                missedFlights++;
            }
            averageWait += globalTime - currentEvent.executor.arrivalTime;
        }
    }
    averageWait = averageWait / P;
    printIntoFile(averageWait, missedFlights, argv);
}

void case6(Passenger *passengers, int P, int L, int S, char* argv[]){
    priority_queue<Event> eventQ;
    for(int i = 0; i < P; i++){
        eventQ.push(*new Event(passengers[i], 1, passengers[i].arrivalTime));
    }
    priority_queue<Passenger> luggageQ;
    priority_queue<Passenger> securityQ;
    int globalTime = 0;
    double averageWait = 0;
    int missedFlights = 0;
    while(!eventQ.empty()){
        Event currentEvent = eventQ.top();
        eventQ.pop();
        globalTime = currentEvent.time;
        if(currentEvent.eventType == 1){
            if(currentEvent.executor.hasLuggage == "L"){
                luggageQ.push(currentEvent.executor);
            } else{
                currentEvent.eventType = 2;
            }
            if(L > 0 && !luggageQ.empty()){
                Event e1(luggageQ.top(), 2, globalTime + luggageQ.top().luggageTimeNeeded);
                luggageQ.pop();
                eventQ.push(e1);
                L--;
            }
        }
        if(currentEvent.eventType == 2){
            if(currentEvent.executor.hasLuggage == "L") {
                L++;
                if (!luggageQ.empty()) {
                    Event e2(luggageQ.top(), 2, globalTime + luggageQ.top().luggageTimeNeeded);
                    luggageQ.pop();
                    eventQ.push(e2);
                    L--;
                }
            }
            securityQ.push(currentEvent.executor);
            if(S > 0 && !securityQ.empty()){
                Event e3(securityQ.top(), 3, globalTime + securityQ.top().securityTimeNeeded);
                securityQ.pop();
                eventQ.push(e3);
                S--;
            }
        }
        if(currentEvent.eventType == 3){
            S++;
            if(!securityQ.empty()){
                Event e4(securityQ.top(), 3, globalTime + securityQ.top().securityTimeNeeded);
                securityQ.pop();
                eventQ.push(e4);
                S--;
            }
            if(currentEvent.executor.boardingTime < globalTime){
                missedFlights++;
            }
            averageWait += globalTime - currentEvent.executor.arrivalTime;
        }
    }
    averageWait = averageWait / P;
    printIntoFile(averageWait, missedFlights, argv);
}

void case7(Passenger *passengers, int P, int L, int S, char* argv[]){
    priority_queue<Event> eventQ;
    for(int i = 0; i < P; i++){
        eventQ.push(*new Event(passengers[i], 1, passengers[i].arrivalTime));
    }
    queue<Passenger> luggageQ;
    queue<Passenger> securityQ;
    int globalTime = 0;
    double averageWait = 0;
    int missedFlights = 0;
    while(!eventQ.empty()){
        Event currentEvent = eventQ.top();
        eventQ.pop();
        globalTime = currentEvent.time;
        if(currentEvent.eventType == 1){
            if(currentEvent.executor.hasLuggage == "L"){
                luggageQ.push(currentEvent.executor);
            } else
                currentEvent.eventType = 2;
            if(L > 0 && !luggageQ.empty()){
                Event e1(luggageQ.front(), 2, globalTime + luggageQ.front().luggageTimeNeeded);
                luggageQ.pop();
                eventQ.push(e1);
                L--;
            }
        }
        if(currentEvent.eventType == 2){
            if(currentEvent.executor.hasLuggage == "L"){
                L++;
                if(!luggageQ.empty()){
                    Event e2(luggageQ.front(), 2, globalTime + luggageQ.front().luggageTimeNeeded);
                    luggageQ.pop();
                    eventQ.push(e2);
                    L--;
                }
            }
            if(currentEvent.executor.isVip == "N"){
                securityQ.push(currentEvent.executor);
            }
            else
                currentEvent.eventType = 3;
            if(S > 0 && !securityQ.empty()){
                Event e3(securityQ.front(), 3, globalTime + securityQ.front().securityTimeNeeded);
                securityQ.pop();
                eventQ.push(e3);
                S--;
            }
        }
        if(currentEvent.eventType == 3){
            if(currentEvent.executor.isVip == "N"){
                S++;
                if(!securityQ.empty()){
                    Event e4(securityQ.front(), 3, globalTime + securityQ.front().securityTimeNeeded);
                    securityQ.pop();
                    eventQ.push(e4);
                    S--;
                }
            }
            if(currentEvent.executor.boardingTime < globalTime){
                missedFlights++;
            }
            averageWait += globalTime - currentEvent.executor.arrivalTime;
        }
    }
    averageWait = averageWait / P;
    printIntoFile(averageWait, missedFlights, argv);
}
void case8(Passenger *passengers, int P, int L, int S, char* argv[]){
    priority_queue<Event> eventQ;
    for(int i = 0; i < P; i++){
        eventQ.push(*new Event(passengers[i], 1, passengers[i].arrivalTime));
    }
    priority_queue<Passenger> luggageQ;
    priority_queue<Passenger> securityQ;
    int globalTime = 0;
    double averageWait = 0;
    int missedFlights = 0;
    while(!eventQ.empty()){
        Event currentEvent = eventQ.top();
        eventQ.pop();
        globalTime = currentEvent.time;
        if(currentEvent.eventType == 1){
            if(currentEvent.executor.hasLuggage == "L"){
                luggageQ.push(currentEvent.executor);
            } else
                currentEvent.eventType = 2;
            if(L > 0 && !luggageQ.empty()){
                Event e1(luggageQ.top(), 2, globalTime + luggageQ.top().luggageTimeNeeded);
                luggageQ.pop();
                eventQ.push(e1);
                L--;
            }
        }
        if(currentEvent.eventType == 2){
            if(currentEvent.executor.hasLuggage == "L"){
                L++;
                if(!luggageQ.empty()){
                    Event e2(luggageQ.top(), 2, globalTime + luggageQ.top().luggageTimeNeeded);
                    luggageQ.pop();
                    eventQ.push(e2);
                    L--;
                }
            }
            if(currentEvent.executor.isVip == "N"){
                securityQ.push(currentEvent.executor);
            }
            else
                currentEvent.eventType = 3;
            if(S > 0 && !securityQ.empty()){
                Event e3(securityQ.top(), 3, globalTime + securityQ.top().securityTimeNeeded);
                securityQ.pop();
                eventQ.push(e3);
                S--;
            }
        }
        if(currentEvent.eventType == 3){
            if(currentEvent.executor.isVip == "N"){
                S++;
                if(!securityQ.empty()){
                    Event e4(securityQ.top(), 3, globalTime + securityQ.top().securityTimeNeeded);
                    securityQ.pop();
                    eventQ.push(e4);
                    S--;
                }
            }
            if(currentEvent.executor.boardingTime < globalTime){
                missedFlights++;
            }
            averageWait += globalTime - currentEvent.executor.arrivalTime;
        }
    }
    averageWait = averageWait / P;
    printIntoFile(averageWait, missedFlights, argv);
}
int main(int argc, char* argv[]) {
    if (argc != 3) {
        return 1;
    }
    ifstream infile(argv[1]);
    string line;
    getline(infile, line);
    vector<string> firstLine;
    split1(line, firstLine);

    int P = stoi(firstLine[0]);
    int L = stoi(firstLine[1]);
    int S = stoi(firstLine[2]);
    Passenger passengers[P];

    for(int i = 0; i < P; i++){
        getline(infile, line);
        vector<string> splitted;
        split1(line, splitted);
        Passenger *temp = new Passenger();
        passengers[i] = *temp;
        passengers[i].id = "passenger#" + to_string(i+1);
        passengers[i].arrivalTime = stoi(splitted[0]);
        passengers[i].boardingTime = stoi(splitted[1]);
        passengers[i].luggageTimeNeeded = stoi(splitted[2]);
        passengers[i].securityTimeNeeded = stoi(splitted[3]);
        passengers[i].isVip = splitted[4];
        passengers[i].hasLuggage = splitted[5];
    }

    ofstream myfile;
    myfile.open (argv[2]);
    myfile.close();
    case1(passengers, P, S, L, argv);
    case2(passengers, P, S, L, argv);
    case3(passengers, P, S, L, argv);
    case4(passengers, P, S, L, argv);
    case5(passengers, P, S, L, argv);
    case6(passengers, P, S, L, argv);
    case7(passengers, P, S, L, argv);
    case8(passengers, P, S, L, argv);

    return 0;
}
