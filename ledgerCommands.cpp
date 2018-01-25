#include <iostream>
#include "ledgerCommands.h"
#include "descriptions.h"
using namespace std;

void help() {
    cout << endl;
    cout << F_CMD_DESC << endl;
    cout << T_CMD_DESC << endl;
    cout << E_CMD_DESC << endl;
    cout << P_CMD_DESC << endl;
    cout << D_CMD_DESC << endl;
    cout << W_CMD_DESC << endl;
    cout << I_CMD_DESC << endl;
    cout << V_CMD_DESC << endl;
}

void file(string filename, bool interactive, bool verbose) {
    cout << filename << endl;
}

void transaction(string input, bool interactive, bool verbose) {
    cout << input << endl;
}

void print() {
    cout << "print called" << endl;
}

void dump(string filename, bool interactive, bool verbose) {
    cout << filename << endl;
}

void wipe(bool interactive, bool verbose) {
    cout << "wipe called" << endl;
}