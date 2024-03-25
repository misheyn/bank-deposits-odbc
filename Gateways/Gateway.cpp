#include "Gateway.h"

void Gateway::handleSQLReturn(SQLRETURN sqlReturn, SQLHSTMT hstmt) {
    if (sqlReturn != SQL_SUCCESS) {
        SQLCHAR sqlState[6];
        SQLCHAR errorMsg[SQL_MAX_MESSAGE_LENGTH];
        SQLINTEGER error;
        SQLSMALLINT errorMsgLen;

        SQLGetDiagRec(SQL_HANDLE_STMT, hstmt, 1, sqlState, &error, errorMsg, SQL_MAX_MESSAGE_LENGTH,
                      &errorMsgLen);

        std::string errorMessage = "Error in DB PostgreSQL, state [" + std::string((const char *) (sqlState)) + "]: " +
                                   std::string((const char *) (errorMsg));
        throw std::runtime_error(errorMessage);
    }
}

std::vector<std::vector<std::string>> Gateway::fetchData(SQLHSTMT hstmt) {
    std::vector<std::vector<std::string>> result;
    SQLCHAR columnName[256];
    SQLLEN columnNameLen;
    SQLSMALLINT columnCount = 0;

    SQLNumResultCols(hstmt, &columnCount);

    if (columnCount > 0) {
        while (SQLFetch(hstmt) == SQL_SUCCESS) {
            std::vector<std::string> row;
            for (int i = 1; i <= columnCount; i++) {
                SQLGetData(hstmt, i,
                           SQL_C_CHAR, columnName, sizeof(columnName), &columnNameLen);
                row.emplace_back((const char *) (columnName));
            }
            result.push_back(row);
        }
    }
    return result;
}

