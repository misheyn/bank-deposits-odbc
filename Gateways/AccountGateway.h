#ifndef RPBD_LAB1_ACCOUNTGATEWAY_H
#define RPBD_LAB1_ACCOUNTGATEWAY_H

#include <ctime>
#include <cstdlib>
#include "Gateway.h"

class AccountGateway : Gateway {
public:
    AccountGateway();

    explicit AccountGateway(SQLHDBC hdbc);

    std::vector<std::vector<std::string>>
    insert(int clientId, int depositId, std::string dateOpen, std::string dateClose, std::string amount);

    std::vector<std::vector<std::string>> selectAll();

    std::vector<std::vector<std::string>> selectById(int id);

    std::vector<std::vector<std::string>> selectByClient(int clientId);

    std::vector<std::vector<std::string>> selectByDeposit(int depositId);

    std::vector<std::vector<std::string>>
    update(int accountId, std::string dateClose, std::string amount);

    void remove(int accountId);

private:
    SQLHDBC hdbc;
};


#endif //RPBD_LAB1_ACCOUNTGATEWAY_H
