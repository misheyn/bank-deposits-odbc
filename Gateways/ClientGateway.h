#ifndef RPBD_LAB1_CLIENTGATEWAY_H
#define RPBD_LAB1_CLIENTGATEWAY_H

#include <ctime>
#include <cstdlib>
#include "Gateway.h"
#include "../Models/Address.h"

class ClientGateway : Gateway {
public:
    ClientGateway();

    explicit ClientGateway(SQLHDBC hdbc);

    std::vector<std::vector<std::string>>
    insert(int addressId, std::string firstName, std::string lastName, std::string patronymic, int passportSeries,
           int passportNumber, std::string phoneNumber);

    std::vector<std::vector<std::string>> selectAll();

    std::vector<std::vector<std::string>> selectById(int id);

    std::vector<std::vector<std::string>>
    update(int clientId, std::string firstName, std::string lastName, std::string patronymic, int passportSeries,
           int passportNumber, std::string phoneNumber);

    void remove(int clientId);

private:
    SQLHDBC hdbc;
};


#endif //RPBD_LAB1_CLIENTGATEWAY_H
