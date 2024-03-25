#include "menu.h"

void createTables(SQLHDBC hdbc) {
    SQLHSTMT hstmt;
    SQLRETURN retcode;

    std::string createTablesQuery = "CREATE TABLE IF NOT EXISTS address ("
                                    "address_id serial PRIMARY KEY,"
                                    "city varchar NOT NULL,"
                                    "street varchar NOT NULL,"
                                    "house_number integer NOT NULL"
                                    ");"
                                    "CREATE TABLE IF NOT EXISTS clients ("
                                    "client_code integer PRIMARY KEY,"
                                    "address_id integer REFERENCES address,"
                                    "first_name varchar NOT NULL,"
                                    "last_name varchar NOT NULL,"
                                    "patronymic varchar NOT NULL,"
                                    "passport_series integer NOT NULL,"
                                    "passport_number integer NOT NULL,"
                                    "phone_number numeric(11) NOT NULL"
                                    ");"
                                    "CREATE TABLE IF NOT EXISTS deposits ("
                                    "deposit_code integer PRIMARY KEY,"
                                    "name varchar NOT NULL,"
                                    "storage_period integer NOT NULL,"
                                    "rate real NOT NULL"
                                    ");"
                                    "CREATE TABLE IF NOT EXISTS client_account ("
                                    "account_number integer PRIMARY KEY,"
                                    "client_code integer REFERENCES clients,"
                                    "deposit_code integer REFERENCES deposits,"
                                    "account_opening_date date NOT NULL,"
                                    "account_closing_date date NOT NULL,"
                                    "invested_amount numeric(10, 2) NOT NULL"
                                    ");";

    SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
    retcode = SQLExecDirect(hstmt, (SQLCHAR *) createTablesQuery.c_str(), SQL_NTS);
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
        std::cout << "Successful creation the tables!" << std::endl;

    } else {
        std::cerr << "Error creating tables!" << std::endl;
    }
    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
}

int main() {
    SQLHENV henv;
    SQLHDBC hdbc;
    SQLRETURN retcode;

    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
    SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER) SQL_OV_ODBC3, 0);

    SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);

    std::string connStr = "DRIVER={PostgreSQL ANSI};"
                          "DATABASE=bank_deposits;"
                          "UID=user1;"
                          "PWD=pswd;"
                          "SERVER=localhost;"
                          "PORT=5432;";


    retcode = SQLDriverConnect(hdbc, NULL, (SQLCHAR *) connStr.c_str(), SQL_NTS, NULL, 0, NULL, SQL_DRIVER_COMPLETE);
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
        std::cout << "Successful connection to the database!" << std::endl;

        createTables(hdbc);
        menu(hdbc);

    } else {
        std::cerr << "Error connecting to database!" << std::endl;
    }

    SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
    SQLFreeHandle(SQL_HANDLE_ENV, henv);

    return 0;
}
