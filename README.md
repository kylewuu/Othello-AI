# Self playing Othello AI:
This is the Othello board game recreated in C++ with an AI that users can play against.

This program can be played in three different game modes:
  1. The user will play against the pure Monte-Carlo Tree Search AI that does not have any additional heuristics
  2. The user can watch, step by step, MCTS play against MCTS w/heuristics for one round
  3. The user can quickly run a lot of tests where MCTS plays against MCTS w/heuristics for a set amount of rounds
When the program is first run, the user will have the option to input the set number of playouts. This is so the user can test many different values. However, the number of playouts that have been tested to play well is 10000. The user does not have to change this value as it is strictly to make testing easier.

The X acts as the black piece in Reversi and always moves first.
The O acts as the white piece in Reversi and always moves second.
The yellow numbers are the legal moves given the current board.


## Getting Started:
download and cd into the folder

then type in the following to compile the program

    g++ -o x Main.cpp Reversi.cpp Mct.cpp MctHeuristic.cpp

then use the following to run the program

    ./x

- - - -
Built With:
C++

Authors
Me (Kyle Wu)
