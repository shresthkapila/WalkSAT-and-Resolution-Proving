Fast Implementations of WalkSAT and Resolution Proving

* How to compile the files:

=> Setting the command line at appropriate directory containing all files.

1. Running the python file { main.py } (that is origin version of WalkSAT and prover theorem in logic.py)
     => simply running on the terminal 
        (command line)  $ python3 main.py

2. Running the c++ file (that is the efficient version of WalkSAT and prover theorem)
    => Files needed = ( main.cpp, walksat.h, walksat.cpp, propositionalTP.h, propositionalTP.cpp)

    Also, created a Makefile, that contains all the commands for compiling the files. Simply doing 'make' on terminal will compile the files. 

    => (command line)  $ make
                       $ ./app

    After doing 'make', it will create an executable file that is app ( that is run by ./app )


Therefore after compiling either python or c++ files, you will get the option of choosing which algorithm to run (Choose 1 or 2) and then continue....


