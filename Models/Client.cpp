#include "Client.h"

Client::Client(int id, int addressId, std::string firstName, std::string lastName, std::string patronymic,
               int passportSeries,
               int passportNumber, std::string phoneNumber) {
    this->id = id;
    this->addressId = addressId;
    this->firstName = firstName;
    this->lastName = lastName;
    this->patronymic = patronymic;
    this->passportSeries = passportSeries;
    this->passportNumber = passportNumber;
    this->phoneNumber = phoneNumber;
}

int Client::getId() {
    return id;
}

std::string Client::getFirstName() {
    return firstName;
}

std::string Client::getLastName() {
    return lastName;
}

std::string Client::getPatronymic() {
    return patronymic;
}

int Client::getPassportSeries() {
    return passportSeries;
}

int Client::getPassportNumber() {
    return passportNumber;
}

std::string Client::getPhoneNumber() {
    return phoneNumber;
}

int Client::getAddressId() {
    return addressId;
}

void Client::print() {
    std::cout << "Fullname: " + lastName + " " + firstName + " " + patronymic << std::endl;
    std::cout
            << "Passport data (series number): " + std::to_string(passportSeries) + " " + std::to_string(passportNumber)
            << std::endl;
    std::cout << "Phone number: " + phoneNumber << std::endl;
}


