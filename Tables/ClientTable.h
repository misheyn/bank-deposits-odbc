#ifndef RPBD_LAB1_CLIENTTABLE_H
#define RPBD_LAB1_CLIENTTABLE_H

#include "../Gateways/ClientGateway.h"
#include "../Models/Client.h"

class ClientTable {
public:
    explicit ClientTable(ClientGateway gateway);

    std::vector<Client> getAll();

    Client getById(int clientId);

    Client add(int addressId, std::string firstName, std::string lastName, std::string patronymic, int passportSeries,
               int passportNumber, std::string phoneNumber);

    Client update(int clientId, std::string firstName, std::string lastName, std::string patronymic, int passportSeries,
                  int passportNumber, std::string phoneNumber);

    void remove(int clientId);

private:
    ClientGateway gateway;

    Client setClient(std::vector<std::string> clientStr);

    std::vector<Client> setClients(std::vector<std::vector<std::string>> clientsStr);
};


#endif //RPBD_LAB1_CLIENTTABLE_H
