#ifndef SIMPLE_BITCOIN_LEDGERCOMMANDS_H
#define SIMPLE_BITCOIN_LEDGERCOMMANDS_H

#include "ledger.h"

void help();
void file(Ledger*, bool, bool);
void transaction(Ledger*, bool, bool);
void dump(Ledger*, bool, bool);
void balance(Ledger*, bool, bool);

#endif
