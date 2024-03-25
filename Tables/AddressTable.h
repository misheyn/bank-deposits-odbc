#ifndef RPBD_LAB1_ADDRESSTABLE_H
#define RPBD_LAB1_ADDRESSTABLE_H

#include "../Gateways/AddressGateway.h"
#include "../Models/Address.h"

class AddressTable {
public:
    explicit AddressTable(AddressGateway gateway);

    Address getById(int addressId);

    Address add(std::string city, std::string street, int houseNumber);

    Address update(int addressId, std::string city, std::string street, int houseNumber);

    void remove(int addressId);

private:
    AddressGateway gateway;

    Address setAddress(std::vector<std::string> addressStr);

    std::vector<Address> setAddresses(std::vector<std::vector<std::string>> addressesStr);
};


#endif //RPBD_LAB1_ADDRESSTABLE_H
