#include <iostream>
#include <vector>
#include "descriptions.h"
#include "ledger.h"
#include "ledgerCommands.h"

using namespace std;

void insertFakeTrans(Ledger* ledger);

int main() {
    Ledger* ledger = new Ledger();
    bool interactive = false;
    bool verbose = false;
    string input;

    insertFakeTrans(ledger);

    getline(cin, input);


    while(input != "E" && input != "e") {

        // why can't i do switch statements with strings!
        if (input == "H" || input == "h") {
            help();
        } else if (input == "I" || input == "i") {
            interactive = !interactive;
            promptInteraction(interactive);
        } else if (input == "V" || input == "v") {
            verbose = !verbose;
            promptVerbose(verbose);
        } else if (input == "F" || input == "f") {
            file(input, interactive, verbose);
        } else if (input == "T" || input == "t") {
            transaction(input, interactive, verbose);
        } else if (input == "P" || input == "p") {
            ledger->print();
        } else if (input == "D" || input == "d") {
            dump(ledger, interactive, verbose);
        } else if (input == "W" || input == "w") {
            wipe(interactive, verbose);
        } else {
            promptHelp(input);
        }

        getline(cin, input);
    }

    return 0;
}

void insertFakeTrans(Ledger* ledger) {
    vector <utxo> utxos;
    vector <account> accounts;

    utxo tempU = {
            12345,
            0
    };
    utxo tempV = {
            12346,
            0
    };

    account tempA = {
            "lol",
            12
    };
    account tempB = {
            "lol1",
            12
    };
    account tempC = {
            "lol2",
            12
    };

    utxos.push_back(tempU);
    utxos.push_back(tempV);
    accounts.push_back(tempA);
    accounts.push_back(tempB);
    accounts.push_back(tempC);

    struct transaction trans = {
            utxos,
            accounts
    };

    ledger->addTransaction(1, trans);
    ledger->addTransaction(2, trans);
    ledger->addTransaction(3, trans);
    ledger->addTransaction(4, trans);
    ledger->addTransaction(5, trans);
}
