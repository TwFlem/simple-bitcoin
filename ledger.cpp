#include "ledger.h"
#include "descriptions.h"
#include <unordered_map>
#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;


Ledger::Ledger() {}

bool Ledger::addTransaction(transaction trans) {
    if(!this->validateId(trans)) {
        cout << ERR_TRANS_ID_TAKEN << trans.id << endl;
        return false;
    }

    if(!this->validateInput(trans)) {
        return false;
    }


    this->transactionKeys.push_back(trans.id);
    this->transactions.insert(pair<string, transaction>(trans.id, trans));
    return  true;
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

int Ledger::size() {
    return this->transactionKeys.size();
}

bool Ledger::validateId(transaction trans) {
    for(int i = 0; i < this->transactionKeys.size(); i++) {
        if(this->transactionKeys.at(i) == trans.id) {
            return false;
        }
    }
    return true;
}

bool Ledger::ledgerHasId(string id) {
    for(int i = 0; i < this->transactionKeys.size(); i++) {
        if(this->transactionKeys.at(i) == id) {
            return true;
        }
    }
    return false;
}

bool Ledger::validateInput(transaction trans) {
    unsigned int currTransSum = this->sumAccountBalances(trans.accounts);
    unsigned int sumOfAllUtxoin = 0;
    vector<account> accsIn;
    for(int i = 0; i < trans.utxos.size(); i++) {
        utxo inUtxo = trans.utxos.at(i);
        transaction prevTrans;

        if (!this->getTransaction(inUtxo.transactionId, prevTrans)) {
            cout << ERR_TRANS_ID_DOES_NOT_EXIST << inUtxo.transactionId << endl;
            return false;
        }

        if (inUtxo.index > prevTrans.accounts.size() - 1) {
            cout << ERR_TRANS_GENERIC << trans.id << endl;
            cout << ERR_UTXO_INDEX_OOB << trans.id;
            cout << " UTXO with transaction id: " << inUtxo.transactionId;
            cout << " accounts size " << prevTrans.accounts.size() << " <= " << inUtxo.index << endl;
            return false;
        }

        sumOfAllUtxoin +=  prevTrans.accounts.at(inUtxo.index).amt;
        accsIn.push_back(prevTrans.accounts.at(inUtxo.index));
    }

    if (trans.utxos.size() > 0 && currTransSum != sumOfAllUtxoin) {
        cout << ERR_UTXO_ACC_MISMATCH << "previous transaction input balance ";
        cout << sumOfAllUtxoin << " conflicts with this ";
        cout << "transaction's output total of " << currTransSum << endl;
        return false;
    }

    for (int i = 0; i < accsIn.size(); i++) {
        bool found = false;
        for (int j = 0; j < trans.accounts.size(); j++) {
            if (trans.accounts.at(j).accountId == accsIn.at(i).accountId) {
                found = true;
                break;
            }
        }
        if (!found) {
            cout << ERR_UTXO_ACC_MISMATCH << "previous transaction account id ";
            cout << accsIn.at(i).accountId << " does not appear in ";
            cout << "transaction " << trans.id << " output" << endl;
            return false;
        }
    }

    return true;
}


bool Ledger::getTransaction(string id, transaction &trans) {
    bool valid = this->ledgerHasId(id);
    if (valid) {
        trans = this->transactions[id];
    }
    return valid;
}

unsigned int Ledger::sumAccountBalances(std::vector<account> accs) {
    unsigned int sum = 0;
    for(int i = 0; i < accs.size(); i++) {
        sum += accs.at(i).amt;
    }
    return sum;
}

string fmtTrans(string transId, vector<utxo> utxos, vector<account> accounts) {
    string transStr = "";
    transStr = transStr + transId + "; " + to_string(utxos.size()) + "; ";

    if (utxos.size() == 0) transStr = transStr + "; ";

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

    string errTrans = "Bad Transaction: " + transStr;

    int iterator = 0;

    transId = extractId(iterator, transStr, SEMI_COLON);

    // if verbose
    cout << "extracted trans id: " << transId << endl;

    if (transId == "" || transId.length() != VALID_ID_LENGTH) {
        if (transId == "") {
            cout << INVALID_ID_BASE << transStr << endl;
        } else {
            cout << INVALID_ID_BASE << transId << " in " << transStr << " has invalid length of ";
            cout << transId.length() << ". Should be " << VALID_ID_LENGTH << "." << endl;
        }
        return transaction{};
    }

    string utxoCntStr = extractId(iterator, transStr, SEMI_COLON);
    cout << "extracted uxto cnt: " << utxoCntStr << endl;

    if(utxoCntStr == "" || !is_number(utxoCntStr)) {
        if (transId == "") {
            cout << INVALID_UTXO_CNT_BASE << transStr << endl;
        } else {
            cout << INVALID_UTXO_CNT_BASE << transId << " in " << transStr << " must be numeric." << endl;
        }
        return transaction{};
    }


    try {
        utxoCnt = stoi(utxoCntStr);
    } catch (string &e) {
        cout << e << endl;
        return transaction{};
    }

    if (utxoCnt == 0) {
        trimWhiteSpace(iterator, transStr);
        if(iterator >= transStr.length() || transStr[iterator] != SEMI_COLON) {
            cout << "Error: utxo count mismatch." << endl;
            return transaction{};
        }
        iterator++;
    } else {
        utxos = extractUtxoPairs(iterator, transStr, utxoCnt);
        if(utxos.size() == 0) {
            cout << "Error: utxo mal formed" << endl;
            return transaction{};
        }
        cout << "utxo pairs: " << utxos.at(0).transactionId << " " << utxos.at(0).index << endl;
    }
    cout << "before extracted: " << transStr[iterator] << endl;

    if(utxoCnt != utxos.size()) {
        cout << "Error: utxo count does match utxo size" << endl;
        return transaction{};
    }

    string voutCntStr = extractPairCnt(iterator, transStr, SEMI_COLON);
    cout << "extracted: " << voutCntStr << endl;

    if(voutCntStr == "" || !is_number(voutCntStr)) {
        if (voutCntStr == "") {
            cout << INVALID_VOUT_CNT_BASE << transStr << endl;
        } else {
            cout << INVALID_VOUT_CNT_BASE << transId << " in " << transStr << " must be numeric." << endl;
        }
        return transaction{};
    }

    try {
        voutCnt = stoi(voutCntStr);
    } catch (string &e) {
        cout << e << endl;
        return transaction{};
    }

    if (voutCnt == 0) {
        scanToDelim(iterator, transStr, SEMI_COLON);
        iterator++;
    } else {
        accounts = extractAccountPairs(iterator, transStr, voutCnt);
        if(accounts.size() == 0) {
            cout << "Error: vout mal formed" << endl;
            return transaction{};
        }
    }

    if (accounts.size() > 0) cout << "vout pairs: " << accounts.at(0).accountId << " " << accounts.at(0).amt << endl;

    if(voutCnt != accounts.size()) {
        cout << "Error: vout count does match vout size" << endl;
        return transaction{};
    }

    trimWhiteSpace(iterator, transStr);

    if(iterator != transStr.length()) {
        cout << "Error: mal formed transaction." << endl;
        cout << iterator << " " << transStr.length() << endl;
        return transaction{};
    }


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
    vector<utxo> emptyUtxo;
    string token = "";

    for (int x = 0; x < utxoNum; x++) {
        utxo ut;
        for (i; i < transStr.length(); i++) {

            if (isspace(transStr[i])) continue;

            else if (transStr[i] == '(') {
                //TODO: account for no )
                bool complete = false;
                while (!complete) {
                    i++;
                    if (isspace(transStr[i])) continue;

                    if (isalnum(transStr[i])) {
                        string transId = extractId(i, transStr, COMMA);
                        if (transId == "" || transId.length() != VALID_ID_LENGTH) {
                            if (transId == "") {
                                cout << INVALID_ID_BASE << transStr << endl;
                            } else {
                                cout << INVALID_ID_BASE << transId << " in " << transStr << " has invalid length of ";
                                cout << transId.length() << ". Should be " << VALID_ID_LENGTH << "." << endl;
                            }
                            return emptyUtxo;
                        }
                        ut.transactionId = transId;
                        while (transStr[i] != CLOSING_PAREN) {
                            unsigned int utxoIndex;
                            string utxoIndexStr = extractPairCnt(i, transStr, CLOSING_PAREN);

                            if (!is_number(utxoIndexStr)) {
                                cout << INVALID_VOUT_CNT_BASE << transId << " in " << transStr << " must be numeric." << endl;
                                return emptyUtxo;
                            }
                            utxoIndex = stoi(utxoIndexStr);
                            ut.index = utxoIndex;
                            complete = true;
                            break;
                        }
                    }

                }
                utxos.push_back(ut);
                break;
            }

            else if (transStr[i] == ';') {
                i++;
                break;
            }

            else {
                cout << "Error: Missing (" << endl;
                return emptyUtxo;
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
    vector<account> emptyAccs;
    string token = "";

    for (int x = 0; x < accNum; x++) {
        account acc;
        for (i; i < transStr.length(); i++) {

            if (isspace(transStr[i])) continue;

            else if (transStr[i] == '(') {
                //TODO: account for no )
                bool complete = false;
                while (!complete) {
                    i++;
                    if (isspace(transStr[i])) continue;

                    if (isalnum(transStr[i])) {
                        string accId = extractId(i, transStr, COMMA);
                        if(accId == "") {
                            cout << INVALID_ACC_ID_BASE << transStr << endl;
                            return emptyAccs;
                        }
                        acc.accountId = accId;
                        while (transStr[i] != CLOSING_PAREN) {
                            string accAmtStr = extractPairCnt(i, transStr, CLOSING_PAREN);
                            if (accAmtStr == "" || !is_number(accAmtStr)) {
                                cout << INVALID_VOUT_CNT_BASE << " in " << transStr << " must be numeric." << endl;
                                return emptyAccs;
                            }
                            acc.amt = stoi(accAmtStr);
                            complete = true;
                            break;
                        }
                    }

                }
                accounts.push_back(acc);
                break;
            }

            else if (transStr[i] == ';') {
                i++;
                break;
            }

            else {
                cout << "Error: Missing (" << endl;
                return emptyAccs;
            }
        }
    }
    return accounts;
}

void scanToDelim(int &i, string transStr, char endingDelim) {
    while (transStr[i] != endingDelim) i++;
}

void trimWhiteSpace(int &i, string transStr) {
    while (isspace(transStr[i])) i++;
}

bool is_number(const std::string& s) {
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}
