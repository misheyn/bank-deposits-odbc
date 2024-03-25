#include "AddressTable.h"

AddressTable::AddressTable(AddressGateway gateway) {
    this->gateway = gateway;
}

Address AddressTable::getById(int addressId) {
    std::vector<std::vector<std::string>> result = gateway.select(addressId);
    return setAddress(result[0]);
}

Address AddressTable::add(std::string city, std::string street, int houseNumber) {
    std::vector<std::vector<std::string>> result = gateway.insert(city, street, houseNumber);
    return setAddress(result[0]);
}

Address AddressTable::update(int addressId, std::string city, std::string street, int houseNumber) {
    std::vector<std::vector<std::string>> result = gateway.update(addressId, city, street, houseNumber);
    return setAddress(result[0]);
}

void AddressTable::remove(int addressId) {
    gateway.remove(addressId);
}

Address AddressTable::setAddress(std::vector<std::string> addressStr) {
    int addressId = atoi(addressStr[0].c_str());
    std::string city = addressStr[1];
    std::string street = addressStr[2];
    int houseNumber = atoi(addressStr[3].c_str());
    Address address(addressId, city, street, houseNumber);
    return address;
}

std::vector<Address> AddressTable::setAddresses(std::vector<std::vector<std::string>> addressesStr) {
    std::vector<Address> address;
    for (int i = 0; i < addressesStr.size(); i++) {
        address.push_back(setAddress(addressesStr[i]));
    }
    return address;
}



