#include <iostream>
#include "descriptions.h"

void promptHelp(std::string input) {
    std::cout << std::endl;
    std::cout << "Error: \"" << input << "\" is not a valid input" << std::endl;
    std::cout << PROMPT_HELP << std::endl;
}

void promptInteraction(bool interactive) {
    std::cout << std::endl;
    if (interactive) std::cout << PROMPT_INTERACTION_ACTIVE << std::endl;
    else std::cout << PROMPT_INTERACTION_NOT_ACTIVE << std::endl;
}

void promptVerbose(bool verbose) {
    std::cout << std::endl;
    if (verbose) std::cout << PROMPT_VERBOSE_ACTIVE << std::endl;
    else std::cout << PROMPT_VERBOSE_NOT_ACTIVE << std::endl;
}
