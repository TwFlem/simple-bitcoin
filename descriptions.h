#ifndef DESCRIPTIONS_H_
#define DESCRIPTIONS_H_

#include <string>

// Command descriptions
// File
const std::string F_CMD_DESC = "[F]ile:  Supply filename:<infilename>.  Read in a file of transactions.\n"
        "Any invalid transaction shall be identified with an error message to stderr, but not stored.\n"
        "Print an error message to stderr if the input file named cannot be opened.\n"
        "The message shall be “Error: file <infilename> cannot be opened for reading” on a single line,\n"
        "where <infilename> is the name provided as additional command input.\n";

// Transaction
const std::string T_CMD_DESC = "[T]ransaction: Supply Transaction:<see format below>\n"
        "Read in a single transaction in the format:\n"
        "<TransID>; M; (<TransID>, <vout>)^M; N; (<AcctID>, <amount>)^N\n"
        "Items in angle brackets are parameters, M and N are whole numbers, and caret M (or N)\n"
        "indicates M (or N) repetitions of the parenthesized pairs."
        "It shall be checked for validity against the ledger, and added if it is valid.\n"
        "If it is not valid, then do not add it to the ledger and print a message to stderr\n"
        "with the transaction number followed by a colon, a space, and the reason it is invalid on a single line.\n";

// Exit
const std::string E_CMD_DESC = "[E]xit:  Quit the program\n";

// Print
const std::string P_CMD_DESC = "[P]rint:  Print current ledger (all transactions in the order they were added)\n"
        "to stdout in the transaction format given below, one transaction per line.\n";

// Dump
const std::string D_CMD_DESC = "[D]ump:  Supply filename:<outfilename>.  Dump ledger to the named file.\n"
        "Print an error message to stderr if the output file named cannot be opened.\n"
        "The message shall be “Error: file <outfilename> cannot be opened for writing” on a single line,\n"
        "where <outfilename> is the name provided as additional command input.\n";
// Wipe
const std::string W_CMD_DESC = "[W]ipe:  Wipe the entire ledger to start fresh.\n";

// Interactive
const std::string I_CMD_DESC = "[I]nteractive: Toggle interactive mode. Start in non-interactive mode, where no command prompts are printed.\n"
        "Print command prompts and prompts for additional input in interactive mode,\n"
        "starting immediately (i.e., print a command prompt following the I command).\n";

// Verbose
const std::string V_CMD_DESC = "[V]erbose: Toggle verbose mode. Start in non-verbose mode.\n"
        "In verbose mode, print additional diagnostic information as you wish.\n"
        "At all times, output each transaction number as it is read in, followed by a colon, a space, and the result\n"
        "(“good” or “bad”).\n";

const std::string PROMPT_HELP = "type H or h for a list of available commands";

const std::string PROMPT_INTERACTION_ACTIVE = "Interactive mode activated:\n"
                                        "\t-Type a command.\n"
                                        "\t-Type H or h for a list of commands.\n"
                                        "\t-Type I or i to exit interactive mode.\n";

const std::string PROMPT_INTERACTION_NOT_ACTIVE = "Interactive mode deactivated:\n";

const std::string PROMPT_VERBOSE_ACTIVE = "Verbose mode activated:\n";

const std::string PROMPT_VERBOSE_NOT_ACTIVE = "Verbose mode deactivated:\n";

const std::string INVALID_ID_BASE = "Input has invalid transaction id: ";

const std::string ERR_TRANS_ID_TAKEN = "Error, the following transaction id has been taken: ";
const std::string ERR_TRANS_ID_DOES_NOT_EXIST = "Error, the following transaction id does not exist in the current ledger: ";
const std::string ERR_TRANS_GENERIC = "Error, the following transaction is invalid: ";
const std::string ERR_UTXO_INDEX_OOB = "UTXO index is out of bounds with previous accounts\n";
const std::string ERR_UTXO_ACC_MISMATCH = "Previous transaction and current transaction input/output mismatch: ";

void promptHelp(std::string);
void promptInteraction(bool);
void promptVerbose(bool);

#endif
