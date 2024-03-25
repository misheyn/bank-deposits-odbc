#include "menu.h"

void menu(SQLHDBC hdbc) {

    int life = 1, ch = -1;
    auto clientTable = ClientTable(ClientGateway(hdbc));
    auto addressTable = AddressTable(AddressGateway(hdbc));
    auto depositTable = DepositTable(DepositGateway(hdbc));
    auto accountTable = AccountTable(AccountGateway(hdbc));

    while (life) {
        std::cout << "\n************************************************" << std::endl;
        std::cout << "*  " << "Choose what you want to do/get/change/delete:" << std::endl;
        std::cout << "*  " << "[0]: Exit" << std::endl;
        std::cout << "*  " << "[1]: Clients" << std::endl;
        std::cout << "*  " << "[2]: Deposits" << std::endl;
        std::cout << "*  " << "[3]: Clients accounts" << std::endl;
        std::cin >> ch;
        ignoreChars(ch);
        switch (ch) {
            case 0:
                life = 0;
                break;
            case 1:
                clientMenu(addressTable, clientTable);
                break;
            case 2:
                depositMenu(depositTable);
                break;
            case 3:
                accountMenu(accountTable, clientTable, depositTable);
                break;
            default:
                std::cerr << "! Error. There is no such option. ";
                std::cerr << "Please enter a number between 0 and 3 !\n\n";
                break;
        }
    }
}


