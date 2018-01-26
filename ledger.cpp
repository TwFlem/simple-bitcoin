#include "ledger.h"
#include <unordered_map>
#include <vector>
#include <iostream>
#include <string>

using namespace std;


Ledger::Ledger() {}

void Ledger::addTransaction(unsigned int transId, transaction trans) {
    this->transactionkeys.push_back(transId);
    this->transactions.insert(pair<unsigned int, transaction>(transId, trans));
}

void Ledger::print() {
    cout << endl;
    cout << this->getAllFmtTransactions() << endl;
}

string Ledger::getAllFmtTransactions() {
    string transactions = "";
    for(auto const transId : this->transactionkeys) {
        transaction trans = this->transactions.at(transId);
        transactions = transactions + fmtTrans(transId, trans.utxos, trans.accounts) + "\n";
    }
    return transactions;
}

string fmtTrans(unsigned int transId, vector<utxo> utxos, vector<account> accounts) {
    string transStr = "";
    transStr = transStr + to_string(transId) + "; " + to_string(utxos.size()) + "; ";

    for(int i = 0; i < utxos.size(); i++) {
        utxo currUtxo = utxos.at(i);
        transStr = transStr + "(" + to_string(currUtxo.transactionId) + ", " + to_string(currUtxo.index) + ")";

        if (i == utxos.size() - 1) transStr = transStr + "; ";
        else transStr = transStr + " ";
    }

    transStr = transStr + to_string(accounts.size()) + "; ";

    for(int i = 0; i < accounts.size(); i++) {
        account currAccount = accounts.at(i);
        transStr = transStr + "(" + currAccount.accountId + ", " + to_string(currAccount.amt) + ") ";
    }
    return transStr;
}