#ifndef RPBD_LAB1_ACCOUNT_H
#define RPBD_LAB1_ACCOUNT_H

#include <ctime>
#include <string>
#include <iostream>

class Account {
public:
    Account() {}

    Account(int id, int clientId, int depositId, std::string dateOpen, std::string dateClose, std::string amount);

    int getId();

    int getClientId();

    int getDepositId();

    std::string getDateOpen();

    std::string getDateClose();

    std::string getAmount();

    void print();

private:
    int id;
    int clientId;
    int depositId;
    std::string dateOpen;
    std::string dateClose;
    std::string amount;
};


#endif //RPBD_LAB1_ACCOUNT_H
