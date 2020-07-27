#include "Reversi.h"

using namespace std;

Reversi::Reversi(void)
{
    print_intro();
    init_boards();
    print_boards();

    main_loop();
};

void Reversi::print_intro()
{
    cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxx\n"
         << "x                         x\n"
         << "x         Reversi         x\n"
         << "x                         x\n"
         << "xxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n " << endl;
}

void Reversi::init_boards()
{
    player_board = new int[64];
    map_board = new int[64];

    for (int i = 0; i < 64; i++)
    {
        player_board[i] = 0;
        map_board[i] = 0;
    }
}

void Reversi::print_boards()
{
    for (int i = 0; i < 8; i++)
    {

        // player board
        cout << " ";
        for (int j = 0; j < 8; j++)
        {

            cout << (player_board[(i * 8) + j] == 0 ? " " : (player_board[(i * 8) + j] == 1 ? "x" : "O")) << ((j == 7) ? " " : " | ");
        }
        cout << "          ";

        // map board
        for (int j = 0; j < 8; j++)
        {

            cout << (player_board[(i * 8) + j] == 0 ? (((i * 8) + j > 9 ? " " : "  ") + std::to_string((i * 8) + j) + " ") : "    ") << ((j == 7) ? " " : " | ");
        }

        // player board
        if (i != 7)
            cout << "\n-------------------------------";

        // map board
        cout << "         ";
        if (i != 7)
            cout << "-------------------------------------------------------";

        cout << "\n";
    }
    cout << "\n";
}

void Reversi::main_loop()
{
}