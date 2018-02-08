#ifndef SIMPLE_BITCOIN_LEDGER_H
#define SIMPLE_BITCOIN_LEDGER_H

#define VALID_ID_LENGTH 8
#define SEMI_COLON ';'
#define COMMA ','
#define CLOSING_PAREN ')'

#include <map>
#include <vector>
#include <string>
#include <unordered_map>

struct utxo {
    std::string transactionId;
    unsigned int index;
};
struct account {
    std::string accountId;
    unsigned int amt;
    bool spent;
};
struct transaction{
    std::string id;
    std::vector <utxo> utxos;
    std::vector <account> accounts;
};

class Ledger {

typedef std::unordered_map<std::string, transaction> transactionMap;

public:
    Ledger();
    Ledger(std::vector<transaction>);
    bool addTransaction(transaction, bool);
    bool getTransaction(std::string, transaction&);
    bool ledgerHasId(std::string);
    unsigned int sumAccountBalances(std::vector<account>);
    void print();
    std::string getAllFmtTransactions();
    void wipe();
    int size();
    void balance(std::string);
private:
    std::vector<std::string> transactionKeys;
    transactionMap transactions;
    transaction findTransaction(unsigned int);
    bool validateId(transaction);
    bool validateInput(transaction);
    void markUtxoSpent(std::string, int);
};

std::string fmtTrans(std::string, std::vector<utxo>, std::vector<account>);
transaction parseTransaction(std::string);
std::string extractId(int&, std::string, char);
std::string extractPairCnt(int&, std::string, char);
std::vector<utxo> extractUtxoPairs(int&, std::string, int);
std::vector<account> extractAccountPairs(int&, std::string, int);
bool is_number(const std::string&);
void scanToDelim(int&, std::string, char);
void trimWhiteSpace(int&, std::string);
std::string idToLower(std::string);
bool isHex(const std::string);

#endif //SIMPLE_BITCOIN_LEDGER_H
