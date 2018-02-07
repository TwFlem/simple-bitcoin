#include <iostream>
#include <fstream>
#include <utility>
#include "ledgerCommands.h"
#include "descriptions.h"
#include "ledger.h"
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

void file(Ledger* ledger, bool interactive, bool verbose) {
    string filename;
    string transactionStr;

    if (interactive) cout << "Enter a filename to generate a ledger" << endl;

    getline(cin, filename);

    ifstream file(filename);


    while (getline(file, transactionStr)) {
        struct transaction newTrans = parseTransaction(transactionStr);
        if(newTrans.id == "" || !ledger->addTransaction(newTrans)) {
            ledger->wipe();
            break;
        }
    }
    file.close();
}

void transaction(Ledger* ledger, bool interactive, bool verbose) {
    string trans;

    if (interactive) cout << "Enter a transaction to add to the ledger" << endl;

    getline(cin, trans);

    struct transaction newTrans = parseTransaction(trans);

    if(newTrans.id == "") {
        return;
    }

    ledger->addTransaction(newTrans);
    ledger->print();
}

void dump(Ledger* ledger, bool interactive, bool verbose) {
    string filename;
    ofstream ledgerFile;

    if (interactive) cout << "Enter a file name to dump the ledger" << endl;

    getline(cin, filename);

    ledgerFile.open (filename);
    if (verbose) cout << "Writing ledger to file " << filename << ":" << endl;

    string allFmtTransactions = ledger->getAllFmtTransactions();

    ledgerFile << allFmtTransactions;
    if (verbose) cout << allFmtTransactions;

    ledgerFile.close();
}
