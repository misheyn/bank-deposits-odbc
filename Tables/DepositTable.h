#ifndef RPBD_LAB1_DEPOSITTABLE_H
#define RPBD_LAB1_DEPOSITTABLE_H

#include "../Gateways/DepositGateway.h"
#include "../Models/Deposit.h"

class DepositTable {
public:
    explicit DepositTable(DepositGateway gateway);

    std::vector<Deposit> getAll();

    Deposit getById(int depositId);

    Deposit add(std::string name, int period, float rate);

    Deposit update(int depositId, std::string name, int period, float rate);

    void remove(int depositId);

private:
    DepositGateway gateway;

    Deposit setDeposit(std::vector<std::string> depositStr);

    std::vector<Deposit> setDeposits(std::vector<std::vector<std::string>> depositsStr);
};


#endif //RPBD_LAB1_DEPOSITTABLE_H
