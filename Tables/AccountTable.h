#ifndef RPBD_LAB1_ACCOUNTTABLE_H
#define RPBD_LAB1_ACCOUNTTABLE_H

#include "../Gateways/AccountGateway.h"
#include "../Models/Account.h"

class AccountTable {
public:
    explicit AccountTable(AccountGateway gateway);

    std::vector<Account> getAll();

    Account getById(int accountId);

    std::vector<Account> getByClient(int clientId);

    std::vector<Account> getByDeposit(int depositId);

    Account add(int clientId, int depositId, std::string dateOpen, std::string dateClose, std::string amount);

    Account update(int accountId, std::string dateClose, std::string amount);

    void remove(int accountId);

private:
    AccountGateway gateway;

    Account setAccount(std::vector<std::string> accountStr);

    std::vector<Account> setAccounts(std::vector<std::vector<std::string>> accountsStr);
};


#endif //RPBD_LAB1_ACCOUNTTABLE_H
