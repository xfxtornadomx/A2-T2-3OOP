#ifndef ASSIGNMENT_DEMO_2_PYRAMIDBOARD_H
#define ASSIGNMENT_DEMO_2_PYRAMIDBOARD_H

#include <iostream>
#include "BoardGame_Classes.h"

using namespace std;

template <typename T>
class pyramidXO : public Board<T> {
public:
    pyramidXO() {
        this->rows = 3;
        this->columns = 5;

        this->board = new T*[this->rows];
        for (int i = 0; i < this->rows; ++i) {
            this->board[i] = new T[this->columns];
            for (int j = 0; j < this->columns; ++j) {
                this->board[i][j] = ' ';
            }
        }

        this->n_moves = 0;
    }

    int getRows() const {
        return this->rows;
    }

    int getColumns() const {
        return this->columns;
    }

    T getBoardValue(int x, int y) const {
        return this->board[x][y];
    }

    void display_board() override {
        for (int row = 0; row < this->rows; ++row) {
            int spaces = this->rows - row - 1;
            cout << string(spaces, ' ');
            for (int col = 0; col < this->columns; ++col) {
                if (col <= row * 2) {
                    cout << "(" << row << "," << col << ")" << this->board[row][col];
                    if (col < row * 2) cout << " ";
                } else {
                    cout << "  ";
                }
            }
            cout << endl;
        }
    }
    bool update_board(int x, int y, T symbol) override {
        if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || y > x * 2) {
            cout << "Invalid move" << endl;
            return false;
        }
        if (this->board[x][y] != ' ') {
            cout << "Cell already occupied" << endl;
            return false;
        }
        this->board[x][y] = symbol;
        this->n_moves++;
        return true;
    }

    bool is_win() override {
        // Check horizontal wins
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j <= this->columns - 3; ++j) {
                if (this->board[i][j] != ' ' &&
                    this->board[i][j] == this->board[i][j + 1] &&
                    this->board[i][j] == this->board[i][j + 2]) {
                    return true;
                }
            }
        }

        // Check vertical wins
        for (int j = 0; j < this->columns; ++j) {
            if (this->board[0][j] != ' ' &&
                this->board[0][j] == this->board[1][j] &&
                this->board[0][j] == this->board[2][j]) {
                return true;
            }
        }

        // Check diagonal wins
        if (this->board[0][0] != ' ' &&
            this->board[0][0] == this->board[1][2] &&
            this->board[0][0] == this->board[2][4]) {
            return true;
        }
        if (this->board[0][2] != ' ' &&
            this->board[0][2] == this->board[1][0] &&
            this->board[0][2] == this->board[2][0]) {
            return true;
        }

        return false;  // No winning condition met
    }
    bool is_draw() override {
        if (is_win()) {
            return false;
        }
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->columns; ++j) {
                if (j <= i * 2 && this->board[i][j] == ' ') {
                    return false;
                }
            }
        }
        return true;
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }

    ~pyramidXO() {
        for (int i = 0; i < this->rows; ++i) {
            delete[] this->board[i];
        }
        delete[] this->board;
    }
};

template <typename T>
class pyramid_X_O_Player : public Player<T> {
public:
    pyramid_X_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

    void getmove(int &x, int &y) override {
        cout << "\nPlease enter your move x and y (row and column) separated by spaces keeping in mind it is a pyramid board: ";
        cin >> x >> y;
        while (x < 0 || x >= static_cast<pyramidXO<T>*>(this->boardPtr)->getRows() || y < 0 || y >= static_cast<pyramidXO<T>*>(this->boardPtr)->getColumns() || y > x * 2 ||
               static_cast<pyramidXO<T>*>(this->boardPtr)->getBoardValue(x, y) != ' ') {
            cout << "Invalid move. Please enter a valid move x and y (row and column) separated by spaces: ";
            cin >> x >> y;
        }
    }
};

template <typename T>
class pyramid_X_O_Random_Player : public RandomPlayer<T> {
public:
    pyramid_X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
        this->dimension = 3;
        this->name = symbol;
        srand(static_cast<unsigned int>(time(0)));
    }

    void getmove(int &x, int &y) override {
        do {
            x = rand() % this->dimension;
            y = rand() % (x * 2 + 1);
        } while (static_cast<pyramidXO<T>*>(this->boardPtr)->getBoardValue(x, y) != ' ');
    }
};

#endif // ASSIGNMENT_DEMO_2_PYRAMIDBOARD_H