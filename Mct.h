#include <string>
#include <iostream>

using namespace std;

class Mct
{
    int initial_turn;
    int playouts;
    int *initial_board;
    int *initial_legal_moves;
    int player;

    int *board;
    int *legal_moves;
    int turn;

public:
    Mct(int *, int *, int, int);
    void make_move(void);
    int playout(void);
    bool check_for_end(void);
    void find_legal_moves(void);
    void clear_legal_moves(void);
    int check_winner(void);
    void print_boards(void);
    void make_first_move(int);
};