#include "ledger.h"
#include <unordered_map>
#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;


Ledger::Ledger() {}

void Ledger::addTransaction(transaction trans) {
    this->transactionKeys.push_back(trans.id);
    this->transactions.insert(pair<string, transaction>(trans.id, trans));
}

void Ledger::print() {
    cout << endl;
    cout << this->getAllFmtTransactions() << endl;
}

string Ledger::getAllFmtTransactions() {
    string transactions = "";
    for(auto const transId : this->transactionKeys) {
        transaction trans = this->transactions.at(transId);
        transactions = transactions + fmtTrans(transId, trans.utxos, trans.accounts) + "\n";
    }
    return transactions;
}

void Ledger::wipe() {
    std::vector<std::string> transactionKeys;
    transactionMap transactions;
    this->transactionKeys = transactionKeys;
    this->transactions = transactions;
}

string fmtTrans(string transId, vector<utxo> utxos, vector<account> accounts) {
    string transStr = "";
    transStr = transStr + transId + "; " + to_string(utxos.size()) + "; ";

    for(int i = 0; i < utxos.size(); i++) {
        utxo currUtxo = utxos.at(i);
        transStr = transStr + "(" + currUtxo.transactionId + ", " + to_string(currUtxo.index) + ")";

        if (i == utxos.size() - 1) transStr = transStr + "; ";
    }

    transStr = transStr + to_string(accounts.size()) + "; ";

    for(int i = 0; i < accounts.size(); i++) {
        account currAccount = accounts.at(i);
        transStr = transStr + "(" + currAccount.accountId + ", " + to_string(currAccount.amt) + ")";
    }
    return transStr;
}

transaction parseTransaction(string transStr) {
    string transId;
    int utxoCnt;
    int voutCnt;
    transaction trans;
    vector<utxo> utxos;
    vector<account> accounts;
    transaction emptyTrans = transaction{ transId, utxos, accounts };

    string token = "";
    string errTrans = "Bad Transaction: " + transStr;

    int iterator = 0;

    transId = extractId(iterator, transStr, SEMI_COLON);
    cout << "extracted trans id: " << transId << endl;

    if (transId == "" || transId.length() != VALID_ID_LENGTH) {
        if (transId.length() != VALID_ID_LENGTH) cout << "Error: transaction id is not "
                                                      << VALID_ID_LENGTH << " characters in length" << endl;
        cout << errTrans << endl;
        return emptyTrans;
    }

    string utxoCntStr = extractPairCnt(iterator, transStr, SEMI_COLON);
    cout << "extracted uxto cnt: " << utxoCntStr << endl;


    utxoCnt = stoi(utxoCntStr);

    utxos = extractUtxoPairs(iterator, transStr, utxoCnt);
    cout << "utxo pairs: " << utxos.at(0).transactionId << " " << utxos.at(0).index << endl;

    if (transId == "") {
        cout << errTrans << endl;
        return emptyTrans;
    }
    if (transId == "") {
        cout << errTrans << endl;
        return emptyTrans;
    }
    string voutCntStr = extractPairCnt(iterator, transStr, SEMI_COLON);
    cout << "extracted: " << voutCntStr << endl;

    if (transId == "") {
        cout << errTrans << endl;
        return emptyTrans;
    }

    voutCnt = stoi(voutCntStr);

    accounts = extractAccountPairs(iterator, transStr, voutCnt);
    cout << "vout pairs: " << accounts.at(0).accountId << " " << accounts.at(0).amt << endl;


    return transaction{
            transId,
            utxos,
            accounts
    };
}

string extractId(int &i, string transStr, char endingDelim) {
    string token = "";
    for (i; i < transStr.length(); i++) {


        if (isspace(transStr[i])) continue;

        if (isalnum(transStr[i])) {

            if (token.length() > 0) {
                cout << "Error: transaction id mal formed." << endl;
                token = "";
                break;
            }
            while(isalnum(transStr[i])) {
                token = token + transStr[i];
                i++;
            }

            i--;
            continue;
        }

        if (transStr[i] == endingDelim) {
            i++;
            break;
        }

        if (!isspace(transStr[i]) && !isalnum(transStr[i])) {
            cout << "Error: \"" << transStr[i] << "\" is not part of a valid transaction id." << endl;
            token = "";
            break;
        }
    }
    return token;
}

string extractPairCnt(int &i, string transStr, char endingDelim) {
    string token = "";
    for (i; i < transStr.length(); i++) {

        if (isspace(transStr[i])) continue;

        if (isdigit(transStr[i])) {
            while(isdigit(transStr[i])) {
                token = token + transStr[i];
                i++;
            }
            i--;
            continue;
        }

        if (transStr[i] == endingDelim) {
            i++;
            break;
        }

        if (!isspace(transStr[i]) && !isdigit(transStr[i]) && transStr[i] != endingDelim) {
            cout << "Error: \"" << transStr[i] << "\" is not part of a valid utxo count." << endl;
            return "";
        }
    }
    return token;
}

vector<utxo> extractUtxoPairs(int &i, string transStr, int utxoNum) {
    vector<utxo> utxos;
    string token = "";

    for (int x = 0; x < utxoNum; x++) {
        utxo ut;
        for (i; i < transStr.length(); i++) {

            if (isspace(transStr[i])) continue;

            if (transStr[i] == '(') {
                //TODO: account for no )
                bool complete = false;
                while (!complete) {
                    i++;
                    if (isspace(transStr[i])) continue;

                    if (isalnum(transStr[i])) {
                        ut.transactionId = extractId(i, transStr, COMMA);
                        while (transStr[i] != CLOSING_PAREN) {
                            ut.index = stoi(extractPairCnt(i, transStr, CLOSING_PAREN));
                            complete = true;
                            break;
                        }
                    }

                }
                utxos.push_back(ut);
                break;
            }

            if (transStr[i] == ';') {
                i++;
                break;
            }
        }
    }
    //TODO: fix this
    i++;
    cout << "i and char before returning utxos: " << i << " " << transStr[i] << endl;
    return utxos;
}

vector<account> extractAccountPairs(int &i, string transStr, int accNum) {
    vector<account> accounts;
    string token = "";

    for (int x = 0; x < accNum; x++) {
        account acc;
        for (i; i < transStr.length(); i++) {

            if (isspace(transStr[i])) continue;

            if (transStr[i] == '(') {
                //TODO: account for no )
                bool complete = false;
                while (!complete) {
                    i++;
                    if (isspace(transStr[i])) continue;

                    if (isalnum(transStr[i])) {
                        acc.accountId = extractId(i, transStr, COMMA);
                        while (transStr[i] != CLOSING_PAREN) {
                            acc.amt = stoi(extractPairCnt(i, transStr, CLOSING_PAREN));
                            complete = true;
                            break;
                        }
                    }

                }
                accounts.push_back(acc);
                break;
            }

            if (transStr[i] == ';') {
                i++;
                break;
            }
        }
    }
    return accounts;
}