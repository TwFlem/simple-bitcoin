#ifndef SIMPLE_BITCOIN_LEDGERCOMMANDS_H
#define SIMPLE_BITCOIN_LEDGERCOMMANDS_H

#include "ledger.h"

void help();
void file(std::string, bool, bool);
void transaction(std::string, bool, bool);
void dump(Ledger*, bool, bool);
void wipe(bool, bool);

#endif
