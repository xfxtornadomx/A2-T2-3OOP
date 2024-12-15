//
// Created by Ahmed Atef on 11/12/2024.
//

#ifndef ASSIGNMENT_DEMO_2_WORDX_O_H
#define ASSIGNMENT_DEMO_2_WORDX_O_H
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
#include <cstdlib>
#include <ctime>

using namespace std;
class wordX_0 : public Board<char> {
private:
    set<string> dictionary;
    string wordSequence;
    int wordIndex;

public:
    wordX_0() : wordIndex(0) {
        this->rows = this->columns = 3;
        this->board = new char*[this->rows];
        for (int i = 0; i < this->rows; i++) {
            this->board[i] = new char[this->columns];
            for (int j = 0; j < this->columns; j++) {
                this->board[i][j] = ' ';  // Initialize with space character
            }
        }
        this->n_moves = 0;
        load_dict("dic.txt");
    }

    void load_dict(const string& fileName) {
        ifstream file(fileName);
        if (!file.is_open()) {
            cerr << "Failed to open file: " << fileName << endl;
            return;
        }
        string line;
        while (getline(file, line)) {
            dictionary.insert(line);
        }
        file.close();
    }

    string trim(const string& str) {
        size_t first = str.find_first_not_of(" \t\n\r\f\v");
        size_t last = str.find_last_not_of(" \t\n\r\f\v");
        return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
    }

    bool checkWordSequence(const string& wordSequence) {
        ifstream file("dic.txt");

        if (!file.is_open()) {
            cerr << "Failed to open file: dic.txt" << endl;
            return false;
        }

        string line;
        string trimmedWordSequence = trim(wordSequence);
        transform(trimmedWordSequence.begin(), trimmedWordSequence.end(), trimmedWordSequence.begin(), ::toupper);

        while (getline(file, line)) {
            string trimmedLine = trim(line);  // Trim each line from the file
            transform(trimmedLine.begin(), trimmedLine.end(), trimmedLine.begin(), ::toupper);

            if (trimmedLine == trimmedWordSequence) {
                cout << "Found match: " << trimmedLine << endl;
                file.close();
                return true;
            }
        }

        file.close();
        return false;
    }

    bool update_board(int x, int y, char symbol) override {
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

    bool is_win() override {
        // Check rows
        for (int i = 0; i < this->rows; i++) {
            string word = "";
            for (int j = 0; j < this->columns; j++) {
                word += this->board[i][j];
            }

            if (checkWordSequence(word)) {
                return true;
            }
        }

        // Check columns
        for (int j = 0; j < this->columns; j++) {
            string word = "";
            for (int i = 0; i < this->rows; i++) {
                word += this->board[i][j];
            }

            if (checkWordSequence(word)) {
                return true;
            }
        }

        // Check main diagonal
        string word = "";
        for (int i = 0; i < this->rows; i++) {
            word += this->board[i][i];
        }

        if (checkWordSequence(word)) {
            return true;
        }


        word = "";
        for (int i = 0; i < this->rows; i++) {
            word += this->board[i][this->columns - i - 1];
        }
        if (checkWordSequence(word)) {
            return true;
        }

        return false;
    }
    bool is_draw() override {
        return (this->n_moves == 9 && !is_win());
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }

    ~wordX_0() {
        for (int i = 0; i < this->rows; i++) {
            delete[] this->board[i];
        }
        delete[] this->board;
    }
};
class WordX_O_Player : public Player<char> {
public:
    WordX_O_Player(string name) : Player<char>(name, ' ') {}

    void getmove(int& x, int& y) override {
        cout << "\n" << name << ", please enter your move (x, y, followed by your letter): ";
        while (!(cin >> x >> y >> symbol) || x < 0 || x >= 3 || y < 0 || y >= 3 || !isalpha(symbol)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter your move (x, y, followed by your letter): ";
        }
        symbol = toupper(symbol);
    }
};
template <typename T>
class wordX_O_Random_Player : public RandomPlayer<T> {
public:
    wordX_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
        this->dimension = 3;  // For 3x3 board
        this->name = "Random Computer Player";
        srand(static_cast<unsigned int>(time(0)));
    }

    void getmove(int& x, int& y) override {

        x = rand() % this->dimension;
        y = rand() % this->dimension;


        char randomLetter = 'A' + rand() % 26;
        this->symbol = randomLetter;
    }
};

#endif //ASSIGNMENT_DEMO_2_WORDX_O_H
