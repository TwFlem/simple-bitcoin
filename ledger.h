#ifndef SIMPLE_BITCOIN_LEDGER_H
#define SIMPLE_BITCOIN_LEDGER_H

#include <map>
#include <vector>
#include <string>
#include <unordered_map>


struct utxo {
    unsigned int transactionId;
    unsigned int index;
};
struct account {
    std::string accountId;
    unsigned int amt;
};
struct transaction {
    std::vector <utxo> utxos;
    std::vector <account> accounts;
};

class Ledger {

typedef std::unordered_map<unsigned int, transaction> transactionMap;

public:
    Ledger();
    Ledger(std::vector<transaction>);
    void addTransaction(unsigned int, transaction);
    void print();
    std::string getAllFmtTransactions();
private:
    std::vector<unsigned int> transactionkeys;
    transactionMap transactions;
    transaction findTransaction(unsigned int);
};

std::string fmtTrans(unsigned int, std::vector<utxo>, std::vector<account>);

#endif //SIMPLE_BITCOIN_LEDGER_H
