#include "Address.h"

Address::Address(int id, std::string city, std::string street, int houseNumber) {
    this->id = id;
    this->city = city;
    this->street = street;
    this->houseNumber = houseNumber;
}

void Address::setCity(std::string city) {
    this->city = city;
}

void Address::setStreet(std::string street) {
    this->street = street;
}

void Address::setHouseNumber(int houseNumber) {
    this->houseNumber = houseNumber;
}

void Address::print() {
    std::cout << "Address: " + city + ", " + street + ", " + std::to_string(houseNumber) << std::endl;
}

int Address::getId() {
    return id;
}

std::string Address::getCity() {
    return city;
}

std::string Address::getStreet() {
    return street;
}

int Address::getHouseNumber() {
    return houseNumber;
}
