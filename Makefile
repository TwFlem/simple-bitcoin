CC=g++
CFLAGS=-std=c++11
OPENSSL_INCLUDE=-I /usr/local/opt/openssl/include
OPENSSL_LIB=-L /usr/local/opt/openssl/lib

all: ledger

ledger: main.cpp ledgerCommands.cpp descriptions.cpp
	$(CC) $(CFLAGS) $(OPENSSL_LIB) -lssl -lcrypto $(OPENSSL_INCLUDE) main.cpp ledgerCommands.cpp descriptions.cpp ledger.cpp -o ledger

clean:
	rm ledger

