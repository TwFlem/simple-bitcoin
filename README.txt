This is written in c++ and Requires c++11.

Running make will output a binary called ledger.

To run it, input the following into terminal:

make
./ledger

h/H will show a list of commands.

Known Bugs: Double spending has not been accounted for. For example, the ledger:
f2cea539; 0; ; 1; (Alice, 1000)
4787df35; 1; (f2cea539, 0); 3; (Bob, 150)(Alice, 845)(Gopesh, 5)
8789ff90; 1; (f2cea539, 0); 3; (Bob, 150)(Alice, 845)(Gopesh, 5)

is valid.

This is a result of UTXO not being marked as consumed. As a result, Balance does not
work correctly either. For the sake of having something, B/b outputs an account's
last transaction output.