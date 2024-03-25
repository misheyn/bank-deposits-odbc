#include "Account.h"

Account::Account(int id, int clientId, int depositId, std::string dateOpen, std::string dateClose, std::string amount) {
    this->id = id;
    this->clientId = clientId;
    this->depositId = depositId;
    this->dateOpen = dateOpen;
    this->dateClose = dateClose;
    this->amount = amount;
}

int Account::getId() {
    return id;
}

int Account::getClientId() {
    return clientId;
}

int Account::getDepositId() {
    return depositId;
}

std::string Account::getDateOpen() {
    return dateOpen;
}

std::string Account::getDateClose() {
    return dateClose;
}

std::string Account::getAmount() {
    return amount;
}

void Account::print() {
    std::cout << "Account number: " + std::to_string(id) << std::endl;
    std::cout << "Account opening date: " + dateOpen << std::endl;
    std::cout << "Account closing date: " + dateClose << std::endl;
    std::cout << "Invested amount: " + amount << std::endl;
}