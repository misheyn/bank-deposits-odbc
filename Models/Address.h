#ifndef RPBD_LAB1_ADDRESS_H
#define RPBD_LAB1_ADDRESS_H

#include <string>
#include <iostream>

class Address {
public:
    Address() {}

    Address(int id, std::string city, std::string street, int houseNumber);

    int getId();

    std::string getCity();

    std::string getStreet();

    int getHouseNumber();

    void print();

    void setCity(std::string city);

    void setStreet(std::string street);

    void setHouseNumber(int houseNumber);

private:
    int id;
    std::string city;
    std::string street;
    int houseNumber;
};


#endif //RPBD_LAB1_ADDRESS_H
