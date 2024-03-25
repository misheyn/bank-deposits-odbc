#ifndef RPBD_LAB1_DEPOSIT_H
#define RPBD_LAB1_DEPOSIT_H

#include <string>
#include <iostream>

class Deposit {
public:
    Deposit() {}

    Deposit(int id, std::string name, int period, float rate);

    int getId();

    std::string getName();

    int getPeriod();

    float getRate();

    void print();

private:
    int id;
    std::string name;
    int period;
    float rate;
};


#endif //RPBD_LAB1_DEPOSIT_H
