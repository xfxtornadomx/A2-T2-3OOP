//
// Created by Ahmed Atef on 16/12/2024.
//

#ifndef ASSIGNMENT_DEMO_2_CONNECT4_H
#define ASSIGNMENT_DEMO_2_CONNECT4_H
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include "BoardGame_Classes.h"

using namespace std;

template <typename T>
class Connect4Board : public Board<T> {
public:
    Connect4Board(int r = 6, int c = 7);
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;

private:
    vector<vector<T>> board;
    int rows;
    int columns;
    int n_moves = 0;
};

template <typename T>
class C4HumanPlayer {
public:
    C4HumanPlayer(string n, T s) : name(n), symbol(s) {}
    void get_move(int& x, int& y, int columns) {
        cout << name << ", enter column (0-" << columns - 1 << "): ";
        cin >> y;
        x = 0;
    }
    T get_symbol() const { return symbol; }

private:
    string name;
    T symbol;
};

template <typename T>
class C4RandomPlayer {
public:
    C4RandomPlayer(T s) : symbol(s) { srand(time(nullptr)); }
    void get_move(int& x, int& y, int columns) {
        y = rand() % columns;
        x = 0;
    }
    T get_symbol() const { return symbol; }

private:
    T symbol;
};

template <typename T>
Connect4Board<T>::Connect4Board(int r, int c) : rows(r), columns(c) {
    board.resize(rows, vector<T>(columns, ' '));
}

template <typename T>
bool Connect4Board<T>::update_board(int x, int y, T symbol) {
    if (y < 0 || y >= columns || board[0][y] != ' ') {
        return false;
    }
    for (int i = rows - 1; i >= 0; --i) {
        if (board[i][y] == ' ') {
            board[i][y] = symbol;
            n_moves++;
            return true;
        }
    }
    return false;
}

template <typename T>
void Connect4Board<T>::display_board() {
    for (const auto& row : board) {
        for (const auto& cell : row) {
            cout << "|" << cell;
        }
        cout << "|\n";
    }
    for (int j = 0; j < columns; ++j) {
        cout << " " << j;
    }
    cout << "\n";
}

template <typename T>
bool Connect4Board<T>::is_win() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns - 3; ++j) {
            if (board[i][j] != ' ' && board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2] && board[i][j] == board[i][j + 3]) {
                return true;
            }
        }
    }
    for (int i = 0; i < rows - 3; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (board[i][j] != ' ' && board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j] && board[i][j] == board[i + 3][j]) {
                return true;
            }
        }
    }
    for (int i = 0; i < rows - 3; ++i) {
        for (int j = 0; j < columns - 3; ++j) {
            if (board[i][j] != ' ' && board[i][j] == board[i + 1][j + 1] && board[i][j] == board[i + 2][j + 2] && board[i][j] == board[i + 3][j + 3]) {
                return true;
            }
        }
    }
    for (int i = 3; i < rows; ++i) {
        for (int j = 0; j < columns - 3; ++j) {
            if (board[i][j] != ' ' && board[i][j] == board[i - 1][j + 1] && board[i][j] == board[i - 2][j + 2] && board[i][j] == board[i - 3][j + 3]) {
                return true;
            }
        }
    }
    return false;
}

template <typename T>
bool Connect4Board<T>::is_draw() {
    return n_moves == rows * columns;
}

template <typename T>
bool Connect4Board<T>::game_is_over() {
    return is_win() || is_draw();
}

#endif //ASSIGNMENT_DEMO_2_CONNECT4_H
