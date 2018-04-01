#ifndef SIMPLE_BITCOIN_LEDGERCOMMANDS_H
#define SIMPLE_BITCOIN_LEDGERCOMMANDS_H

#include <openssl/rsa.h>
#include <openssl/evp.h>
#include "ledger.h"

void help();
void file(Ledger*, bool, bool);
void transaction(Ledger*, bool, bool);
void dump(Ledger*, bool, bool);
void balance(Ledger*, bool, bool);
void output(Ledger*);
void readKeyFile(std::unordered_map<std::string, EVP_PKEY*>*, bool, bool);
void checkSignature(Ledger*, std::unordered_map<std::string, EVP_PKEY*>);

#endif
