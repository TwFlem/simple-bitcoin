#include <iostream>
#include "descriptions.h"

void promptHelp(std::string input) {
    std::cout << std::endl;
    std::cout << "Error: \"" << input << "\" is not a valid input" << std::endl;
    std::cout << PROMPT_HELP << std::endl;
}

void promptInteraction(bool interactive) {
    std::cout << std::endl;
    if (interactive) std::cout << PROMPT_INTERACTION << std::endl;
}
