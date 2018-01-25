CC=g++
CFLAGS=-std=c++11

all: ledger

ledger: main.cpp ledgerCommands.cpp descriptions.cpp
	$(CC) $(CFLAGS) main.cpp ledgerCommands.cpp descriptions.cpp -o ledger

