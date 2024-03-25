#ifndef RPBD_LAB1_DEPOSITGATEWAY_H
#define RPBD_LAB1_DEPOSITGATEWAY_H

#include <ctime>
#include <cstdlib>
#include "Gateway.h"

class DepositGateway : Gateway {
public:
    DepositGateway();

    explicit DepositGateway(SQLHDBC hdbc);

    std::vector<std::vector<std::string>>
    insert(std::string name, int period, float rate);

    std::vector<std::vector<std::string>> selectAll();

    std::vector<std::vector<std::string>> selectById(int id);

    std::vector<std::vector<std::string>>
    update(int depositId, std::string name, int period, float rate);

    void remove(int depositId);

private:
    SQLHDBC hdbc;
};


#endif //RPBD_LAB1_DEPOSITGATEWAY_H
