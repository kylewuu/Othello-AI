#include <string>
#include <iostream>

using namespace std;

class Reversi
{
    int a;
    int *player_board;
    int *map_board;

public:
    Reversi(void);
    void print_intro(void);
    void init_boards(void);
    void main_loop(void);
    void print_boards(void);
};