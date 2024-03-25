#ifndef RPBD_LAB1_ADDRESSGATEWAY_H
#define RPBD_LAB1_ADDRESSGATEWAY_H

#include "Gateway.h"

class AddressGateway : Gateway {
public:
    AddressGateway();

    explicit AddressGateway(SQLHDBC hdbc);

    std::vector<std::vector<std::string>>
    insert(std::string city, std::string street, int houseNumber);

    std::vector<std::vector<std::string>> select(int id);

    std::vector<std::vector<std::string>> update(int id, std::string city, std::string street, int houseNumber);

    void remove(int id);

private:
    SQLHDBC hdbc;
};


#endif //RPBD_LAB1_ADDRESSGATEWAY_H
