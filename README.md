# initial-matrix-command-line-tool

This is the initial version of my 'matrix comand line tool'. For a more complete version, please see [matrix command line tool](https://github.com/arteen1000/matrix-command-line-tool).

This program is capable of taking in dynamic user input, performing input validation, and using it to perform three basic matrix operations:

- scalar multiplication
- matrix addition
- matrix multiplication

After I had already completed the project, and was getting ready to add more operations, I realized that having the user input their row and column data manually took too much time, so I had the idea to allow them to input matrix data by row and have the program figure out their row and column data.

For that version, please the link above.

If you would still like to compile and use this version, you may do so by running the following steps in your terminal:

- `$ git clone https://github.com/arteen1000/initial-matrix-command-line-tool.git matrix-cli`
- `$ cd matrix-cli`
- `$ g++ -std=c++20 -Ofast *.cpp -o matrix`

After this, you may run the program at any time using:

- `./matrix`
