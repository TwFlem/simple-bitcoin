#include <iostream>
#include <vector>
#include "descriptions.h"
#include "ledger.h"
#include "ledgerCommands.h"

using namespace std;

int main() {
    Ledger* ledger = new Ledger();
    bool interactive = false;
    bool verbose = false;
    string input;

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
            balance(ledger, verbose, interactive);
        } else {
            promptHelp(input);
        }

        if (interactive) cout << "Type a command: ";
        getline(cin, input);
    }

    return 0;
}