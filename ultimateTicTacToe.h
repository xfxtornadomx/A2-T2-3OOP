//
// Created by Ahmed Atef on 15/12/2024.
//

#ifndef ASSIGNMENT_DEMO_2_ULTIMATETICTACTOE_H
#define ASSIGNMENT_DEMO_2_ULTIMATETICTACTOE_H
#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <ctime>
// for toupper()
using namespace std;
template <typename T>
class X_O_Board:public Board<T> {
public:
    X_O_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    T** get_board() { return this->board; }

};

template <typename T>
class X_O_Player : public Player<T> {
public:
    X_O_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class X_O_Random_Player : public RandomPlayer<T>{
public:
    X_O_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
X_O_Board<T>::X_O_Board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool X_O_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
            cout << "Please enter valid coordinates" << endl;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void X_O_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool X_O_Board<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)) {
            return true;
        }
    }

    // Check diagonals
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
        return true;
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool X_O_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool X_O_Board<T>::game_is_over() {
    return is_win() || is_draw();
}



template <typename T>
class ultimateTicTacToe : public Board<T> {
private:
    X_O_Board<T>* subBoards[3][3];
    T ultimateBoard[3][3];

public:
    ultimateTicTacToe() {
        this->rows = 3;
        this->columns = 3;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                subBoards[i][j] = new X_O_Board<T>();
                ultimateBoard[i][j] = ' ';
            }
        }
        this->n_moves = 0;
    }

    bool update_board(int x, int y, T symbol) override {
        if (x < 0 || x >= 9 || y < 0 || y >= 9) {
            cout << "Invalid move. Coordinates should be between 0 and 8" << endl;
            return false;
        }
        int ultimateX = x / 3;
        int ultimateY = y / 3;
        int subX = x % 3;
        int subY = y % 3;

        if (ultimateBoard[ultimateX][ultimateY] != ' ') {
            cout << "This board is already won by Player " << ultimateBoard[ultimateX][ultimateY] << ". Please choose another board" << endl;
            return false;
        }

        if (subBoards[ultimateX][ultimateY]->update_board(subX, subY, symbol)) {
            if (subBoards[ultimateX][ultimateY]->is_win()) {
                ultimateBoard[ultimateX][ultimateY] = symbol;
            }
            this->n_moves++;
            return true;
        }
        return false;
    }

    void display_board() override {
        for (int i = 0; i < 3; i++) {
            for (int k = 0; k < 3; k++) {
                for (int j = 0; j < 3; j++) {
                    for (int l = 0; l < 3; l++) {
                        cout << subBoards[i][j]->get_board()[k][l] << " ";
                    }
                    cout << " | ";
                }
                cout << endl;
            }
            cout << "-----------------------------" << endl;
        }
    }

    bool is_win() override {
        for (int i = 0; i < 3; ++i) {
            if ((ultimateBoard[i][0] == ultimateBoard[i][1] && ultimateBoard[i][1] == ultimateBoard[i][2] && ultimateBoard[i][0] != ' ') ||
                (ultimateBoard[0][i] == ultimateBoard[1][i] && ultimateBoard[1][i] == ultimateBoard[2][i] && ultimateBoard[0][i] != ' ')) {
                return true;
            }
        }
        if ((ultimateBoard[0][0] == ultimateBoard[1][1] && ultimateBoard[1][1] == ultimateBoard[2][2] && ultimateBoard[0][0] != ' ') ||
            (ultimateBoard[0][2] == ultimateBoard[1][1] && ultimateBoard[1][1] == ultimateBoard[2][0] && ultimateBoard[0][2] != ' ')) {
            return true;
        }
        return false;
    }

    bool is_draw() override {
        if (this->n_moves == 81 && !is_win()) {
            return true;
        }
        return false;
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }

    T** get_board() {
        return this->board;
    }

    ~ultimateTicTacToe() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                delete subBoards[i][j];
            }
        }
    }
};
template <typename T>
class ultimateTicTacToePlayer : public Player<T> {
public:
    ultimateTicTacToePlayer(string name, T symbol) : Player<T>(name, symbol) {}

    void getmove(int& x, int& y) {
        int smallX, smallY;
        cout << "\n" << this->name << ", please enter your move (big board x, big board y, small board cell x, small board cell y): ";
        cin >> x >> y >> smallX >> smallY;
        x = x * 3 + smallX;
        y = y * 3 + smallY;
    }
};
template <typename T>
class ultimateTicTacToeRandomPlayer : public RandomPlayer<T> {
public:
    ultimateTicTacToeRandomPlayer(T symbol) : RandomPlayer<T>(symbol) {
        srand(static_cast<unsigned int>(time(0)));
        this->name = symbol;
    }

    void getmove(int& x, int& y) override {
        int bigX = rand() % 3;
        int bigY = rand() % 3;
        int smallX = rand() % 3;
        int smallY = rand() % 3;
        x = bigX * 3 + smallX;
        y = bigY * 3 + smallY;
    }
};



#endif //ASSIGNMENT_DEMO_2_ULTIMATETICTACTOE_H
