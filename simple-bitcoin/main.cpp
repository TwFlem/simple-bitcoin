#include <iostream>
#include "descriptions.h"
#include "ledgerCommands.h"

using namespace std;

int main() {
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
            file(input, interactive, verbose);
        } else if (input == "T" || input == "t") {
            transaction(input, interactive, verbose);
        } else if (input == "P" || input == "p") {
            print();
        } else if (input == "D" || input == "d") {
            dump(input, interactive, verbose);
        } else if (input == "W" || input == "w") {
            wipe(interactive, verbose);
        } else {
            promptHelp(input);
        }

        getline(cin, input);
    }

    return 0;
}