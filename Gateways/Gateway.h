#ifndef RPBD_LAB1_GATEWAY_H
#define RPBD_LAB1_GATEWAY_H

#include <windows.h>
#include <odbcinst.h>
#include <iostream>
#include <sql.h>
#include <sqlext.h>
#include <vector>
#include <string>
#include <stdexcept>

class Gateway {
protected:
    void handleSQLReturn(SQLRETURN sqlReturn, SQLHSTMT hstmt);

    std::vector<std::vector<std::string>> fetchData(SQLHSTMT hstmt);
};


#endif //RPBD_LAB1_GATEWAY_H
