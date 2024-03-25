#include "AddressGateway.h"

AddressGateway::AddressGateway() {
    hdbc = nullptr;
}

AddressGateway::AddressGateway(SQLHDBC hdbc) {
    this->hdbc = hdbc;
}

std::vector<std::vector<std::string>> AddressGateway::insert(std::string city, std::string street, int houseNumber) {
    SQLHSTMT hstmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    std::string insertQuery =
            "INSERT INTO address (address_id, city, street, house_number) VALUES (DEFAULT, '" +
            city + "', '" + street + "', " + std::to_string(houseNumber) +
            ") RETURNING address_id, city, street, house_number";
    SQLRETURN sqlReturn = SQLExecDirect(hstmt, (SQLCHAR *) insertQuery.c_str(), SQL_NTS);
    handleSQLReturn(sqlReturn, hstmt);

    std::vector<std::vector<std::string>> result = fetchData(hstmt);

    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    return result;
}

std::vector<std::vector<std::string>> AddressGateway::select(int id) {
    SQLHSTMT hstmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    std::string selectQuery =
            "SELECT address_id, city, street, house_number FROM address WHERE address_id = " + std::to_string(id);
    SQLRETURN sqlReturn = SQLExecDirect(hstmt, (SQLCHAR *) selectQuery.c_str(), SQL_NTS);
    handleSQLReturn(sqlReturn, hstmt);

    std::vector<std::vector<std::string>> result = fetchData(hstmt);

    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    return result;
}

std::vector<std::vector<std::string>>
AddressGateway::update(int id, std::string city, std::string street, int houseNumber) {
    SQLHSTMT hstmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    std::string updateQuery = "UPDATE address SET city = '" + city + "', street = '" + street + +"', house_number = " +
                              std::to_string(houseNumber) + " WHERE address_id = " + std::to_string(id) +
                              " RETURNING address_id, city, street, house_number";
    SQLRETURN sqlReturn = SQLExecDirect(hstmt, (SQLCHAR *) updateQuery.c_str(), SQL_NTS);
    handleSQLReturn(sqlReturn, hstmt);

    std::vector<std::vector<std::string>> result = fetchData(hstmt);

    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    return result;
}

void AddressGateway::remove(int id) {
    SQLHSTMT hstmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    std::string deleteQuery = "DELETE FROM address WHERE address_id = " + std::to_string(id);
    SQLRETURN sqlReturn = SQLExecDirect(hstmt, (SQLCHAR *) deleteQuery.c_str(), SQL_NTS);
    handleSQLReturn(sqlReturn, hstmt);

    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
}

