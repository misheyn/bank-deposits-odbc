#include "Deposit.h"

Deposit::Deposit(int id, std::string name, int period, float rate) {
    this->id = id;
    this->name = name;
    this->period = period;
    this->rate = rate;
}

int Deposit::getId() {
    return id;
}

std::string Deposit::getName() {
    return name;
}

int Deposit::getPeriod() {
    return period;
}

float Deposit::getRate() {
    return rate;
}

void Deposit::print() {
    std::cout << "Name: " + name << std::endl;
    std::cout << "Period (month): " + std::to_string(period) << std::endl;
    std::cout << "Rate, % per annum: " + std::to_string(rate) << std::endl;
}
