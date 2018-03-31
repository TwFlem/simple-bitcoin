#include <iostream>
#include <stdio.h>
#include <fstream>
#include <utility>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
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
    string possibleSig;
    bool hadSig = true;

    if (interactive) cout << "Enter a filename to generate a ledger" << endl;

    getline(cin, filename);

    ifstream file(filename);

    if(!file) {
        cerr << "Error: file " << filename << " cannot be opened for reading" << endl;
        return;
    }


    while (true) {
        if(hadSig) {
            if(!getline(file, transactionStr)) {
                break;
            }
        }

        if(transactionStr == "") {
            hadSig = true;
            continue;
        }

        struct transaction newTrans = parseTransaction(transactionStr);

        // account for possible signature on next line
        if(!getline(file, possibleSig)) {
            if(newTrans.id != "") {
                !ledger->addTransaction(newTrans, verbose);
            }
            break;
        }

        if(isHex(possibleSig)) {
            newTrans.signature = possibleSig;
            hadSig = true;
        } else {
            transactionStr = possibleSig;
            hadSig = false;
        }

        if(newTrans.id != "") {
            if(verbose) cout << newTrans.id << " has signature of: " << newTrans.signature << endl;
            !ledger->addTransaction(newTrans, verbose);
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

    ledger->addTransaction(newTrans, verbose);
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

    ledger->getBalance(accName);
}

void output(Ledger* ledger) {
    ledger->outputBlock();
}

void readKeyFile(unordered_map<string, EVP_PKEY*>* accCryptoKeys, bool interactive, bool verbose) {
    string input;
    string token = "";
    vector<string> tokens;
    string accountId;
    string filename;
    EVP_PKEY* pkey;
    if (interactive) cout << "Enter an <accountId> <keyFilename>" << endl;
    getline(cin, input);

    for(int i = 0; i < input.length(); i++) {
        if(isspace(input[i])) {
            tokens.push_back(token);
            token = "";
            continue;
        }
        token = token + input[i];
    }
    if(token.length() != 0) {
        tokens.push_back(token);
    }

    if(tokens.size() < 2) {
        cerr << "Error: key file not read, not enough arguments." << endl;
        cerr << tokens.at(0) << endl;
        return;
    }

    accountId = tokens.at(0);
    filename = tokens.at(1);

    if(tokens.size() > 2) {
        string excessTokens = "";
        for(int i = 2; i < tokens.size(); i++) {
            excessTokens = excessTokens + " " + tokens.at(i);
        }
        cerr << "Warning: too many tokens provided." << endl;
        cerr << "<accountId> " << accountId << endl;
        cerr << "<keyFilename> " << filename << endl;
        cerr << "Excess tokens: " << excessTokens << endl;
        cerr << "File will be read using the accountId and keyFilename" << endl;
    }
    FILE* fp = fopen(filename.c_str(), "r");
    if(fp == NULL) {
        cerr << "Error: Public key " << accountId << " " << filename << " not read" << endl;
        return;
    }

    pkey = PEM_read_PUBKEY(fp, NULL, NULL, NULL);
    if(pkey == NULL) {
        cerr << "Error: Public key " << accountId << " " << filename << " not read" << endl;
        return;
    }
    fclose(fp);

    if (accCryptoKeys->find(accountId) == accCryptoKeys->end()) {
        accCryptoKeys->insert(pair<string, EVP_PKEY*>(accountId, pkey));
    } else {
        cerr << "Warning: overwitten previously set public key for " << accountId << endl;
        accCryptoKeys->at(accountId) = pkey;
    }
    if (verbose) cout << "Added public key " << accCryptoKeys->at(accountId) << endl;
}
