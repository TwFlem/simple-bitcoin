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
    cout << B_CMD_DESC << endl;
}

void file(Ledger* ledger, bool interactive, bool verbose) {
    string filename;
    string transactionStr;

    if (interactive) cout << "Enter a filename to generate a ledger" << endl;

    getline(cin, filename);

    ifstream file(filename);

    if(!file) {
        cerr << "Error: file " << filename << " cannot be opened for reading" << endl;
        return;
    }


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

    if (interactive) cout << "Enter a transaction:" << endl;

    getline(cin, trans);

    struct transaction newTrans = parseTransaction(trans);

    if(newTrans.id == "") {
        return;
    }

    ledger->addTransaction(newTrans);
}

void dump(Ledger* ledger, bool interactive, bool verbose) {
    string filename;
    ofstream ledgerFile;

    if (interactive) cout << "Enter a file name to dump the ledger" << endl;

    getline(cin, filename);

    try {
        ledgerFile.open(filename);
    } catch (string e) {
        cerr << "Error: file " << filename << " cannot be opened for writing" << endl;
        return;
    }

    if (verbose) cout << "Writing ledger to file " << filename << ":" << endl;

    string allFmtTransactions = ledger->getAllFmtTransactions();

    ledgerFile << allFmtTransactions;
    if (verbose) cout << allFmtTransactions;

    ledgerFile.close();
}

void balance(Ledger* ledger, bool interactive, bool verbose) {
    string accName;
    if (interactive) cout << "Enter an account name:" << endl;

    getline(cin, accName);

    ledger->balance(accName);
}
