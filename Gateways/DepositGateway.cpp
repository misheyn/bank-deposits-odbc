#include "DepositGateway.h"

DepositGateway::DepositGateway() {
    hdbc = nullptr;
}

DepositGateway::DepositGateway(SQLHDBC hdbc) {
    this->hdbc = hdbc;
}

std::vector<std::vector<std::string>> DepositGateway::insert(std::string name, int period, float rate) {
    SQLHSTMT hstmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    srand(time(NULL));
    int depositCode = 100 + rand() % (999 - 100 + 1);

    std::string insertQuery =
            "INSERT INTO deposits (deposit_code, name, storage_period, rate) VALUES (" + std::to_string(depositCode) +
            ", '" + name + "', " + std::to_string(period) + ", " + std::to_string(rate) +
            ") RETURNING deposit_code, name, storage_period, rate";
    SQLRETURN sqlReturn = SQLExecDirect(hstmt, (SQLCHAR *) insertQuery.c_str(), SQL_NTS);
    handleSQLReturn(sqlReturn, hstmt);

    std::vector<std::vector<std::string>> result = fetchData(hstmt);

    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    return result;
}

std::vector<std::vector<std::string>> DepositGateway::selectAll() {
    SQLHSTMT hstmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    std::string selectQuery =
            "SELECT deposit_code, name, storage_period, rate FROM deposits";
    SQLRETURN sqlReturn = SQLExecDirect(hstmt, (SQLCHAR *) selectQuery.c_str(), SQL_NTS);
    handleSQLReturn(sqlReturn, hstmt);

    std::vector<std::vector<std::string>> result = fetchData(hstmt);

    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    return result;
}

std::vector<std::vector<std::string>> DepositGateway::selectById(int id) {
    SQLHSTMT hstmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    std::string selectQuery =
            "SELECT deposit_code, name, storage_period, rate FROM deposits WHERE deposit_code = " + std::to_string(id);
    SQLRETURN sqlReturn = SQLExecDirect(hstmt, (SQLCHAR *) selectQuery.c_str(), SQL_NTS);
    handleSQLReturn(sqlReturn, hstmt);

    std::vector<std::vector<std::string>> result = fetchData(hstmt);

    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    return result;
}

std::vector<std::vector<std::string>> DepositGateway::update(int depositId, std::string name, int period, float rate) {
    SQLHSTMT hstmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    std::string updateQuery =
            "UPDATE deposits SET name = '" + name + "', storage_period = " + std::to_string(period) + ", rate = " +
            std::to_string(rate) + " WHERE deposit_code = " + std::to_string(depositId) +
            " RETURNING deposit_code, name, storage_period, rate";
    SQLRETURN sqlReturn = SQLExecDirect(hstmt, (SQLCHAR *) updateQuery.c_str(), SQL_NTS);
    handleSQLReturn(sqlReturn, hstmt);

    std::vector<std::vector<std::string>> result = fetchData(hstmt);

    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    return result;
}

void DepositGateway::remove(int depositId) {
    SQLHSTMT hstmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    std::string deleteQuery = "DELETE FROM deposits WHERE deposit_code = " + std::to_string(depositId);
    SQLRETURN sqlReturn = SQLExecDirect(hstmt, (SQLCHAR *) deleteQuery.c_str(), SQL_NTS);
    handleSQLReturn(sqlReturn, hstmt);

    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
}
