#include "DepositTable.h"

DepositTable::DepositTable(DepositGateway gateway) {
    this->gateway = gateway;
}

std::vector<Deposit> DepositTable::getAll() {
    std::vector<std::vector<std::string>> result = gateway.selectAll();
    return setDeposits(result);
}

Deposit DepositTable::getById(int depositId) {
    std::vector<std::vector<std::string>> result = gateway.selectById(depositId);
    return setDeposit(result[0]);
}

Deposit DepositTable::add(std::string name, int period, float rate) {
    std::vector<std::vector<std::string>> result = gateway.insert(name, period, rate);
    return setDeposit(result[0]);
}

Deposit DepositTable::update(int depositId, std::string name, int period, float rate) {
    std::vector<std::vector<std::string>> result = gateway.update(depositId, name, period, rate);
    return setDeposit(result[0]);
}

void DepositTable::remove(int depositId) {
    gateway.remove(depositId);
}

Deposit DepositTable::setDeposit(std::vector<std::string> depositStr) {
    int depositId = atoi(depositStr[0].c_str());
    std::string name = depositStr[1];
    int period = atoi(depositStr[2].c_str());
    float rate = atof(depositStr[3].c_str());
    Deposit deposit(depositId, name, period, rate);
    return deposit;
}

std::vector<Deposit> DepositTable::setDeposits(std::vector<std::vector<std::string>> depositsStr) {
    std::vector<Deposit> deposits;
    for (int i = 0; i < depositsStr.size(); i++) {
        deposits.push_back(setDeposit(depositsStr[i]));
    }
    return deposits;
}

