#ifndef RPBD_LAB1_CLIENT_H
#define RPBD_LAB1_CLIENT_H

#include <string>
#include "Address.h"

class Client {
public:
    Client() {}

    Client(int id, int addressId, std::string firstName, std::string lastName, std::string patronymic,
           int passportSeries,
           int passportNumber, std::string phoneNumber);

    int getId();

    int getAddressId();

    std::string getFirstName();

    std::string getLastName();

    std::string getPatronymic();

    int getPassportSeries();

    int getPassportNumber();

    std::string getPhoneNumber();

    void print();

private:
    int id;
    int addressId;
    std::string firstName;
    std::string lastName;
    std::string patronymic;
    int passportSeries;
    int passportNumber;
    std::string phoneNumber;
};


#endif //RPBD_LAB1_CLIENT_H
