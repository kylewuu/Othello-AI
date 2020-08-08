#include "Reversi.h"
#include "Mct.h"
#include "MctHeuristic.h"
#include <cstdlib>
#include <ctime>

using namespace std;

Reversi::Reversi(void)
{

    main_loop();
};

void Reversi::print_intro()
{
    cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxx\n"
         << "x                         x\n"
         << "x         Reversi         x\n"
         << "x                         x\n"
         << "xxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n " << endl;

    if(!ai_vs_ai)
    {
        if (player == 1)
            cout << "You are \033[31mx\033[0m, you are going first\n\n";
        else if (player == 2)
            cout << "You are \033[36mO\033[0m, you are going second\n\n";
    }
    else
    {
        if (player == 1)
            cout << "Heuristic AI is \033[31mx\033[0m, it is going first\n\n";
        else if (player == 2)
            cout << "Heuristic AI is \033[36mO\033[0m, it is going second\n\n";
    }
    
}

void Reversi::init_boards()
{
    board = new int[64];
    legal_moves = new int[64];

    for (int i = 0; i < 64; i++)
    {
        board[i] = 0;
    }

    board[35] = 1;
    board[28] = 1;

    board[27] = 2;
    board[36] = 2;
}

void Reversi::clear_legal_moves()
{
    for (int i = 0; i < 64; i++)
    {
        legal_moves[i] = 0;
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

            cout << "\033[33m" << (board[(i * 8) + j] == 0 ? (legal_moves[(i * 8) + j] == 1 ? (((i * 8) + j > 9 ? " " : "  ") + std::to_string((i * 8) + j) + " \033[0m") : "    \033[0m") : (board[(i * 8) + j] == 1 ? " \033[31mx\033[0m  " : " \033[36mO\033[0m  ")) << ((j == 7) ? " " : " | ");
        }
        cout << "          ";

        // map board
        // for (int j = 0; j < 8; j++)
        // {

        //     cout << (legal_moves[(i * 8) + j] == 1 ? (((i * 8) + j > 9 ? " " : "  ") + std::to_string((i * 8) + j) + " ") : "    ") << ((j == 7) ? " " : " | ");
        // }

        // player board
        if (i != 7)
            cout << "\n-------------------------------------------------------";

        // map board
        // cout << "         ";
        // if (i != 7)
        //     cout << "-------------------------------------------------------";

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

bool Reversi::is_legal_move(string str)
{
    if (!is_int(str))
        return false;

    int int_input = stoi(str);

    for (int i = 0; i < 64; i++)
    {
        if (i == int_input && legal_moves[i] == 1)
        {

            return true;
        }
    }
    return false;
}

void Reversi::find_legal_moves()
{
    int opponent;
    int temp;
    bool piece_between;

    if (turn == 1)
        opponent = 2;
    else
        opponent = 1;

    for (int i = 0; i < 64; i++)
    {
        // cout << board[i];
        if (board[i] == turn)
        {
            // top left
            temp = i - 9;
            piece_between = false;
            while (temp < 64 && temp >= 0 && (temp + 1) % 8 != 0 && board[temp] == opponent)
            {
                piece_between = true;
                temp -= 9;
            }
            if (temp < 64 && temp >= 0 && board[temp] == 0 && (temp + 1) % 8 != 0 && piece_between)
                legal_moves[temp] = 1;

            // top
            temp = i - 8;
            piece_between = false;
            while (temp < 64 && temp >= 0 && board[temp] == opponent)
            {
                piece_between = true;
                temp -= 8;
            }
            if (temp < 64 && temp >= 0 && board[temp] == 0 && piece_between)
                legal_moves[temp] = 1;

            // top right
            temp = i - 7;
            piece_between = false;
            while (temp < 64 && temp >= 0 && (temp) % 8 != 0 && board[temp] == opponent)
            {
                piece_between = true;
                temp -= 7;
            }
            if (temp < 64 && temp >= 0 && board[temp] == 0 && (temp) % 8 != 0 && piece_between)
                legal_moves[temp] = 1;

            // right
            temp = i + 1;
            piece_between = false;
            while (temp < 64 && temp >= 0 && (temp) % 8 != 0 && board[temp] == opponent)
            {
                piece_between = true;
                temp += 1;
            }
            if (temp < 64 && temp >= 0 && board[temp] == 0 && (temp) % 8 != 0 && piece_between)
                legal_moves[temp] = 1;

            // bottom right
            temp = i + 9;
            piece_between = false;
            while (temp < 64 && temp >= 0 && (temp) % 8 != 0 && board[temp] == opponent)
            {
                piece_between = true;
                temp += 9;
            }
            if (temp < 64 && temp >= 0 && board[temp] == 0 && (temp) % 8 != 0 && piece_between)
                legal_moves[temp] = 1;

            // bottom
            temp = i + 8;
            piece_between = false;
            while (temp < 64 && temp >= 0 && board[temp] == opponent)
            {
                piece_between = true;
                temp += 8;
            }
            if (temp < 64 && temp >= 0 && board[temp] == 0 && piece_between)
                legal_moves[temp] = 1;

            // bottom left
            temp = i + 7;
            piece_between = false;
            while (temp < 64 && temp >= 0 && (temp + 1) % 8 != 0 && board[temp] == opponent)
            {
                piece_between = true;
                temp += 7;
            }
            if (temp < 64 && temp >= 0 && board[temp] == 0 && (temp + 1) % 8 != 0 && piece_between)
                legal_moves[temp] = 1;

            // left
            temp = i - 1;
            piece_between = false;
            while (temp < 64 && temp >= 0 && (temp + 1) % 8 != 0 && board[temp] == opponent)
            {
                piece_between = true;
                temp -= 1;
            }
            if (temp < 64 && temp >= 0 && board[temp] == 0 && (temp + 1) % 8 != 0 && piece_between)
                legal_moves[temp] = 1;
        }
    }
}

bool Reversi::check_for_end()
{

    bool legal_moves_flag = false;
    for (int i = 0; i < 64; i++)
    {
        if (legal_moves[i] == 1)
        {
            legal_moves_flag = true;
            return false;
        }
    }

    if (!legal_moves_flag)
    {
        if (turn == 1)
        {

            turn = 2;
            find_legal_moves();
            for (int i = 0; i < 64; i++)
            {
                if (legal_moves[i] == 1)
                {
                    cout << "\033[31mx\033[0m has no moves, \033[36mO\033[0m is going now.\n\n";
                    print_boards();
                    return false;
                }
            }
        }
        else
        {

            turn = 1;
            find_legal_moves();
            for (int i = 0; i < 64; i++)
            {
                if (legal_moves[i] == 1)
                {
                    cout << "\033[36mO\033[0m has no moves, \033[31mx\033[0m is going now.\n\n";
                    print_boards();
                    return false;
                }
            }
        }
    }

    for (int i = 0; i < 64; i++)
    {
        if (board[i] == 0)
        {
            cout << "No players can make anymore valid moves\n";
        }
    }

    return true;
}

int Reversi::check_winner()
{
    int x = 0;
    int o = 0;

    for (int i = 0; i < 64; i++)
    {
        if (board[i] == 1)
            x += 1;
        else if (board[i] == 2)
            o += 1;
    }

    cout << "\nx: " << x;
    cout << "\nO: " << o;
    if (x > o)
        return 1;
    else if (o > x)
        return 2;
    return 0;
}

void Reversi::make_move(string str) // need to add the flipping
{
    int int_input = stoi(str);

    int opponent;
    int temp;
    bool piece_between;

    if (turn == 1)
        opponent = 2;
    else
        opponent = 1;

    int i = int_input;

    // top left
    temp = i - 9;
    piece_between = false;
    while (temp < 64 && temp >= 0 && (temp + 1) % 8 != 0 && board[temp] == opponent)
    {
        piece_between = true;
        temp -= 9;
    }
    if (board[temp] == turn && (temp + 1) % 8 != 0 && piece_between)
    {

        temp = i - 9;
        while (temp < 64 && temp >= 0 && (temp + 1) % 8 != 0 && board[temp] == opponent)
        {
            board[temp] = turn;
            temp -= 9;
        }
    };

    // top
    temp = i - 8;
    piece_between = false;
    while (temp < 64 && temp >= 0 && board[temp] == opponent)
    {
        piece_between = true;
        temp -= 8;
    }
    if (board[temp] == turn && piece_between)
    {

        temp = i - 8;
        while (temp < 64 && temp >= 0 && board[temp] == opponent)
        {
            board[temp] = turn;
            temp -= 8;
        }
    };

    // top right
    temp = i - 7;
    piece_between = false;
    while (temp < 64 && temp >= 0 && (temp) % 8 != 0 && board[temp] == opponent)
    {
        piece_between = true;
        temp -= 7;
    }
    if (board[temp] == turn && (temp) % 8 != 0 && piece_between)
    {
        temp = i - 7;
        while (temp < 64 && temp >= 0 && (temp) % 8 != 0 && board[temp] == opponent)
        {
            board[temp] = turn;
            temp -= 7;
        }
    };

    // right
    temp = i + 1;
    piece_between = false;
    while (temp < 64 && temp >= 0 && (temp) % 8 != 0 && board[temp] == opponent)
    {
        piece_between = true;
        temp += 1;
    }
    if (board[temp] == turn && (temp) % 8 != 0 && piece_between)
    {
        temp = i + 1;
        while (temp < 64 && temp >= 0 && (temp) % 8 != 0 && board[temp] == opponent)
        {
            board[temp] = turn;
            temp += 1;
        }
    };

    // bottom right
    temp = i + 9;
    piece_between = false;
    while (temp < 64 && temp >= 0 && (temp) % 8 != 0 && board[temp] == opponent)
    {
        piece_between = true;
        temp += 9;
    }
    if (board[temp] == turn && (temp) % 8 != 0 && piece_between)
    {
        temp = i + 9;
        while (temp < 64 && temp >= 0 && (temp) % 8 != 0 && board[temp] == opponent)
        {
            board[temp] = turn;
            temp += 9;
        }
    };

    // bottom
    temp = i + 8;
    piece_between = false;
    while (temp < 64 && temp >= 0 && board[temp] == opponent)
    {
        piece_between = true;
        temp += 8;
    }
    if (board[temp] == turn && piece_between)
    {
        temp = i + 8;
        while (temp < 64 && temp >= 0 && board[temp] == opponent)
        {
            board[temp] = turn;
            temp += 8;
        }
    };

    // bottom left
    temp = i + 7;
    piece_between = false;
    while (temp < 64 && temp >= 0 && (temp + 1) % 8 != 0 && board[temp] == opponent)
    {
        piece_between = true;
        temp += 7;
    }
    if (board[temp] == turn && (temp + 1) % 8 != 0 && piece_between)
    {
        temp = i + 7;
        while (temp < 64 && temp >= 0 && (temp + 1) % 8 != 0 && board[temp] == opponent)
        {
            board[temp] = turn;
            temp += 7;
        }
    };

    // left
    temp = i - 1;
    piece_between = false;
    while (temp < 64 && temp >= 0 && (temp + 1) % 8 != 0 && board[temp] == opponent)
    {
        piece_between = true;
        temp -= 1;
    }
    if (board[temp] == turn && (temp + 1) % 8 != 0 && piece_between)
    {
        temp = i - 1;
        while (temp < 64 && temp >= 0 && (temp + 1) % 8 != 0 && board[temp] == opponent)
        {
            board[temp] = turn;
            temp -= 1;
        }
    };

    board[int_input] = turn;
    if (turn == 1)
        turn = 2;
    else
        turn = 1;
}

void Reversi::temp_make_random_move()
{

    int move = rand() % 64;
    ;
    while (legal_moves[move] == 0)
    {
        move = rand() % 64;
    }

    cout << "The AI chose: " << move << "\n";

    make_move(std::to_string(move));
}

void Reversi::read_input()
{
    // if player's turn
    if (turn == player)
    {
        if(!ai_vs_ai)
        {
            bool is_int_flag = false;
            bool is_valid_space_flag = false;
            if (turn == 2)
                cout << "o (blue): make a move: ";
            else if (turn == 1)
                cout << "x (red): make a move: ";
            cin >> input;
            is_valid_space_flag = is_legal_move(input);

            while (!is_valid_space_flag)
            {
                if (turn == 2)
                    cout << "o (white): make a valid move: ";
                else if (turn == 1)
                    cout << "x (black): make a valid move: ";
                cin >> input;
                is_valid_space_flag = is_legal_move(input);
            }
            cout << "\n";
            make_move(input);
        }
        else
        {
            cout << "It is the heuristic AI's turn\n";
            MctHeuristic ai{board, legal_moves, turn};
            int ai_input = ai.playout();
            make_move(std::to_string(ai_input));
        }
        
    }

    else
    {
        cout << "It is the MCTS's turn\n";
        Mct ai{board, legal_moves, turn};
        int ai_input = ai.playout();
        make_move(std::to_string(ai_input));
        // temp_make_random_move();
    }
}

void Reversi::main_loop()
{
    string ai_vs_ai_string;
    while(ai_vs_ai_string != "yes" && ai_vs_ai_string != "no" &&ai_vs_ai_string != "y" && ai_vs_ai_string != "n" && ai_vs_ai_string != "test")
    {
        cout << "Would you like to just watch two AI play against each other? (yes/no)";
        cin >> ai_vs_ai_string;
    }
    
    if(ai_vs_ai_string == "yes" || ai_vs_ai_string == "y")
    {
        cout << "The match will now begin between heuristic AI and pure Monte-Carlo Tree Search";
        ai_vs_ai = true;
    }
    else if (ai_vs_ai_string == "no" || ai_vs_ai_string == "n")
    {
        cout << "The match will now begin between you and pure Monte-Carlo Tree Search";
        ai_vs_ai = false;
    }
    else if(ai_vs_ai_string == "test")
    {
        ai_vs_ai = true;
        int mct_count = 0;
        int heuristic_count = 0;
        for(int j=0;j<100;j++)
        {
            turn = 1;
            std::srand((unsigned int)time(NULL)); // https://stackoverflow.com/questions/9459035/why-does-rand-yield-the-same-sequence-of-numbers-on-every-run
            // this was added because the same number was being generated on every run
            player = rand() % 2 + 1;
            // if(player == 1) ai = 2;
            // else ai = 1;
            // print_intro();
            init_boards();
            clear_legal_moves();
            find_legal_moves();
            // print_boards();

            while (!check_for_end())
            {
                read_input();
                clear_legal_moves();
                find_legal_moves();
                // print_boards();
            }

            cout << "Fini\n\n";
            int winner = check_winner();
            
            
            if(winner == player) heuristic_count ++;
            else mct_count ++;
        }
        cout << "\nMCTS had: "<<mct_count<< " wins\n";
        cout << "Heuristic AI had: "<<heuristic_count<< " wins\n";
    }
    
    turn = 1; // x always goes first
    std::srand((unsigned int)time(NULL)); // https://stackoverflow.com/questions/9459035/why-does-rand-yield-the-same-sequence-of-numbers-on-every-run
    // this was added because the same number was being generated on every run
    player = rand() % 2 + 1;
    // if(player == 1) ai = 2;
    // else ai = 1;
    print_intro();
    init_boards();
    clear_legal_moves();
    find_legal_moves();
    print_boards();

    while (!check_for_end())
    {
        read_input();
        clear_legal_moves();
        find_legal_moves();
        print_boards();
    }

    cout << "Fini\n\n";
    int winner = check_winner();
    
    if (winner == 1)
        cout << "\nx is the winner\n\n";
    if (winner == 2)
        cout << "\nO is the winner\n\n";
    if (winner == 0)
        cout << "\nThe match ended in a draw\n\n";
    
    if(winner == player) 
    {
        if(ai_vs_ai) cout <<"The heuristic AI won\n";
        else cout <<"The player won\n";
    }
    
    else if(winner != 0) cout <<"The MCTS won\n";
}