#include <string>
#include <iostream>

using namespace std;

class Reversi
{
    int a;
    int turn;
    int *board; // 0 = blank, 1 = player 1, 2 = player 2
    string input;

public:
    Reversi(void);
    void main_loop(void);

    void print_intro(void);
    void init_boards(void);
    void print_boards(void);

    bool is_int(string);
    bool is_valid_space(string);
    void make_move(string);
    void read_input(void);
};