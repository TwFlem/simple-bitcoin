#ifndef DESCRIPTIONS_H_
#define DESCRIPTIONS_H_

#include <string>

// Command descriptions
// File
const std::string F_CMD_DESC = "[F]ile:  Supply filename:<infilename>.  Read in a file of transactions.\n";

// Transaction
const std::string T_CMD_DESC = "[T]ransaction: Supply Transaction:<see format below>\n"
        "Read in a single transaction in the format:\n"
        "<TransID>; M; (<TransID>, <vout>)^M; N; (<AcctID>, <amount>)^N\n"
        "Items in angle brackets are parameters, M and N are whole numbers, and caret M (or N)\n"
        "indicates M (or N) repetitions of the parenthesized pairs."
        "It shall be checked for validity against the ledger, and added if it is valid.\n";

// Exit
const std::string E_CMD_DESC = "[E]xit:  Quit the program\n";

// Print
const std::string P_CMD_DESC = "[P]rint:  Print current ledger (all transactions in the order they were added)\n";

// Dump
const std::string D_CMD_DESC = "[D]ump:  Supply filename:<outfilename>.  Dump the ledger to the named file.\n";
// Wipe
const std::string W_CMD_DESC = "[W]ipe:  Wipe the entire ledger to start fresh.\n";

// Interactive
const std::string I_CMD_DESC = "[I]nteractive: Toggle interactive mode. Start in non-interactive mode, where no command prompts are printed.\n"
        "Prints command prompts and prompts for additional input.\n";

// Verbose
const std::string V_CMD_DESC = "[V]erbose: Toggle verbose mode. Start in non-verbose mode.\n"
        "In verbose mode, additional diagnostic information is printed.\n"
        "At all times, each transaction number is output as it is read in, followed by a colon, a space, and the result\n"
        "(“good” or “bad”).\n";
// Balance
const std::string B_CMD_DESC = "[B]alance: Get the balance of an account by account id.\n";

const std::string PROMPT_HELP = "type H or h for a list of available commands";

const std::string PROMPT_INTERACTION_ACTIVE = "Interactive mode activated:\n"
                                        "\t-Type a command.\n"
                                        "\t-Type H or h for a list of commands.\n"
                                        "\t-Type I or i to exit interactive mode.\n";

const std::string PROMPT_INTERACTION_NOT_ACTIVE = "Interactive mode deactivated:\n";

const std::string PROMPT_VERBOSE_ACTIVE = "Verbose mode activated:\n";

const std::string PROMPT_VERBOSE_NOT_ACTIVE = "Verbose mode deactivated:\n";

const std::string INVALID_ID_BASE = "Input has invalid transaction id: ";
const std::string INVALID_ACC_ID_BASE = "Input has invalid account id: ";
const std::string INVALID_UTXO_CNT_BASE = "Input has invalid UTXO count: ";
const std::string INVALID_VOUT_CNT_BASE = "Input has invalid Account pair count: ";

const std::string ERR_TRANS_ID_TAKEN = "Error, the following transaction id has been taken: ";
const std::string ERR_TRANS_ID_DOES_NOT_EXIST = "Error, the following transaction id does not exist in the current ledger: ";
const std::string ERR_TRANS_GENERIC = "Error, the following transaction is invalid: ";
const std::string ERR_UTXO_INDEX_OOB = "UTXO index is out of bounds with previous accounts\n";
const std::string ERR_UTXO_ACC_MISMATCH = "Previous transaction and current transaction input/output mismatch: ";

void promptHelp(std::string);
void promptInteraction(bool);
void promptVerbose(bool);

#endif
