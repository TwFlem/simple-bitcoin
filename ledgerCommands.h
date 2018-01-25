#ifndef SIMPLE_BITCOIN_LEDGERCOMMANDS_H
#define SIMPLE_BITCOIN_LEDGERCOMMANDS_H

void help();
void file(std::string, bool, bool);
void transaction(std::string, bool, bool);
void print();
void dump(std::string, bool, bool);
void wipe(bool, bool);

#endif
