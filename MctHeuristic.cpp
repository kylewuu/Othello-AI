#include "MctHeuristic.h"
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

MctHeuristic::MctHeuristic(int *board_passed_in, int *legal_moves_passed_in, int turn_passed_in, int playouts_passed_in)
{
    initial_board = new int[64];
    initial_legal_moves = new int[64];
    // playouts = 8400 * 5; // 5 is the number of seconds, 8534 is how many moves can be made in a second
    playouts = playouts_passed_in;
    initial_turn = turn_passed_in;

    // temp variables
    turn = initial_turn;
    legal_moves = new int[64];
    board = new int[64];

    for (int i = 0; i < 64; i++)
    {
        initial_board[i] = board_passed_in[i];
        initial_legal_moves[i] = legal_moves_passed_in[i];
    }
    // for (int i = 0; i < 64; i++)
    // {
    //     if (i % 8 == 0)
    //         cout << "\n";
    //     cout << initial_legal_moves[i] << " ";
    // }
    // cout << "\n\n";
};

void MctHeuristic::make_move(void)
{
    int move = rand() % 64;
    while (legal_moves[move] == 0)
    {
        move = rand() % 64;
    }

    int int_input = move;

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

void MctHeuristic::clear_legal_moves()
{
    for (int i = 0; i < 64; i++)
    {
        legal_moves[i] = 0;
    }
}

void MctHeuristic::find_legal_moves()
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

bool MctHeuristic::check_for_end(void)
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
                    // cout << "\033[31mx\033[0m has no moves, \033[36mO\033[0m is going now.";
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
                    // cout << "\033[36mO\033[0m has no moves, \033[31mx\033[0m is going now.";
                    return false;
                }
            }
        }
    }

    for (int i = 0; i < 64; i++)
    {
        if (board[i] == 0)
        {
            // cout << "No players can make anymore valid moves\n";
        }
    }

    return true;
}

int MctHeuristic::check_winner()
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

    // cout << "\nx: " << x;
    // cout << "\nO: " << o;
    if (x > o)
        return 1;
    else if (o > x)
        return 2;
    return 0;
}

void MctHeuristic::print_boards()
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

void MctHeuristic::make_first_move(int move)
{

    int opponent;
    int temp;
    bool piece_between;

    if (turn == 1)
        opponent = 2;
    else
        opponent = 1;

    int i = move;

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

    board[move] = turn;
    if (turn == 1)
        turn = 2;
    else
        turn = 1;
}

int MctHeuristic::playout(void)
{

    float *scores = new float[64];

    int loss = -50;
    int win = 55;
    int draw = 25;
    int moves_count = 0;
    int dynamic_playouts = 0;
    float early_move_multiplier[64] = {
        1.5, 0.75, 1.25, 1.25, 1.25, 1.25, 0.75, 1.5,
        0.75, 0.75, 1.25, 1.25, 1.25, 1.25, 0.75, 0.75,
        1.25, 1.25, 1.5, 1.5, 1.5, 1.5, 1.25, 1.25,
        1.25, 1.25, 1.5, 1.5, 1.5, 1.5, 1.25, 1.25,
        1.25, 1.25, 1.5, 1.5, 1.5, 1.5, 1.25, 1.25,
        1.25, 1.25, 1.5, 1.5, 1.5, 1.5, 1.25, 1.25,
        0.75, 0.75, 1.25, 1.25, 1.25, 1.25, 0.75, 0.75,
        1.5, 0.75, 1.25, 1.25, 1.25, 1.25, 0.75, 1.5};

    float mid_move_multiplier[64] = {
        1.5, 0.75, 1.25, 1.25, 1.25, 1.25, 0.75, 1.5,
        0.75, 0.75, 1, 1, 1, 1, 0.75, 0.75,
        1.25, 1, 1, 1, 1, 1, 1, 1.25,
        1.25, 1, 1, 1, 1, 1, 1, 1.25,
        1.25, 1, 1, 1, 1, 1, 1, 1.25,
        1.25, 1, 1, 1, 1, 1, 1, 1.25,
        0.75, 0.75, 1, 1, 1, 1, 0.75, 0.75,
        1.5, 0.75, 1.25, 1.25, 1.25, 1.25, 0.75, 1.5};

    float late_move_multiplier[64] = {
        1.5, 1, 1.25, 1.25, 1.25, 1.25, 1, 1.5,
        1, 1, 1, 1, 1, 1, 1, 1,
        1.25, 1, 1, 1, 1, 1, 1, 1.25,
        1.25, 1, 1, 1, 1, 1, 1, 1.25,
        1.25, 1, 1, 1, 1, 1, 1, 1.25,
        1.25, 1, 1, 1, 1, 1, 1, 1.25,
        1, 1, 1, 1, 1, 1, 1, 1,
        1.5, 1, 1.25, 1.25, 1.25, 1.25, 1, 1.5};

    for (int i = 0; i < 64; i++)
    {
        scores[i] = 0;
        if (initial_legal_moves[i] == 1)
            moves_count += 1;
    }

    for (int i = 0; i < 64; i++)
    {
        dynamic_playouts = playouts / moves_count;
        if (initial_legal_moves[i] == 1)
        {
            auto start = high_resolution_clock::now(); // https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
            for (int j = 0; j < dynamic_playouts; j++)
            // for (int j = 0; j < playouts; j++)
            {
                // resetting the board
                turn = initial_turn;
                for (int k = 0; k < 64; k++)
                {
                    board[k] = initial_board[k];
                    legal_moves[k] = initial_legal_moves[k];
                }
                // int count = 0;
                make_first_move(i);

                // heuristics for checking how many moves the opponent now has
                for (int k = 0; k < 64; k++)
                {
                    if (legal_moves[k] == 1)
                        scores[i] -= (3 / dynamic_playouts);
                }
                // // also to detect if it reveals a corner
                if (legal_moves[0] == 1 || legal_moves[7] == 1 || legal_moves[63] == 1 || legal_moves[56] == 1)
                    scores[i] -= (20 / dynamic_playouts);

                while (!check_for_end())
                {

                    make_move();
                    clear_legal_moves();
                    find_legal_moves();
                }

                int winner = check_winner();
                if (winner == initial_turn)
                    scores[i] += win;
                else if (winner != 0)
                    scores[i] += loss;
                if (winner == 0)
                    scores[i] += draw;
            }

            // more heuristics to different spots in the board
            int pieces_count = 0;
            for (int k = 0; k < 64; k++)
            {
                if (initial_board[k] != 0)
                    pieces_count++;
            }

            if (pieces_count <= 15)
                scores[i] *= early_move_multiplier[i];
            else if (pieces_count <= 25)
                scores[i] *= mid_move_multiplier[i];
            else if (pieces_count <= 64)
                scores[i] *= late_move_multiplier[i];

            auto end = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(end - start);
            long duration_seconds = duration.count();
            // cout << dynamic_playouts << " playouts took " << duration_seconds << " milliseconds\n";
        }
    }

    int max = (playouts * loss) - 1 - 5;
    int input = 0;
    for (int i = 0; i < 64; i++)
    {
        if (initial_legal_moves[i] == 1)
        {
            max = scores[i];
            input = i;
        }
    }
    for (int i = 0; i < 64; i++)
    {
        // if (i % 8 == 0)
        //     cout << "\n";
        // cout << scores[i] << " ";
        if (initial_legal_moves[i] == 1 && scores[i] > max)
        {
            max = scores[i];
            input = i;
        }
    }

    cout << "\nThe heuristic AI chose: " << input << "\n";
    return input;
}