#include "AccountGateway.h"

AccountGateway::AccountGateway() {
    hdbc = nullptr;
}

AccountGateway::AccountGateway(SQLHDBC hdbc) {
    this->hdbc = hdbc;
}

std::vector<std::vector<std::string>>
AccountGateway::insert(int clientId, int depositId, std::string dateOpen, std::string dateClose, std::string amount) {
    SQLHSTMT hstmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    srand(time(NULL));
    int accountNumber = 100000 + rand() % (999999 - 100000 + 1);

    std::string insertQuery =
            "INSERT INTO client_account (account_number, client_code, deposit_code, account_opening_date, "
            "account_closing_date, invested_amount) VALUES (" + std::to_string(accountNumber) + ", " +
            std::to_string(clientId) + ", " + std::to_string(depositId) + ", '" + dateOpen + "', '" +
            dateClose + "', " + amount + ") RETURNING account_number, client_code, deposit_code, account_opening_date, "
                                         "account_closing_date, invested_amount";
    SQLRETURN sqlReturn = SQLExecDirect(hstmt, (SQLCHAR *) insertQuery.c_str(), SQL_NTS);
    handleSQLReturn(sqlReturn, hstmt);

    std::vector<std::vector<std::string>> result = fetchData(hstmt);

    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    return result;
}

std::vector<std::vector<std::string>> AccountGateway::selectAll() {
    SQLHSTMT hstmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    std::string selectQuery =
            "SELECT account_number, client_code, deposit_code, account_opening_date, account_closing_date, "
            "invested_amount FROM client_account";
    SQLRETURN sqlReturn = SQLExecDirect(hstmt, (SQLCHAR *) selectQuery.c_str(), SQL_NTS);
    handleSQLReturn(sqlReturn, hstmt);

    std::vector<std::vector<std::string>> result = fetchData(hstmt);

    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    return result;
}

std::vector<std::vector<std::string>> AccountGateway::selectById(int id) {
    SQLHSTMT hstmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    std::string selectQuery =
            "SELECT account_number, client_code, deposit_code, account_opening_date, account_closing_date, "
            "invested_amount FROM client_account WHERE account_number = " + std::to_string(id);
    SQLRETURN sqlReturn = SQLExecDirect(hstmt, (SQLCHAR *) selectQuery.c_str(), SQL_NTS);
    handleSQLReturn(sqlReturn, hstmt);

    std::vector<std::vector<std::string>> result = fetchData(hstmt);

    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    return result;
}

std::vector<std::vector<std::string>> AccountGateway::selectByClient(int clientId) {
    SQLHSTMT hstmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    std::string selectQuery =
            "SELECT account_number, client_code, deposit_code, account_opening_date, account_closing_date, "
            "invested_amount FROM client_account WHERE client_code = " + std::to_string(clientId);
    SQLRETURN sqlReturn = SQLExecDirect(hstmt, (SQLCHAR *) selectQuery.c_str(), SQL_NTS);
    handleSQLReturn(sqlReturn, hstmt);

    std::vector<std::vector<std::string>> result = fetchData(hstmt);

    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    return result;
}

std::vector<std::vector<std::string>> AccountGateway::selectByDeposit(int depositId) {
    SQLHSTMT hstmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    std::string selectQuery =
            "SELECT account_number, client_code, deposit_code, account_opening_date, account_closing_date, "
            "invested_amount FROM client_account WHERE deposit_code = " + std::to_string(depositId);
    SQLRETURN sqlReturn = SQLExecDirect(hstmt, (SQLCHAR *) selectQuery.c_str(), SQL_NTS);
    handleSQLReturn(sqlReturn, hstmt);

    std::vector<std::vector<std::string>> result = fetchData(hstmt);

    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    return result;
}

std::vector<std::vector<std::string>>
AccountGateway::update(int accountId, std::string dateClose, std::string amount) {
    SQLHSTMT hstmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    std::string updateQuery =
            "UPDATE client_account SET account_closing_date = '" + dateClose + "', invested_amount = " + amount +
            " WHERE account_number = " + std::to_string(accountId) + " RETURNING account_number, client_code, "
                                                                     "deposit_code, account_opening_date, account_closing_date, invested_amount";
    SQLRETURN sqlReturn = SQLExecDirect(hstmt, (SQLCHAR *) updateQuery.c_str(), SQL_NTS);
    handleSQLReturn(sqlReturn, hstmt);

    std::vector<std::vector<std::string>> result = fetchData(hstmt);

    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    return result;
}

void AccountGateway::remove(int accountId) {
    SQLHSTMT hstmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    std::string deleteQuery = "DELETE FROM client_account WHERE account_number = " + std::to_string(accountId);
    SQLRETURN sqlReturn = SQLExecDirect(hstmt, (SQLCHAR *) deleteQuery.c_str(), SQL_NTS);
    handleSQLReturn(sqlReturn, hstmt);

    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
}


