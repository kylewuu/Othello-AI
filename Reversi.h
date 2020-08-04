#include <string>
#include <iostream>

using namespace std;

class Reversi
{
    int a;
    int turn;
    int *board; // 0 = blank, 1 = player 1, 2 = player 2. 1=x=black 2=o=white
    int *legal_moves; // 0 = not legal, 1 = legal
    int player;
    int ai;
    string input;

public:
    Reversi(void);
    void main_loop(void);

    void print_intro(void);
    void init_boards(void);
    void print_boards(void);

    bool is_int(string);
    bool is_legal_move(string);
    void clear_legal_moves(void);
    void find_legal_moves(void);
    void make_move(string);
    void read_input(void);
    bool check_for_end(void);
    int check_winner(void);

    void temp_make_random_move(void);
};