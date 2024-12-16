//
// Created by Ahmed Atef on 16/12/2024.
//

#ifndef ASSIGNMENT_DEMO_2_5X5X_O_H
#define ASSIGNMENT_DEMO_2_5X5X_O_H
#include "BoardGame_Classes.h"
#include <vector>
#include <algorithm>

template <typename T>
class X_O_5x5_Board : public Board<T>
{
private:
    int count_sequences(char player_symbol) const;

public:
    X_O_5x5_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool game_is_over();

    bool is_win();
    bool is_draw();

    int get_winner();
    void announce_winner();
};

template <typename T>
class X_O_5x5_Player : public Player<T>
{
public:
    X_O_5x5_Player(string name, T symbol);
    void getmove(int &x, int &y);
};

template <typename T>
class X_O_5x5_Random_Player : public RandomPlayer<T>
{
public:
    X_O_5x5_Random_Player(T symbol);
    void getmove(int &x, int &y);
};

//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <ctime>

using namespace std;

template <typename T>
X_O_5x5_Board<T>::X_O_5x5_Board()
{
    this->rows = this->columns = 5;
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
bool X_O_5x5_Board<T>::update_board(int x, int y, T mark)
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
void X_O_5x5_Board<T>::display_board()
{
    for (int i = 0; i < this->rows; i++)
    {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++)
        {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << (this->board[i][j] ? this->board[i][j] : '.') << " |";
        }
        cout << "\n----------------------------------------------------";
    }
    cout << endl;
}

template <typename T>
int X_O_5x5_Board<T>::count_sequences(char player_symbol) const
{
    int sequence_count = 0;

    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j <= this->columns - 3; j++)
        {
            if (this->board[i][j] == player_symbol &&
                this->board[i][j + 1] == player_symbol &&
                this->board[i][j + 2] == player_symbol)
            {
                sequence_count++;
            }
        }
    }

    for (int i = 0; i <= this->rows - 3; i++)
    {
        for (int j = 0; j < this->columns; j++)
        {
            if (this->board[i][j] == player_symbol &&
                this->board[i + 1][j] == player_symbol &&
                this->board[i + 2][j] == player_symbol)
            {
                sequence_count++;
            }
        }
    }

    for (int i = 0; i <= this->rows - 3; i++)
    {
        for (int j = 0; j <= this->columns - 3; j++)
        {
            if (this->board[i][j] == player_symbol &&
                this->board[i + 1][j + 1] == player_symbol &&
                this->board[i + 2][j + 2] == player_symbol)
            {
                sequence_count++;
            }
        }
    }

    for (int i = 0; i <= this->rows - 3; i++)
    {
        for (int j = 2; j < this->columns; j++)
        {
            if (this->board[i][j] == player_symbol &&
                this->board[i + 1][j - 1] == player_symbol &&
                this->board[i + 2][j - 2] == player_symbol)
            {
                sequence_count++;
            }
        }
    }

    return sequence_count;
}

template <typename T>
bool X_O_5x5_Board<T>::game_is_over()
{
    if (this->n_moves == 24)
    {
        announce_winner();
        return true;
    }
    return false;
}

template <typename T>
void X_O_5x5_Board<T>::announce_winner()
{
    if (this->n_moves == 24)
    {
        int x_sequences = count_sequences('X');
        int o_sequences = count_sequences('O');

        cout << "\nFinal Score after 24 moves:" << endl;
        cout << "Player X: " << x_sequences << " three-in-a-row sequences" << endl;
        cout << "Player O: " << o_sequences << " three-in-a-row sequences" << endl;

        if (x_sequences > o_sequences)
        {
            cout << "\nPlayer X is the winner!" << endl;
        }
        else if (o_sequences > x_sequences)
        {
            cout << "\nPlayer O is the winner!" << endl;
        }
        else
        {
            cout << "\nIt's a draw!" << endl;
        }
    }
}

template <typename T>
bool X_O_5x5_Board<T>::is_win()
{
    return false;
}

template <typename T>
bool X_O_5x5_Board<T>::is_draw()
{
    if (this->n_moves == 24)
    {
        int x_sequences = count_sequences('X');
        int o_sequences = count_sequences('O');
        return (x_sequences == o_sequences);
    }
    return false;
}

template <typename T>
int X_O_5x5_Board<T>::get_winner()
{
    if (this->n_moves == 24)
    {
        int x_sequences = count_sequences('X');
        int o_sequences = count_sequences('O');

        if (x_sequences > o_sequences)
            return 1;
        if (o_sequences > x_sequences)
            return 2;
    }
    return 0;
}

template <typename T>
X_O_5x5_Player<T>::X_O_5x5_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void X_O_5x5_Player<T>::getmove(int &x, int &y)
{
    cout << "\nPlease enter your move x and y (0 to 4) separated by spaces: ";
    cin >> x >> y;
}

template <typename T>
X_O_5x5_Random_Player<T>::X_O_5x5_Random_Player(T symbol) : RandomPlayer<T>(symbol)
{
    this->dimension = 5;
    this->name = symbol;
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void X_O_5x5_Random_Player<T>::getmove(int &x, int &y)
{
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}

#endif //ASSIGNMENT_DEMO_2_5X5X_O_H
