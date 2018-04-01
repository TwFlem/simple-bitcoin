#include <iostream>
#include <vector>
#include <map>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include "descriptions.h"
#include "ledger.h"
#include "ledgerCommands.h"

using namespace std;

void initializeLcrypto();
void cleanLcrypto();

int main() {
    Ledger* ledger = new Ledger();
    unordered_map<string, EVP_PKEY*> accCryptoKeys = {};
    bool interactive = false;
    bool verbose = false;
    string input;

    initializeLcrypto();

    getline(cin, input);


    while(input != "E" && input != "e") {
        if (input == "H" || input == "h") {
            help();
        } else if (input == "I" || input == "i") {
            interactive = !interactive;
            promptInteraction(interactive);
        } else if (input == "V" || input == "v") {
            verbose = !verbose;
            promptVerbose(verbose);
        } else if (input == "F" || input == "f") {
            file(ledger, interactive, verbose);
        } else if (input == "T" || input == "t") {
            transaction(ledger, interactive, verbose);
        } else if (input == "P" || input == "p") {
            ledger->print();
        } else if (input == "D" || input == "d") {
            dump(ledger, interactive, verbose);
        } else if (input == "W" || input == "w") {
            ledger->wipe();
        } else if (input == "B" || input == "b") {
            balance(ledger, interactive, verbose);
        } else if (input == "O" || input == "o") {
            output(ledger);
        } else if (input == "R" || input == "r") {
            readKeyFile(&accCryptoKeys, interactive, verbose);
        } else if (input == "C" || input == "c") {
            checkSignature(ledger, accCryptoKeys);
        } else {
            promptHelp(input);
        }

        if (interactive) cout << "Type a command: ";
        getline(cin, input);
    }

    cleanLcrypto();

    return 0;
}

void initializeLcrypto() {
    /* Load the human readable error strings for libcrypto */
    ERR_load_crypto_strings();

    /* Load all digest and cipher algorithms */
    OpenSSL_add_all_algorithms();

    /* Load config file, and other important initialisation */
    OPENSSL_config(NULL);
}

void cleanLcrypto() {
    /* Removes all digests and ciphers */
    EVP_cleanup();

    /* if you omit the next, a small leak may be left when you make use of the BIO (low level API) for e.g. base64 transformations */
    CRYPTO_cleanup_all_ex_data();

    /* Remove error strings */
    ERR_free_strings();
}
