CC=g++
CFLAGS=-std=c++11

all: ledger

ledger: main.cpp ledgerCommands.cpp descriptions.cpp
	$(CC) $(CFLAGS) main.cpp ledgerCommands.cpp descriptions.cpp ledger.cpp -o ledger

clean:
	rm ledger

