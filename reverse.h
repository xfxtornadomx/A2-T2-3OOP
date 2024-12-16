//
// Created by Ahmed Atef on 16/12/2024.
//

#ifndef ASSIGNMENT_DEMO_2_REVERSE_H
#define ASSIGNMENT_DEMO_2_REVERSE_H
#include "BoardGame_Classes.h"

template <typename T>
class boardReverse : public Board<T>
{
public:
    boardReverse();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class palyerReverse : public Player<T>
{
public:
    palyerReverse(string name, T symbol);
    void getmove(int &x, int &y);
};

template <typename T>
class randReverse : public RandomPlayer<T>
{
public:
    randReverse(T symbol);
    void getmove(int &x, int &y);
};

//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;
template <typename T>
boardReverse<T>::boardReverse()
{
    this->rows = this->columns = 3;
    this->board = new char *[this->rows];
    for (int i = 0; i < this->rows; i++)
    {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++)
        {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool boardReverse<T>::update_board(int x, int y, T mark)
{
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0))
    {
        if (mark == 0)
        {
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else
        {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}

template <typename T>
void boardReverse<T>::display_board()
{
    for (int i = 0; i < this->rows; i++)
    {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++)
        {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

template <typename T>
bool boardReverse<T>::is_win()
{
    char current_player_symbol = (this->n_moves % 2 == 1) ? 'O' : 'X';
    for (int i = 0; i < this->rows; i++)
    {
        if ((this->board[i][0] != 0) &&
            (this->board[i][0] == this->board[i][1] &&
             this->board[i][1] == this->board[i][2]) &&
            (this->board[i][0] == current_player_symbol))
        {
            return true;
        }
    }

    for (int i = 0; i < this->columns; i++)
    {
        if ((this->board[0][i] != 0) &&
            (this->board[0][i] == this->board[1][i] &&
             this->board[1][i] == this->board[2][i]) &&
            (this->board[0][i] == current_player_symbol))
        {
            return true;
        }
    }

    if ((this->board[0][0] != 0) &&
        (this->board[0][0] == this->board[1][1] &&
         this->board[1][1] == this->board[2][2]) &&
        (this->board[0][0] == current_player_symbol))
    {
        return true;
    }

    if ((this->board[0][2] != 0) &&
        (this->board[0][2] == this->board[1][1] &&
         this->board[1][1] == this->board[2][0]) &&
        (this->board[0][2] == current_player_symbol))
    {
        return true;
    }

    return false;
}

template <typename T>
bool boardReverse<T>::is_draw()
{
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool boardReverse<T>::game_is_over()
{
    return is_win() || is_draw();
}

//--------------------------------------

template <typename T>
palyerReverse<T>::palyerReverse(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void palyerReverse<T>::getmove(int &x, int &y)
{
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

template <typename T>
randReverse<T>::randReverse(T symbol) : RandomPlayer<T>(symbol)
{
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void randReverse<T>::getmove(int &x, int &y)
{
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}
#endif //ASSIGNMENT_DEMO_2_REVERSE_H
