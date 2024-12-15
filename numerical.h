//
// Created by Ahmed Atef on 15/12/2024.
//

#ifndef ASSIGNMENT_DEMO_2_NUMERICAL_H
#define ASSIGNMENT_DEMO_2_NUMERICAL_H
#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <limits>
using namespace std;

// Integrated X_O_Board class
template <typename T>
class Numerical_Board : public Board<T> {

public:
    // Constructor
    Numerical_Board() {
        this->rows = this->columns = 3;
        this->board = new char*[this->rows];
        for (int i = 0; i < this->rows; i++) {
            this->board[i] = new char[this->columns];
            for (int j = 0; j < this->columns; j++) {
                this->board[i][j] = ' ';
            }
        }
        this->n_moves = 0;
    }

    // Update the this->board with the given symbol
    bool update_board(int x, int y,  T symbol) override {

        if (x >= this->rows || x < 0 || y < 0 || y >= this->columns) {
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


    // Display the board
    void display_board() override {
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

    // Check if there is a winner
    bool is_win() override {
        auto char_to_int = [](char c) { return c - '0'; };

        for (int i = 0; i < this->rows; i++) {
            if ((char_to_int(this->board[i][0]) + char_to_int(this->board[i][1]) + char_to_int(this->board[i][2]) == 15) ||
                (char_to_int(this->board[0][i]) + char_to_int(this->board[1][i]) + char_to_int(this->board[2][i]) == 15)) {
                return true;
            }
        }
        if ((char_to_int(this->board[0][0]) + char_to_int(this->board[1][1]) + char_to_int(this->board[2][2]) == 15) ||
            (char_to_int(this->board[0][2]) + char_to_int(this->board[1][1]) + char_to_int(this->board[2][0]) == 15)) {
            return true;
        }
        return false;
    }

    // Check if the game is a draw
    bool is_draw() override{
        return (this->n_moves == 9 && !is_win());
    }

    // Check if the game is over
    bool game_is_over() override{
        return is_win() || is_draw();
    }

    // Destructor to clean up dynamically allocated memory
    ~Numerical_Board() {
        for (int i = 0; i < this->rows; i++) {
            delete[] this->board[i];
        }
        delete[] this->board;
    }
};

// Player classes remain the same
class Odd_Numerical_Player : public Player<char> {
private:
    set<int> usedNumbers;

public:
    Odd_Numerical_Player(string name) : Player<char>(name, ' ') {}

    void getmove(int& x, int& y) override {
        int num;
        cout << "\n" << name << ", please enter your move (x, y, followed by an odd number): ";
        while (!(cin >> x >> y >> num) || x < 0 || x >= 3 || y < 0 || y >= 3 || num % 2 == 0 || usedNumbers.count(num)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input or number already used. Please enter your move (x, y, followed by an odd number): ";
        }
        symbol = static_cast<char>(num + '0'); // Set the symbol to the entered number
        usedNumbers.insert(num); // Mark the number as used
    }
};
class Even_Numerical_Player : public Player<char> {
private:
    set<int> usedNumbers;

public:
    Even_Numerical_Player(string name) : Player<char>(name, ' ') {}

    void getmove(int& x, int& y) override {
        int num;
        cout << "\n" << name << ", please enter your move (x, y, followed by an even number): ";
        while (!(cin >> x >> y >> num) || x < 0 || x >= 3 || y < 0 || y >= 3 || num % 2 != 0 || usedNumbers.count(num)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input or number already used. Please enter your move (x, y, followed by an even number): ";
        }
        symbol = static_cast<char>(num + '0');// Set the symbol to the entered number
        usedNumbers.insert(num); // Mark the number as used
    }
};
template <typename T>
class Odd_Numerical_Random_Player : public RandomPlayer<T> {
public:
    Odd_Numerical_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
        this->dimension = 3;  // For 3x3 board
        this->name = "Random Computer Player";
        srand(static_cast<unsigned int>(time(0)));
    }

    void getmove(int& x, int& y) override {
        x = rand() % this->dimension;
        y = rand() % this->dimension;

        int randomOddNumber;
        do {
            randomOddNumber = rand() % 9 + 1;  // Generate a number between 1 and 9
        } while (randomOddNumber % 2 == 0);  // Ensure it is odd

        this->symbol = static_cast<char>(randomOddNumber + '0');  // Convert to character
    }
};

template <typename T>
class Even_Numerical_Random_Player : public RandomPlayer<T> {
public:
    Even_Numerical_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
        this->dimension = 3;  // For 3x3 board
        this->name = "Random Computer Player";
        srand(static_cast<unsigned int>(time(0)));
    }

    void getmove(int& x, int& y) override {
        x = rand() % this->dimension;
        y = rand() % this->dimension;

        int randomEvenNumber;
        do {
            randomEvenNumber = rand() % 8 + 2;  // Generate a number between 2 and 10
        } while (randomEvenNumber % 2 != 0);  // Ensure it is even

        this->symbol = static_cast<char>(randomEvenNumber + '0');  // Convert to character
    }
};

#endif //ASSIGNMENT_DEMO_2_NUMERICAL_H