void ignoreChars(int &status) {
    if (std::cin.fail()) status = -1;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void clientMenu(AddressTable addressTable, ClientTable clientTable) {
    int life = 1, ch = -1;
    while (life) {
        std::cout << "\n************************************************" << std::endl;
        std::cout << "*  " << "Choose what you want to do:" << std::endl;
        std::cout << "*  " << "[0]: Exit" << std::endl;
        std::cout << "*  " << "[1]: Get list of clients" << std::endl;
        std::cout << "*  " << "[2]: Get information about client" << std::endl;
        std::cout << "*  " << "[3]: Add new client" << std::endl;
        std::cout << "*  " << "[4]: Delete client" << std::endl;
        std::cout << "*  " << "[5]: Change client data" << std::endl;
        std::cin >> ch;
        ignoreChars(ch);
        switch (ch) {
            case 0:
                life = 0;
                break;
            case 1:
                getClients(clientTable);
                break;
            case 2:
                getClientData(addressTable, clientTable);
                break;
            case 3:
                addClient(addressTable, clientTable);
                break;
            case 4:
                deleteClient(clientTable);
                break;
            case 5:
                changeClientData(addressTable, clientTable);
                break;
            default:
                std::cerr << "! Error. There is no such option. ";
                std::cerr << "Please enter a number between 0 and 5 !\n\n";
                break;
        }
    }
}

void getClients(ClientTable clientTable) {
    std::vector<Client> clients = clientTable.getAll();
    for (auto it = clients.begin(); it != clients.end(); it++) {
        std::cout << std::distance(clients.begin(), it) << ". ";
        std::cout << (*it).getLastName() + " " + (*it).getFirstName() + " " + (*it).getPatronymic() << std::endl;
    }
}

void getClientData(AddressTable addressTable, ClientTable clientTable) {
    int n, f = 0;
    while (!f) {
        std::cout << "Enter the client's serial number: " << std::endl;
        std::cin >> n;
        ignoreChars(n);
        std::cout << std::endl;
        std::vector<Client> clients = clientTable.getAll();
        if (n < clients.size()) {
            Client client = clientTable.getById(clients[n].getId());
            client.print();
            Address address = addressTable.getById(clients[n].getAddressId());
            address.print();
            f = 1;
        } else {
            std::cout << std::endl;
            std::cerr << "There is no such client!" << std::endl;
        }
    }
}

void addClient(AddressTable addressTable, ClientTable clientTable) {
    std::string name, surname, patronymic, phone, city, street;
    int series, number, house;
    std::cout << "Enter name: " << std::endl;
    std::cin >> name;
    std::cout << "Enter surname: " << std::endl;
    std::cin >> surname;
    std::cout << "Enter patronymic: " << std::endl;
    std::cin >> patronymic;
    std::cout << "Enter passport series: " << std::endl;
    std::cin >> series;
    ignoreChars(series);
    std::cout << "Enter passport number: " << std::endl;
    std::cin >> number;
    ignoreChars(number);
    std::cout << "Enter phone number (format: 79xxxxxxxxx): " << std::endl;
    std::cin >> phone;
    std::cout << "Enter address (city, street and house number): " << std::endl;
    std::cin >> city >> street >> house;
    ignoreChars(house);
    std::cout << std::endl;
    try {
        Address address = addressTable.add(city, street, house);
        Client client = clientTable.add(address.getId(), name, surname, patronymic,
                                        series, number, phone);
        std::cout << "Successful addition of a client!" << std::endl << std::endl;
        client.print();
        address.print();
    } catch (const std::exception &exp) {
        std::cout << exp.what() << std::endl;
    }
}

void changeClientData(AddressTable addressTable, ClientTable clientTable) {
    int n, ch = -1;
    std::vector<Client> clients = clientTable.getAll();
    std::cout << "List of clients: " << std::endl << std::endl;
    for (auto it = clients.begin(); it != clients.end(); it++) {
        std::cout << std::distance(clients.begin(), it) << ". ";
        std::cout << (*it).getLastName() + " " + (*it).getFirstName() + " " + (*it).getPatronymic() << std::endl;
    }
    std::cout << std::endl << "Enter the client's serial number: " << std::endl;
    std::cin >> n;
    ignoreChars(n);
    if (n >= clients.size()) {
        std::cout << std::endl;
        std::cerr << "There is no such client!" << std::endl;
    } else {
        std::cout << "\n************************************************" << std::endl;
        std::cout << "*  " << "Choose what you want to change:" << std::endl;
        std::cout << "*  " << "[1]: Name" << std::endl;
        std::cout << "*  " << "[2]: Surname" << std::endl;
        std::cout << "*  " << "[3]: Passport data" << std::endl;
        std::cout << "*  " << "[4]: Phone number" << std::endl;
        std::cout << "*  " << "[5]: Address" << std::endl;
        std::cin >> ch;
        ignoreChars(ch);
        switch (ch) {
            case 1:
                changeClientName(clientTable, addressTable, clients, n);
                break;
            case 2:
                changeSurname(clientTable, addressTable, clients, n);
                break;
            case 3:
                changePassportData(clientTable, addressTable, clients, n);
                break;
            case 4:
                changePhone(clientTable, addressTable, clients, n);
                break;
            case 5:
                changeAddress(clientTable, addressTable, clients, n);
                break;
            default:
                std::cerr << "! Error. There is no such option. ";
                std::cerr << "Please enter a number between 0 and 5 !\n\n";
                break;
        }
    }
}

void changeClientName(ClientTable clientTable, AddressTable addressTable, std::vector<Client> clients, int n) {
    std::string newName;
    std::cout << "Enter new name: " << std::endl;
    std::cin >> newName;
    try {
        Client client = clientTable.update(clients[n].getId(), newName, clients[n].getLastName(),
                                           clients[n].getPatronymic(), clients[n].getPassportSeries(),
                                           clients[n].getPassportNumber(), clients[n].getPhoneNumber());
        std::cout << "Name updated successfully!" << std::endl << std::endl;
        client.print();
        Address address = addressTable.getById(clients[n].getAddressId());
        address.print();
    } catch (const std::exception &exp) {
        std::cout << exp.what() << std::endl;
    }
}

void changeSurname(ClientTable clientTable, AddressTable addressTable, std::vector<Client> clients, int n) {
    std::string newSurname;
    std::cout << "Enter new surname: " << std::endl;
    std::cin >> newSurname;
    try {
        Client client = clientTable.update(clients[n].getId(), clients[n].getFirstName(), newSurname,
                                           clients[n].getPatronymic(), clients[n].getPassportSeries(),
                                           clients[n].getPassportNumber(), clients[n].getPhoneNumber());
        std::cout << "Surname updated successfully!" << std::endl << std::endl;
        client.print();
        Address address = addressTable.getById(clients[n].getAddressId());
        address.print();
    } catch (const std::exception &exp) {
        std::cout << exp.what() << std::endl;
    }
}

void changePassportData(ClientTable clientTable, AddressTable addressTable, std::vector<Client> clients, int n) {
    int series, number;
    std::cout << "Enter new passport data (series number): " << std::endl;
    std::cin >> series;
    ignoreChars(series);
    std::cin >> number;
    ignoreChars(number);
    try {
        Client client = clientTable.update(clients[n].getId(), clients[n].getFirstName(), clients[n].getLastName(),
                                           clients[n].getPatronymic(), series,
                                           number, clients[n].getPhoneNumber());
        std::cout << "Passport data updated successfully!" << std::endl << std::endl;
        client.print();
        Address address = addressTable.getById(clients[n].getAddressId());
        address.print();
    } catch (const std::exception &exp) {
        std::cout << exp.what() << std::endl;
    }
}

void changePhone(ClientTable clientTable, AddressTable addressTable, std::vector<Client> clients, int n) {
    std::string phone;
    std::cout << "Enter new phone number (format: 79xxxxxxxxx): " << std::endl;
    std::cin >> phone;
    try {
        Client client = clientTable.update(clients[n].getId(), clients[n].getFirstName(), clients[n].getLastName(),
                                           clients[n].getPatronymic(), clients[n].getPassportSeries(),
                                           clients[n].getPassportNumber(), phone);
        std::cout << "Phone number updated successfully!" << std::endl << std::endl;
        client.print();
        Address address = addressTable.getById(clients[n].getAddressId());
        address.print();
    } catch (const std::exception &exp) {
        std::cout << exp.what() << std::endl;
    }
}

void changeAddress(ClientTable clientTable, AddressTable addressTable, std::vector<Client> clients, int n) {
    std::string city, street;
    int house;
    std::cout << "Enter new city (enter 1 if you don't need to change): " << std::endl;
    std::cin >> city;
    std::cout << "Enter new street (enter 1 if you don't need to change): " << std::endl;
    std::cin >> street;
    std::cout << "Enter new house number (enter 1 if you don't need to change): " << std::endl;
    std::cin >> house;
    try {
        Address address = addressTable.getById(clients[n].getAddressId());
        if (city == "1") city = address.getCity();
        if (street == "1") street = address.getStreet();
        if (house == 1) house = address.getHouseNumber();

        address = addressTable.update(clients[n].getAddressId(), city, street, house);
        std::cout << "Address updated successfully!" << std::endl << std::endl;
        Client client = clientTable.getById(clients[n].getId());
        client.print();
        address.print();
    } catch (const std::exception &exp) {
        std::cout << exp.what() << std::endl;
    }
}

void deleteClient(ClientTable clientTable) {
    int n, check;
    std::vector<Client> clients = clientTable.getAll();
    std::cout << "List of clients: " << std::endl << std::endl;
    for (auto it = clients.begin(); it != clients.end(); it++) {
        std::cout << std::distance(clients.begin(), it) << ". ";
        std::cout << (*it).getLastName() + " " + (*it).getFirstName() + " " + (*it).getPatronymic() << std::endl;
    }
    std::cout << std::endl << "Enter the client's serial number: " << std::endl;
    std::cin >> n;
    ignoreChars(n);
    std::cout << "Are you sure? (yes - 1/no - 0) " << std::endl;
    std::cin >> check;
    ignoreChars(check);
    if (n >= clients.size()) {
        std::cout << std::endl;
        std::cerr << "There is no such client!" << std::endl;
    } else if (check) {
        try {
            clientTable.remove(clients[n].getId());
            std::cout << "Client delete successfully!" << std::endl << std::endl;
        } catch (const std::exception &exp) {
            std::cout << exp.what() << std::endl;
        }
    }
}

void depositMenu(DepositTable depositTable) {
    int life = 1, ch = -1;
    while (life) {
        std::cout << "\n************************************************" << std::endl;
        std::cout << "*  " << "Choose what you want to do:" << std::endl;
        std::cout << "*  " << "[0]: Exit" << std::endl;
        std::cout << "*  " << "[1]: Get list of deposits" << std::endl;
        std::cout << "*  " << "[2]: Get information about deposit" << std::endl;
        std::cout << "*  " << "[3]: Add new deposit" << std::endl;
        std::cout << "*  " << "[4]: Delete deposit" << std::endl;
        std::cout << "*  " << "[5]: Change deposit data" << std::endl;
        std::cin >> ch;
        ignoreChars(ch);
        switch (ch) {
            case 0:
                life = 0;
                break;
            case 1:
                getDeposits(depositTable);
                break;
            case 2:
                getDepositData(depositTable);
                break;
            case 3:
                addDeposit(depositTable);
                break;
            case 4:
                deleteDeposit(depositTable);
                break;
            case 5:
                changeDepositData(depositTable);
                break;
            default:
                std::cerr << "! Error. There is no such option. ";
                std::cerr << "Please enter a number between 0 and 5 !\n\n";
                break;
        }
    }
}

void getDeposits(DepositTable depositTable) {
    std::vector<Deposit> deposits = depositTable.getAll();
    for (auto it = deposits.begin(); it != deposits.end(); it++) {
        std::cout << std::distance(deposits.begin(), it) << ". ";
        std::cout << (*it).getName() << std::endl;
    }
}

void getDepositData(DepositTable depositTable) {
    int n, f = 0;
    while (!f) {
        std::cout << "Enter the deposit's serial number: " << std::endl;
        std::cin >> n;
        ignoreChars(n);
        std::cout << std::endl;
        std::vector<Deposit> deposits = depositTable.getAll();
        if (n < deposits.size()) {
            Deposit deposit = depositTable.getById(deposits[n].getId());
            deposit.print();
            f = 1;
        } else {
            std::cout << std::endl;
            std::cerr << "There is no such deposit!" << std::endl;
        }
    }
}

void addDeposit(DepositTable depositTable) {
    std::string name;
    int period;
    float rate;
    std::cout << "Enter name: " << std::endl;
    std::cin >> name;
    std::cout << "Enter storage period (months): " << std::endl;
    std::cin >> period;
    ignoreChars(period);
    std::cout << "Enter rate (% per annum): " << std::endl;
    std::cin >> rate;
    std::cout << std::endl;
    try {
        Deposit deposit = depositTable.add(name, period, rate);
        std::cout << "Deposit add successfully!" << std::endl << std::endl;
        deposit.print();
    } catch (const std::exception &exp) {
        std::cout << exp.what() << std::endl;
    }
}

void changeDepositData(DepositTable depositTable) {
    int n, ch = -1;
    std::vector<Deposit> deposits = depositTable.getAll();
    std::cout << "List of deposits: " << std::endl << std::endl;
    for (auto it = deposits.begin(); it != deposits.end(); it++) {
        std::cout << std::distance(deposits.begin(), it) << ". ";
        std::cout << (*it).getName() << std::endl;
    }
    std::cout << std::endl << "Enter the deposit's serial number: " << std::endl;
    std::cin >> n;
    ignoreChars(n);
    if (n >= deposits.size()) {
        std::cout << std::endl;
        std::cerr << "There is no such deposit!" << std::endl;
    } else {
        std::cout << "\n************************************************" << std::endl;
        std::cout << "*  " << "Choose what you want to change:" << std::endl;
        std::cout << "*  " << "[1]: Name" << std::endl;
        std::cout << "*  " << "[2]: Storage period" << std::endl;
        std::cout << "*  " << "[3]: Rate" << std::endl;
        std::cin >> ch;
        ignoreChars(ch);
        switch (ch) {
            case 1:
                changeDepositName(depositTable, deposits, n);
                break;
            case 2:
                changePeriod(depositTable, deposits, n);
                break;
            case 3:
                changeRate(depositTable, deposits, n);
                break;
            default:
                std::cerr << "! Error. There is no such option. ";
                std::cerr << "Please enter a number between 0 and 3 !\n\n";
                break;
        }
    }
}

void changeDepositName(DepositTable depositTable, std::vector<Deposit> deposits, int n) {
    std::string newName;
    std::cout << "Enter new name: " << std::endl;
    std::cin >> newName;
    try {
        Deposit deposit = depositTable.update(deposits[n].getId(), newName, deposits[n].getPeriod(),
                                              deposits[n].getRate());
        std::cout << "Name updated successfully!" << std::endl << std::endl;
        deposit.print();
    } catch (const std::exception &exp) {
        std::cout << exp.what() << std::endl;
    }
}

void changePeriod(DepositTable depositTable, std::vector<Deposit> deposits, int n) {
    int newPeriod;
    std::cout << "Enter new storage period: " << std::endl;
    std::cin >> newPeriod;
    ignoreChars(newPeriod);
    try {
        Deposit deposit = depositTable.update(deposits[n].getId(), deposits[n].getName(), newPeriod,
                                              deposits[n].getRate());
        std::cout << "Storage period updated successfully!" << std::endl << std::endl;
        deposit.print();
    } catch (const std::exception &exp) {
        std::cout << exp.what() << std::endl;
    }
}

void changeRate(DepositTable depositTable, std::vector<Deposit> deposits, int n) {
    float newRate;
    std::cout << "Enter new rate: " << std::endl;
    std::cin >> newRate;
    try {
        Deposit deposit = depositTable.update(deposits[n].getId(), deposits[n].getName(), deposits[n].getPeriod(),
                                              newRate);
        std::cout << "Rate updated successfully!" << std::endl << std::endl;
        deposit.print();
    } catch (const std::exception &exp) {
        std::cout << exp.what() << std::endl;
    }
}

void deleteDeposit(DepositTable depositTable) {
    int n, check;
    std::vector<Deposit> deposits = depositTable.getAll();
    std::cout << "List of deposits: " << std::endl << std::endl;
    for (auto it = deposits.begin(); it != deposits.end(); it++) {
        std::cout << std::distance(deposits.begin(), it) << ". ";
        std::cout << (*it).getName() << std::endl;
    }
    std::cout << std::endl << "Enter the deposit's serial number: " << std::endl;
    std::cin >> n;
    ignoreChars(n);
    std::cout << "Are you sure? (yes - 1/no - 0) " << std::endl;
    std::cin >> check;
    ignoreChars(check);
    if (n >= deposits.size()) {
        std::cout << std::endl;
        std::cerr << "There is no such deposit!" << std::endl;
    } else if (check) {
        try {
            depositTable.remove(deposits[n].getId());
            std::cout << "Deposit delete successfully!" << std::endl << std::endl;
        } catch (const std::exception &exp) {
            std::cout << exp.what() << std::endl;
        }
    }
}

void accountMenu(AccountTable accountTable, ClientTable clientTable, DepositTable depositTable) {
    int life = 1, ch = -1;
    while (life) {
        std::cout << "\n************************************************" << std::endl;
        std::cout << "*  " << "Choose what you want to do:" << std::endl;
        std::cout << "*  " << "[0]: Exit" << std::endl;
        std::cout << "*  " << "[1]: Get list of client accounts" << std::endl;
        std::cout << "*  " << "[2]: Get information about client account" << std::endl;
        std::cout << "*  " << "[3]: Get list of client accounts for open deposits" << std::endl;
        std::cout << "*  " << "[4]: Get list of clients accounts for specific deposit" << std::endl;
        std::cout << "*  " << "[5]: Open a new account" << std::endl;
        std::cout << "*  " << "[6]: Delete client account" << std::endl;
        std::cout << "*  " << "[7]: Change client account" << std::endl;
        std::cin >> ch;
        ignoreChars(ch);
        switch (ch) {
            case 0:
                life = 0;
                break;
            case 1:
                getAccounts(accountTable, clientTable, depositTable);
                break;
            case 2:
                getAccountData(accountTable, clientTable, depositTable);
                break;
            case 3:
                getAccountsByClient(accountTable, clientTable, depositTable);
                break;
            case 4:
                getAccountsByDeposit(accountTable, clientTable, depositTable);
                break;
            case 5:
                addAccount(accountTable, clientTable, depositTable);
                break;
            case 6:
                deleteAccount(accountTable, clientTable, depositTable);
                break;
            case 7:
                changeAccountData(accountTable, clientTable, depositTable);
                break;
            default:
                std::cerr << "! Error. There is no such option. ";
                std::cerr << "Please enter a number between 0 and 7 !\n\n";
                break;
        }
    }
}

void getAccounts(AccountTable accountTable, ClientTable clientTable, DepositTable depositTable) {
    std::vector<Account> accounts = accountTable.getAll();
    Client client;
    Deposit deposit;
    for (auto it = accounts.begin(); it != accounts.end(); it++) {
        client = clientTable.getById((*it).getClientId());
        deposit = depositTable.getById((*it).getDepositId());
        std::cout << std::distance(accounts.begin(), it) << ". Account: " << (*it).getId() << std::endl;
        std::cout << "   Client: " << client.getLastName() << " " << client.getFirstName() << " "
                  << client.getPatronymic() << std::endl;
        std::cout << "   Deposit: " << deposit.getName() << std::endl;
    }
}

void getAccountData(AccountTable accountTable, ClientTable clientTable, DepositTable depositTable) {
    int n, f = 0;
    while (!f) {
        std::cout << "Enter the account's serial number: " << std::endl;
        std::cin >> n;
        ignoreChars(n);
        std::cout << std::endl;
        std::vector<Account> accounts = accountTable.getAll();
        if (n < accounts.size()) {
            Account account = accountTable.getById(accounts[n].getId());
            Client client = clientTable.getById(account.getClientId());
            Deposit deposit = depositTable.getById(account.getDepositId());
            account.print();
            std::cout << "Client: " << client.getLastName() + " " + client.getFirstName() + " " + client.getPatronymic()
                      << std::endl;
            std::cout << "Deposit: " << deposit.getName() << std::endl;
            f = 1;
        } else {
            std::cout << std::endl;
            std::cerr << "There is no such client account!" << std::endl;
        }
    }
}

void getAccountsByClient(AccountTable accountTable, ClientTable clientTable, DepositTable depositTable) {
    int n, f = 0;

    while (!f) {
        std::vector<Client> clients = clientTable.getAll();
        std::cout << "List of clients: " << std::endl << std::endl;
        for (auto it = clients.begin(); it != clients.end(); it++) {
            std::cout << std::distance(clients.begin(), it) << ". ";
            std::cout << (*it).getLastName() + " " + (*it).getFirstName() + " " + (*it).getPatronymic() << std::endl;
        }
        std::cout << std::endl << "Enter the client's serial number: " << std::endl;
        std::cin >> n;
        ignoreChars(n);
        if (n < clients.size()) {
            Deposit deposit;
            std::vector<Account> accounts = accountTable.getByClient(clients[n].getId());
            std::cout << "Client: "
                      << clients[n].getLastName() + " " + clients[n].getFirstName() + " " + clients[n].getPatronymic()
                      << std::endl << std::endl;
            for (auto it = accounts.begin(); it != accounts.end(); it++) {
                (*it).print();
                deposit = depositTable.getById((*it).getDepositId());
                std::cout << "Deposit: " << deposit.getName() << std::endl << std::endl;
            }
            f = 1;
        } else {
            std::cout << std::endl;
            std::cerr << "There is no such client account!" << std::endl;
        }
    }
}

void getAccountsByDeposit(AccountTable accountTable, ClientTable clientTable, DepositTable depositTable) {
    int n, f = 0;

    while (!f) {
        std::vector<Deposit> deposits = depositTable.getAll();
        std::cout << "List of deposits: " << std::endl << std::endl;
        for (auto it = deposits.begin(); it != deposits.end(); it++) {
            std::cout << std::distance(deposits.begin(), it) << ". ";
            std::cout << (*it).getName() << std::endl;
        }
        std::cout << std::endl << "Enter the deposit's serial number: " << std::endl;
        std::cin >> n;
        ignoreChars(n);
        if (n < deposits.size()) {
            Client client;
            std::vector<Account> accounts = accountTable.getByDeposit(deposits[n].getId());
            std::cout << "Deposit: " << deposits[n].getName() << std::endl << std::endl;
            for (auto it = accounts.begin(); it != accounts.end(); it++) {
                client = clientTable.getById((*it).getClientId());
                std::cout << "Client: "
                          << client.getLastName() + " " + client.getFirstName() + " " + client.getPatronymic()
                          << std::endl << std::endl;
                (*it).print();
            }
            f = 1;
        } else {
            std::cout << std::endl;
            std::cerr << "There is no such client account!" << std::endl;
        }
    }
}

void addAccount(AccountTable accountTable, ClientTable clientTable, DepositTable depositTable) {
    int n, m, f = 0;
    std::vector<Client> clients = clientTable.getAll();
    while (!f) {
        std::cout << "List of clients: " << std::endl << std::endl;
        for (auto it = clients.begin(); it != clients.end(); it++) {
            std::cout << std::distance(clients.begin(), it) << ". ";
            std::cout << (*it).getLastName() + " " + (*it).getFirstName() + " " + (*it).getPatronymic() << std::endl;
        }
        std::cout << std::endl << "Enter the client's serial number: " << std::endl;
        std::cin >> n;
        ignoreChars(n);
        if (n >= clients.size()) {
            std::cout << std::endl;
            std::cerr << "There is no such client!" << std::endl;
        } else {
            f = 1;
        }
    }
    f = 0;
    std::vector<Deposit> deposits = depositTable.getAll();
    while (!f) {
        std::cout << "List of deposits: " << std::endl << std::endl;
        for (auto it = deposits.begin(); it != deposits.end(); it++) {
            std::cout << std::distance(deposits.begin(), it) << ". ";
            std::cout << (*it).getName() << std::endl;
        }
        std::cout << std::endl << "Enter the deposit's serial number: " << std::endl;
        std::cin >> m;
        ignoreChars(m);
        if (m >= deposits.size()) {
            std::cout << std::endl;
            std::cerr << "There is no such deposit!" << std::endl;
        } else {
            f = 1;
        }
    }
    std::string openDate, closeDate, amount;
    std::cout << "Enter account opening date (format: YYYY-MM-DD): " << std::endl;
    std::cin >> openDate;
    std::cout << "Enter account closing date (format: YYYY-MM-DD): " << std::endl;
    std::cin >> closeDate;
    std::cout << "Enter the amount to invest: " << std::endl;
    std::cin >> amount;
    std::cout << std::endl;
    try {
        Account account = accountTable.add(clients[n].getId(), deposits[m].getId(), openDate, closeDate, amount);
        std::cout << "Client account add successfully!" << std::endl << std::endl;
        account.print();
        std::cout << "Client: "
                  << clients[n].getLastName() + " " + clients[n].getFirstName() + " " + clients[n].getPatronymic()
                  << std::endl;
        std::cout << "Deposit: " << deposits[m].getName() << std::endl;
    } catch (const std::exception &exp) {
        std::cout << exp.what() << std::endl;
    }
}

void changeAccountData(AccountTable accountTable, ClientTable clientTable, DepositTable depositTable) {
    int n, ch = -1;
    std::vector<Account> accounts = accountTable.getAll();
    Client client;
    Deposit deposit;
    for (auto it = accounts.begin(); it != accounts.end(); it++) {
        client = clientTable.getById((*it).getClientId());
        deposit = depositTable.getById((*it).getDepositId());
        std::cout << std::distance(accounts.begin(), it) << ". Account: " << (*it).getId() << std::endl;
        std::cout << "   Client: " << client.getLastName() << " " << client.getFirstName() << " "
                  << client.getPatronymic() << std::endl;
        std::cout << "   Deposit: " << deposit.getName() << std::endl;
    }
    std::cout << std::endl << "Enter the account's serial number: " << std::endl;
    std::cin >> n;
    ignoreChars(n);
    if (n >= accounts.size()) {
        std::cout << std::endl;
        std::cerr << "There is no such account!" << std::endl;
    } else {
        std::cout << "\n************************************************" << std::endl;
        std::cout << "*  " << "Choose what you want to change:" << std::endl;
        std::cout << "*  " << "[1]: Account closing date" << std::endl;
        std::cout << "*  " << "[2]: Invested amount" << std::endl;
        std::cin >> ch;
        ignoreChars(ch);
        switch (ch) {
            case 1:
                changeCloseDate(accountTable, clientTable, depositTable, accounts, n);
                break;
            case 2:
                changeAmount(accountTable, clientTable, depositTable, accounts, n);
                break;
            default:
                std::cerr << "! Error. There is no such option. ";
                std::cerr << "Please enter a number between 0 and 2 !\n\n";
                break;
        }
    }
}

void changeCloseDate(AccountTable accountTable, ClientTable clientTable, DepositTable depositTable,
                     std::vector<Account> accounts, int n) {
    std::string newCloseDate;
    std::cout << "Enter new account closing date (format: YYYY-MM-DD): " << std::endl;
    std::cin >> newCloseDate;
    try {
        Account account = accountTable.update(accounts[n].getId(), newCloseDate, accounts[n].getAmount());
        Client client = clientTable.getById(account.getClientId());
        Deposit deposit = depositTable.getById(account.getDepositId());
        std::cout << "Account closing date updated successfully!" << std::endl << std::endl;
        account.print();
        std::cout << "Client: " << client.getLastName() + " " + client.getFirstName() + " " + client.getPatronymic()
                  << std::endl;
        std::cout << "Deposit: " << deposit.getName() << std::endl;
    } catch (const std::exception &exp) {
        std::cout << exp.what() << std::endl;
    }
}

void changeAmount(AccountTable accountTable, ClientTable clientTable, DepositTable depositTable,
                  std::vector<Account> accounts, int n) {
    std::string newAmount;
    std::cout << "Enter new invested amount: " << std::endl;
    std::cin >> newAmount;
    try {
        Account account = accountTable.update(accounts[n].getId(), accounts[n].getDateClose(), newAmount);
        Client client = clientTable.getById(account.getClientId());
        Deposit deposit = depositTable.getById(account.getDepositId());
        std::cout << "Invested amount updated successfully!" << std::endl << std::endl;
        account.print();
        std::cout << "Client: " << client.getLastName() + " " + client.getFirstName() + " " + client.getPatronymic()
                  << std::endl;
        std::cout << "Deposit: " << deposit.getName() << std::endl;
    } catch (const std::exception &exp) {
        std::cout << exp.what() << std::endl;
    }
}

void deleteAccount(AccountTable accountTable, ClientTable clientTable, DepositTable depositTable) {
    int n, check;
    std::vector<Account> accounts = accountTable.getAll();
    Client client;
    Deposit deposit;
    for (auto it = accounts.begin(); it != accounts.end(); it++) {
        client = clientTable.getById((*it).getClientId());
        deposit = depositTable.getById((*it).getDepositId());
        std::cout << std::distance(accounts.begin(), it) << ". Account: " << (*it).getId() << std::endl;
        std::cout << "   Client: " << client.getLastName() << " " << client.getFirstName() << " "
                  << client.getPatronymic() << std::endl;
        std::cout << "   Deposit: " << deposit.getName() << std::endl;
    }
    std::cout << std::endl << "Enter the account's serial number: " << std::endl;
    std::cin >> n;
    ignoreChars(n);
    std::cout << "Are you sure? (yes - 1/no - 0) " << std::endl;
    std::cin >> check;
    ignoreChars(check);
    if (n >= accounts.size()) {
        std::cout << std::endl;
        std::cerr << "There is no such account!" << std::endl;
    } else if (check) {
        try {
            accountTable.remove(accounts[n].getId());
            std::cout << "Client account delete successfully!" << std::endl << std::endl;
        } catch (const std::exception &exp) {
            std::cout << exp.what() << std::endl;
        }
    }
}