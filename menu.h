#ifndef RPBD_LAB1_MENU_H
#define RPBD_LAB1_MENU_H

#include <windows.h>
#include <odbcinst.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include "./Tables/ClientTable.h"
#include "./Tables/AddressTable.h"
#include "./Tables/DepositTable.h"
#include "./Tables/AccountTable.h"
#include "./Gateways/ClientGateway.h"
#include "./Gateways/AddressGateway.h"
#include "./Gateways/DepositGateway.h"
#include "./Gateways/AccountGateway.h"

void menu(SQLHDBC hdbc);

void ignoreChars(int &status);

void clientMenu(AddressTable addressTable, ClientTable clientTable);

void depositMenu(DepositTable depositTable);

void accountMenu(AccountTable accountTable, ClientTable clientTable, DepositTable depositTable);

void getClients(ClientTable clientTable);

void getClientData(AddressTable addressTable, ClientTable clientTable);

void addClient(AddressTable addressTable, ClientTable clientTable);

void changeClientData(AddressTable addressTable, ClientTable clientTable);

void changeClientName(ClientTable clientTable, AddressTable addressTable, std::vector<Client> clients, int n);

void changeSurname(ClientTable clientTable, AddressTable addressTable, std::vector<Client> clients, int n);

void changePassportData(ClientTable clientTable, AddressTable addressTable, std::vector<Client> clients, int n);

void changePhone(ClientTable clientTable, AddressTable addressTable, std::vector<Client> clients, int n);

void changeAddress(ClientTable clientTable, AddressTable addressTable, std::vector<Client> clients, int n);

void deleteClient(ClientTable clientTable);

void getDeposits(DepositTable depositTable);

void getDepositData(DepositTable depositTable);

void addDeposit(DepositTable depositTable);

void changeDepositData(DepositTable depositTable);

void changeDepositName(DepositTable depositTable, std::vector<Deposit> deposits, int n);

void changePeriod(DepositTable depositTable, std::vector<Deposit> deposits, int n);

void changeRate(DepositTable depositTable, std::vector<Deposit> deposits, int n);

void deleteDeposit(DepositTable depositTable);

void getAccounts(AccountTable accountTable, ClientTable clientTable, DepositTable depositTable);

void getAccountData(AccountTable accountTable, ClientTable clientTable, DepositTable depositTable);

void getAccountsByClient(AccountTable accountTable, ClientTable clientTable, DepositTable depositTable);

void getAccountsByDeposit(AccountTable accountTable, ClientTable clientTable, DepositTable depositTable);

void addAccount(AccountTable accountTable, ClientTable clientTable, DepositTable depositTable);

void changeAccountData(AccountTable accountTable, ClientTable clientTable, DepositTable depositTable);

void changeCloseDate(AccountTable accountTable, ClientTable clientTable, DepositTable depositTable,
                     std::vector<Account> accounts, int n);

void changeAmount(AccountTable accountTable, ClientTable clientTable, DepositTable depositTable,
                  std::vector<Account> accounts, int n);

void deleteAccount(AccountTable accountTable, ClientTable clientTable, DepositTable depositTable);

#endif //RPBD_LAB1_MENU_H
