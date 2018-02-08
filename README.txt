This is written in c++ and is compiled using g++.

Running make will output a binary called ledger.

To run it, input the following into terminal:

make
./ledger

To recompile, run make clean and repeat the commands above.

h/H will show a list of commands.

Notes:

When reading in a [F]ile, if any transaction is invalid, then none of the transactions
are accepted prior to the invalid transaction are kept. Invalid single [T]ransactions
do not wipe the history of the ledger.

Errors from running any command are always printed to cerr- regardless of whether
verbose mode is off or on. The only things that are printed using [V]erbose are
<transid>: good and <transid>: bad as each transaction is added to the ledger.

Although not stated explicitly, Double spending has been accounted for.

For example, the ledger:
f2cea539; 0; ; 1; (Alice, 1000)
4787df35; 1; (f2cea539, 0); 3; (Bob, 150)(Alice, 845)(Gopesh, 5)
8789ff90; 1; (f2cea539, 0); 3; (Bob, 150)(Alice, 845)(Gopesh, 5)

will not be valid since (Alice, 1000) has already been consumed once.

Known Bugs: None that I know of.
