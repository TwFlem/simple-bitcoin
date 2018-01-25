#include "descriptions.h"
#include <iostream>

using namespace std;

int main() {
    bool interactive = true;
    string input;
    getline(cin, input);

    while(input != "E" && input != "e") {

        // why can't i do switch statements with strings!
        if (input == "H" || input == "h") {
            help();
        }
        if (input == "I" || input == "i") {
            interactive = !interactive;
            promptInteraction(interactive);
        } else {
            promptHelp(input);
        }

        getline(cin, input);
    }

    return 0;
}