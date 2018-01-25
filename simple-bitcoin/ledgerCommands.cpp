#include <iostream>
#include "ledgerCommands.h"
#include "descriptions.h"

void help() {
    std::cout << std::endl;
    std::cout << F_CMD_DESC << std::endl;
    std::cout << T_CMD_DESC << std::endl;
    std::cout << E_CMD_DESC << std::endl;
    std::cout << P_CMD_DESC << std::endl;
    std::cout << D_CMD_DESC << std::endl;
    std::cout << W_CMD_DESC << std::endl;
    std::cout << I_CMD_DESC << std::endl;
    std::cout << V_CMD_DESC << std::endl;
}
