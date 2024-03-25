#include "AccountTable.h"

AccountTable::AccountTable(AccountGateway gateway) {
    this->gateway = gateway;
}

std::vector<Account> AccountTable::getAll() {
    std::vector<std::vector<std::string>> result = gateway.selectAll();
    return setAccounts(result);
}

Account AccountTable::getById(int accountId) {
    std::vector<std::vector<std::string>> result = gateway.selectById(accountId);
    return setAccount(result[0]);
}

std::vector<Account> AccountTable::getByClient(int clientId) {
    std::vector<std::vector<std::string>> result = gateway.selectByClient(clientId);
    return setAccounts(result);
}

std::vector<Account> AccountTable::getByDeposit(int depositId) {
    std::vector<std::vector<std::string>> result = gateway.selectByDeposit(depositId);
    return setAccounts(result);
}

Account
AccountTable::add(int clientId, int depositId, std::string dateOpen, std::string dateClose, std::string amount) {
    std::vector<std::vector<std::string>> result = gateway.insert(clientId, depositId, dateOpen, dateClose, amount);
    return setAccount(result[0]);
}

Account AccountTable::update(int accountId, std::string dateClose, std::string amount) {
    std::vector<std::vector<std::string>> result = gateway.update(accountId, dateClose, amount);
    return setAccount(result[0]);
}

void AccountTable::remove(int accountId) {
    gateway.remove(accountId);
}

Account AccountTable::setAccount(std::vector<std::string> accountStr) {
    int accountId = atoi(accountStr[0].c_str());
    int clientId = atoi(accountStr[1].c_str());
    int depositId = atoi(accountStr[2].c_str());
    std::string dateOpen = accountStr[3];
    std::string dateClose = accountStr[4];
    std::string amount = accountStr[5];
    Account account(accountId, clientId, depositId, dateOpen, dateClose, amount);
    return account;
}

std::vector<Account> AccountTable::setAccounts(std::vector<std::vector<std::string>> accountsStr) {
    std::vector<Account> accounts;
    for (int i = 0; i < accountsStr.size(); i++) {
        accounts.push_back(setAccount(accountsStr[i]));
    }
    return accounts;
}
