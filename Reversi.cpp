#include "Reversi.h"

using namespace std;

Reversi::Reversi(void)
{
    // print_intro();
    // init_boards();
    // print_boards();

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
    board = new int[64];

    for (int i = 0; i < 64; i++)
    {
        board[i] = 0;
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

            cout << (board[(i * 8) + j] == 0 ? " " : (board[(i * 8) + j] == 1 ? "x" : "O")) << ((j == 7) ? " " : " | ");
        }
        cout << "          ";

        // map board
        for (int j = 0; j < 8; j++)
        {

            cout << (board[(i * 8) + j] == 0 ? (((i * 8) + j > 9 ? " " : "  ") + std::to_string((i * 8) + j) + " ") : "    ") << ((j == 7) ? " " : " | ");
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

bool Reversi::is_int(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}

bool Reversi::is_valid_space(string str)
{
    if (!is_int(str))
        return false;

    int int_input = stoi(str);

    for (int i = 0; i < 64; i++)
    {
        if (i == int_input && board[i] == 0)
        {

            return true;
        }
    }
    return false;
}

void Reversi::make_move(string str)
{
    int int_input = stoi(str);

    board[int_input] = turn;
    if (turn == 1)
        turn = 2;
    else
        turn = 1;
}

void Reversi::read_input()
{
    bool is_int_flag = false;
    bool is_valid_space_flag = false;
    cout << "Make a move: ";
    cin >> input;
    is_valid_space_flag = is_valid_space(input);

    while (!is_valid_space_flag)
    {
        cout << "Make a valid move: ";
        cin >> input;
        is_valid_space_flag = is_valid_space(input);
    }
    cout << "\n";
    make_move(input);
}

void Reversi::main_loop()
{
    print_intro();
    init_boards();
    turn = 1;

    while (true)
    {
        read_input();
        print_boards();
    }
}