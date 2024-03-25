cmake_minimum_required(VERSION 3.24)
project(RPBD_Lab1)

set(CMAKE_CXX_STANDARD 17)

add_executable(RPBD_Lab1 main.cpp Models/Client.cpp Models/Client.h Gateways/ClientGateway.cpp Gateways/ClientGateway.h Models/Address.cpp Models/Address.h Models/Deposit.cpp Models/Deposit.h Models/Account.cpp Models/Account.h Gateways/DepositGateway.cpp Gateways/DepositGateway.h Gateways/AccountGateway.cpp Gateways/AccountGateway.h Tables/ClientTable.cpp Tables/ClientTable.h Tables/DepositTable.cpp Tables/DepositTable.h Tables/AccountTable.cpp Tables/AccountTable.h menu.cpp menu.h Gateways/Gateway.h Gateways/AddressGateway.cpp Gateways/AddressGateway.h Tables/AddressTable.cpp Tables/AddressTable.h Gateways/Gateway.cpp)

target_link_libraries(RPBD_Lab1 -lodbc32 -lodbccp32)