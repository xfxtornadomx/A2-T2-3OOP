//
// Created by Ahmed Atef on 16/12/2024.
//

#ifndef ASSIGNMENT_DEMO_2_SUS_H
#define ASSIGNMENT_DEMO_2_SUS_H
#include "BoardGame_Classes.h"

int total_game_n_moves;
template <typename T>
class boardSUS : public Board<T>
{
public:
    boardSUS();
    bool **visited;
    bool update_board(int x, int y, T symbol);
    bool is_draw();
    bool is_win();
    bool game_is_over();
    int player1_score;
    int player2_score;
    void display_board();
};

template <typename T>
class playerSUS : public Player<T>
{
public:
    playerSUS(string name, T symbol);
    void getmove(int &x, int &y);
};

template <typename T>
class randSUS : public RandomPlayer<T>
{
public:
    randSUS(T symbol);
    void getmove(int &x, int &y);
};

//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

template <typename T>
boardSUS<T>::boardSUS()
{
    this->rows = this->columns = 3;
    this->board = new char *[this->rows];
    this->visited = new bool *[this->rows];

    player1_score = 0;
    player2_score = 0;

    for (int i = 0; i < this->rows; i++)
    {
        this->board[i] = new char[this->columns];
        this->visited[i] = new bool[this->columns];
        for (int j = 0; j < this->columns; j++)
        {
            this->visited[i][j] = false;
            this->board[i][j] = ' ';
        }
    }
    total_game_n_moves = 0;
    this->n_moves = 0;
}

template <typename T>
bool boardSUS<T>::update_board(int x, int y, T mark)
{

    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns)
    {
        return false;
    }

    if (this->board[x][y] != ' ' && mark != ' ')
    {
        return false;
    }

    if (mark == ' ')
    {
        this->n_moves--;
        total_game_n_moves--;
        this->board[x][y] = ' ';
    }
    else
    {
        this->n_moves++;
        total_game_n_moves++;
        this->board[x][y] = toupper(mark);
    }

    for (int i = 0; i < this->rows; i++)
    {
        string row_str = string(1, this->board[i][0]) + string(1, this->board[i][1]) + string(1, this->board[i][2]);
        if (!visited[i][1] && row_str == "SUS" && this->board[i][0] != ' ')
        {
            visited[i][1] = true;
            (mark == 'S') ? player1_score++ : (mark == 'U') ? player2_score++
                                                            : player2_score + 0;
        }
    }
    for (int i = 0; i < this->columns; i++)
    {
        string col_str = string(1, this->board[0][i]) + string(1, this->board[1][i]) + string(1, this->board[2][i]);
        if (!visited[1][i] && col_str == "SUS" && this->board[0][i] != ' ')
        {
            visited[1][i] = true;
            (mark == 'S') ? player1_score++ : (mark == 'U') ? player2_score++
                                                            : player2_score + 0;
        }
    }

    if (!visited[1][1])
    {
        string diag1 = string(1, this->board[0][0]) + string(1, this->board[1][1]) + string(1, this->board[2][2]);
        string diag2 = string(1, this->board[0][2]) + string(1, this->board[1][1]) + string(1, this->board[2][0]);

        if ((diag1 == "SUS" && this->board[0][0] != ' ') ||
            (diag2 == "SUS" && this->board[0][2] != ' '))
        {
            visited[1][1] = true;
            (mark == 'S') ? player1_score++ : (mark == 'U') ? player2_score++
                                                            : player2_score + 0;
        }
    }

    return true;
}

template <typename T>
void boardSUS<T>::display_board()
{
    cout << "\n+++++++++++++++++++++++++++++";
    for (int i = 0; i < this->rows; i++)
    {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++)
        {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n+++++++++++++++++++++++++++++";
    }
    cout << endl;
}

template <typename T>
bool boardSUS<T>::is_win()
{
    if (total_game_n_moves == 9)
    {
        if (player1_score > player2_score)
        {
            cout << "Player 1 wins!\n";
            return true;
        }
        else if (player2_score > player1_score)
        {
            cout << "Player 2 wins!\n";
            return true;
        }
    }
    return false;
}
template <typename T>
bool boardSUS<T>::is_draw()
{
    return total_game_n_moves == 9 && player1_score == player2_score;
}

template <typename T>
bool boardSUS<T>::game_is_over()
{
    return is_win() || is_draw();
}

template <typename T>
playerSUS<T>::playerSUS(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void playerSUS<T>::getmove(int &x, int &y)
{
    if (total_game_n_moves == 10)
    {
        x = 1;
        y = 1;
        return;
    }

    do
    {
        cout << "\nEnter move coordinates (row column): ";
        cin >> x >> y;
    } while (x < 0 || x > 2 || y < 0 || y > 2);
}

template <typename T>
randSUS<T>::randSUS(T symbol) : RandomPlayer<T>(symbol)
{
    this->dimension = 3;
    this->name = symbol;
    srand(time(nullptr));
}

template <typename T>
void randSUS<T>::getmove(int &x, int &y)
{
    do
    {
        x = rand() % this->dimension;
        y = rand() % this->dimension;
    } while (x < 0 || x > 2 || y < 0 || y > 2);
}
#endif //ASSIGNMENT_DEMO_2_SUS_H
