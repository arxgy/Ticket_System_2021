//
// Created by lenovo on 2021/5/22.
//

#ifndef TRAINSTATION_TICKET_H
#define TRAINSTATION_TICKET_H
#include "String.hpp"
#include "BPT.hpp"
#include "date.hpp"
#include "Train.h"
#include "Map.hpp"
#include "Order.h"
#include <algorithm>
using namespace RA;

extern Train_System trainControl;
extern Order_System orderControl;

class Ticket{
public:
    String<21> TrainID;
    int StationNo;
    date StartDayTime{};
    date StartDay{} , EndDay{};
    int ArrivalTime{} , LeaveTime{};
    int Price{};

    Ticket() = default;
    Ticket(const String<21> &trainID , int stationNo, const date &startDayTime , const date &startDay, const date &endDay , int arrivalTime , int leaveTime , int price);
    Ticket(const Ticket &t);
    Ticket &operator=(const Ticket &t);

    bool operator==(const Ticket &rhs) const;

    bool operator!=(const Ticket &rhs) const;

    bool operator<(const Ticket &t) const;
    bool operator>(const Ticket &t) const;
    bool operator<=(const Ticket &rhs) const;
    bool operator>=(const Ticket &rhs) const;

    friend class ticket_System;
};


class ticket_System{
private:
    BPlusTree<String<40> , Ticket, 500, 300 > ticket_BPT;// pair(车站，发车日期) —— 车票

    void addTicket(const String<40> &station , const Ticket &t);
    void delTicket(const String<40> &station , const Ticket &t);

public:
    ticket_System(){
        ticket_BPT.initialize("tickets_BPT.dat" , "Ticket.dat");
    };
    void restart();
    vector<Ticket> find(const String<40> &trainID);
    void addTicket(const Train &t);
    void buyTicket(const String<21> &username , const Train &t , const String<40> &st , const String<40> &ed , const date &d , int Stationnum , int isQue , int OrderNo);
    vector<pair<Ticket , Ticket>> queryTicket(const String<40> &st , const String<40> &ed , const date &d);
    vector<pair<pair<int , int> , pair<Ticket , Ticket>>> queryTransfer(const Train &t , const String<40> &st , const String<40> &ed , const date &d , int type);
    void queryTransfer(const String<40> &st , const String<40> &ed , const date &d , int type);
    void que_BuyTicket(const String<21> &username , const Order &refund_o);

    friend class Train;
};
#endif //TRAINSTATION_TICKET_H
