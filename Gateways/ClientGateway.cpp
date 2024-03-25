#include "ClientGateway.h"

ClientGateway::ClientGateway() {
    hdbc = nullptr;
}

ClientGateway::ClientGateway(SQLHDBC hdbc) {
    this->hdbc = hdbc;
}

std::vector<std::vector<std::string>>
ClientGateway::insert(int addressId, std::string firstName, std::string lastName, std::string patronymic,
                      int passportSeries, int passportNumber, std::string phoneNumber) {
    SQLHSTMT hstmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    srand(time(NULL));
    int clientCode = 1000 + rand() % (9999 - 1000 + 1);

    std::string insertQuery =
            "INSERT INTO clients (client_code, address_id, first_name, last_name, patronymic, passport_series, "
            "passport_number, phone_number) VALUES (" + std::to_string(clientCode) + ", " +
            std::to_string(addressId) + ", '" + firstName + "', '" + lastName + "', '" + patronymic + "', " +
            std::to_string(passportSeries) + ", " + std::to_string(passportNumber) + ", " + phoneNumber +
            ") RETURNING client_code, address_id, first_name, last_name, patronymic, passport_series, "
            "passport_number, phone_number";
    SQLRETURN sqlReturn = SQLExecDirect(hstmt, (SQLCHAR *) insertQuery.c_str(), SQL_NTS);
    handleSQLReturn(sqlReturn, hstmt);

    std::vector<std::vector<std::string>> result = fetchData(hstmt);

    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    return result;
}

std::vector<std::vector<std::string>> ClientGateway::selectAll() {
    SQLHSTMT hstmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    std::string selectQuery =
            "SELECT client_code, address_id, first_name, last_name, patronymic, passport_series, passport_number, "
            "phone_number FROM clients";
    SQLRETURN sqlReturn = SQLExecDirect(hstmt, (SQLCHAR *) selectQuery.c_str(), SQL_NTS);
    handleSQLReturn(sqlReturn, hstmt);

    std::vector<std::vector<std::string>> result = fetchData(hstmt);

    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    return result;
}

std::vector<std::vector<std::string>> ClientGateway::selectById(int id) {
    SQLHSTMT hstmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    std::string selectQuery =
            "SELECT client_code, address_id, first_name, last_name, patronymic, passport_series, passport_number, "
            "phone_number FROM clients WHERE client_code = " + std::to_string(id);
    SQLRETURN sqlReturn = SQLExecDirect(hstmt, (SQLCHAR *) selectQuery.c_str(), SQL_NTS);
    handleSQLReturn(sqlReturn, hstmt);

    std::vector<std::vector<std::string>> result = fetchData(hstmt);

    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    return result;
}

std::vector<std::vector<std::string>>
ClientGateway::update(int clientId, std::string firstName, std::string lastName, std::string patronymic,
                      int passportSeries, int passportNumber, std::string phoneNumber) {
    SQLHSTMT hstmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    std::string updateQuery =
            "UPDATE clients SET first_name = '" + firstName + "', last_name = '" + lastName + "', patronymic = '" +
            patronymic + "', passport_series = " + std::to_string(passportSeries) + ", passport_number = " +
            std::to_string(passportNumber) + ", phone_number = " + phoneNumber + " WHERE client_code = " +
            std::to_string(clientId) + " RETURNING client_code, address_id, first_name, last_name, patronymic, "
                                       "passport_series, passport_number, phone_number";
    SQLRETURN sqlReturn = SQLExecDirect(hstmt, (SQLCHAR *) updateQuery.c_str(), SQL_NTS);
    handleSQLReturn(sqlReturn, hstmt);

    std::vector<std::vector<std::string>> result = fetchData(hstmt);

    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    return result;
}

void ClientGateway::remove(int clientId) {
    SQLHSTMT hstmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    std::string deleteQuery = "DELETE FROM clients WHERE client_code = " + std::to_string(clientId);
    SQLRETURN sqlReturn = SQLExecDirect(hstmt, (SQLCHAR *) deleteQuery.c_str(), SQL_NTS);
    handleSQLReturn(sqlReturn, hstmt);

    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
}
