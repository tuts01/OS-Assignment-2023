To compile the program, use the "make" command as a Makefile has been included.

To run the program, ensure there is a text file named c_file with a valid list
of customers, and run the following command:
    ./cq m tc tw td ti
where
    m = The size of the customer queue
    tc = The periodic time for a customer to arrive in the queue
    tw = The time taken to serve a withdrawal
    td = The time taken to serve a deposit
    ti = The time taken to serve information
and each value entered is a positive integer.

If an invalid argument is entered, or the incorrect number of arguments, an
error message is printed along with the correct usage of the program.
If all arguments are valid, and c_file exists and is in the correct format, the
program should not output anything to the user. (I.e. no news is good news.)

To delete the executable and any object files use the "make clean" command.