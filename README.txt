This is written in c++ and is compiled using g++.

Running make will output a binary called ledger.

To run it, input the following into terminal:

make
./ledger

To recompile, run "make clean" and repeat the commands above.

h/H will show a list of commands.

Notes:

The original intent on reading from a [F]ile with a single incorrect
transaction was to reject everything from the file and wipe the ledger.
This was changed because it may make testing difficult.

Invalid single [T]ransactions do not wipe the history of the ledger.

Errors from running any command are always printed to cerr- regardless of whether
verbose mode is off or on. The only things that are printed using [V]erbose are
<transid>: good and <transid>: bad as each transaction is added to the ledger.

Known Bugs: None that I know of.
