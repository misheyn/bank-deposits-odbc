#include "ClientTable.h"

Client ClientTable::setClient(std::vector<std::string> clientStr) {
    int clientId = atoi(clientStr[0].c_str());
    int addressId = atoi(clientStr[1].c_str());
    std::string firstName = clientStr[2];
    std::string lastName = clientStr[3];
    std::string patronymic = clientStr[4];
    int passportSeries = atoi(clientStr[5].c_str());
    int passportNumber = atoi(clientStr[6].c_str());
    std::string phoneNumber = clientStr[7];
    Client client(clientId, addressId, firstName, lastName, patronymic, passportSeries, passportNumber,
                  phoneNumber);
    return client;
}

std::vector<Client> ClientTable::setClients(std::vector<std::vector<std::string>> clientsStr) {
    std::vector<Client> clients;
    for (int i = 0; i < clientsStr.size(); i++) {
        clients.push_back(setClient(clientsStr[i]));
    }
    return clients;
}

ClientTable::ClientTable(ClientGateway gateway) {
    this->gateway = gateway;
}

std::vector<Client> ClientTable::getAll() {
    std::vector<std::vector<std::string>> result = gateway.selectAll();
    return setClients(result);
}

Client ClientTable::getById(int clientId) {
    std::vector<std::vector<std::string>> result = gateway.selectById(clientId);
    return setClient(result[0]);
}

Client ClientTable::add(int addressId, std::string firstName, std::string lastName, std::string patronymic,
                        int passportSeries, int passportNumber, std::string phoneNumber) {
    std::vector<std::vector<std::string>> result = gateway.insert(addressId, firstName, lastName, patronymic,
                                                                  passportSeries, passportNumber, phoneNumber);
    return setClient(result[0]);
}

Client ClientTable::update(int clientId, std::string firstName, std::string lastName, std::string patronymic,
                           int passportSeries, int passportNumber, std::string phoneNumber) {
    std::vector<std::vector<std::string>> result = gateway.update(clientId, firstName, lastName, patronymic,
                                                                  passportSeries, passportNumber, phoneNumber);
    return setClient(result[0]);
}

void ClientTable::remove(int clientId) {
    gateway.remove(clientId);
}



