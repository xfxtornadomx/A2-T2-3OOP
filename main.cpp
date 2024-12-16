/*
 * Assignment 2 T2-3 s17-18
 * Team Members:
 * 1. Ahmed Atef Adel - ID: 20230026
 * 2. Ali Mahmoud Mohamed - ID: 20230026
 * 3. Mohamed Ayman - ID: 20231137
 *
 * Games Implemented:
 * - Ahmed Atef Adel:
 *   1. Pyramid TicTacToe
 *   2. Word TicTacToe
 *   3. Ultimate TicTacToe
 *   4. SUS
 *
 * - Ali Mahmoud Mohamed:
 *   1. Connect 4
 *   2. Numerical TicTacToe
 *   3. Ultimate TicTacToe
 *   4. SUS
 *
 * - Mohamed Ayman:
 *   1. 5x5 TicTacToe
 *   2. Misere TicTacToe
 *   3. Ultimate TicTacToe
 *   4. SUS
 */

#include "BoardGame_Classes.h"
#include "pyramidBoard.h"
#include "connect4.h"
#include "wordX_O.h"
#include "numerical.h"
#include "ultimateTicTacToe.h"
#include <iostream>
using namespace std;

int main(){
    int x;
    while (true) {
        cout << "____Welcome to to our Teams implemenation of the board classes____" << endl;
        cout << "Choose your desired game" << endl;
        cout << "1.Pyramic TicTacToe\n2-Four-in-a-row\n3-5*5 TicTacToe\n4-Word TicTacToe\n5-Numerical TicTacToe\n6-Misere TicTacToe\n7-Ultimate TicTacToe\n8-SUS\n9-Exit\nEnter a number between 1 and 9: ";

        cin >> x;
        if(x<1 || x>9 ){
            cout << "please enter a number within the range" << endl;
            continue;
        };

        switch (x) {
            case 1: {
                int choice;
                Player<char> *players[2] = {nullptr, nullptr};
                pyramidXO<char> *B = new pyramidXO<char>();
                string playerXName, player2Name;

                cout << "Welcome to pyramid X-O Game. :)\n";

                // Set up player 1
                cout << "Enter Player X name: ";
                cin >> playerXName;
                cout << "Choose Player X type:\n";
                cout << "1. Human\n";
                cout << "2. Random Computer\n";
                cin >> choice;

                switch (choice) {
                    case 1:
                        players[0] = new pyramid_X_O_Player<char>(playerXName, 'X');
                        break;
                    case 2:
                        players[0] = new pyramid_X_O_Random_Player<char>('X');
                        break;
                    default:
                        cout << "Invalid choice for Player 1. Exiting the game.\n";
                        delete B;
                        return 1;
                }

                // Set up player 2
                cout << "Enter Player O name: ";
                cin >> player2Name;
                cout << "Choose Player O type:\n";
                cout << "1. Human\n";
                cout << "2. Random Computer\n";
                cin >> choice;

                switch (choice) {
                    case 1:
                        players[1] = new pyramid_X_O_Player<char>(player2Name, 'O');
                        break;
                    case 2:
                        players[1] = new pyramid_X_O_Random_Player<char>('O');
                        break;
                    default:
                        cout << "Invalid choice for Player 2. Exiting the game.\n";
                        delete players[0];
                        delete B;
                        return 1;
                }

                // Set the board for both players
                players[0]->setBoard(B);
                players[1]->setBoard(B);

                // Create the game manager and run the game
                GameManager<char> x_o_game(B, players);
                x_o_game.run();

                // Clean up
                for (int i = 0; i < 2; ++i) {
                    delete players[i];
                }
                delete B;

                break;
            }
            case 2: {
                Connect4Board<char> board;
                C4HumanPlayer<char> player1("Player 1", 'X');
                C4RandomPlayer<char> player2('O');
                int turn = 0;
                int x, y;
                while (!board.game_is_over()) {
                    board.display_board();
                    if (turn % 2 == 0) {
                        cout << "\nPlayer 1's turn (X)\n";
                        player1.get_move(x, y, 7);
                    } else {
                        cout << "\nPlayer 2's turn (O)\n";
                        player2.get_move(x, y, 7);
                    }

                    if (!board.update_board(x, y, (turn % 2 == 0 ? 'X' : 'O'))) {
                        cout << "Invalid move. Try again.\n";
                        continue;
                    }

                    if (board.is_win()) {
                        board.display_board();
                        cout << "\n" << (turn % 2 == 0 ? "Player 1 (X)" : "Player 2 (O)") << " Wins!\n";
                        return 0;
                    }
                    turn++;
                }
                board.display_board();
                cout << "\nGame Is Draw!\n";

                break;
            }
            case 3:

                break;
            case 4: {
                int choice;
                Player<char> *players[2];  // Player array to hold two players
                wordX_0 *B = new wordX_0();  // Create a new wordX_0 board game
                string playerXName, player2Name;

                cout << "Welcome to WordX_O Game. :)\n";

                // Set up player 1
                cout << "Enter Player 1 name: ";
                cin >> playerXName;
                cout << "Choose Player 1 type:\n";
                cout << "1. Human\n";
                cout << "2. Random Computer\n";
                cin >> choice;

                switch (choice) {
                    case 1:
                        players[0] = new WordX_O_Player(playerXName);  // Human player
                        break;
                    case 2:
                        players[0] = new wordX_O_Random_Player<char>('1');  // Random computer player
                        break;
                    default:
                        cout << "Invalid choice for Player 1. Exiting the game.\n";
                        delete B;
                        return 1;
                }

                // Set up player 2
                cout << "Enter Player 2 name: ";
                cin >> player2Name;
                cout << "Choose Player 2 type:\n";
                cout << "1. Human\n";
                cout << "2. Random Computer\n";
                cin >> choice;

                switch (choice) {
                    case 1:
                        players[1] = new WordX_O_Player(player2Name);  // Human player
                        break;
                    case 2:
                        players[1] = new wordX_O_Random_Player<char>('2');  // Random computer player
                        break;
                    default:
                        cout << "Invalid choice for Player 2. Exiting the game.\n";
                        delete B;
                        for (int i = 0; i < 2; ++i) {
                            delete players[i];
                        }
                        return 1;
                }

                // Create the game manager and run the game
                GameManager<char> x_o_game(B, players);  // Initialize the game manager with the board and players
                x_o_game.run();  // Run the game

                // Clean up resources
                delete B;
                for (int i = 0; i < 2; ++i) {
                    delete players[i];
                }


                break;
            }
            case 5: {
                int choice;
                Player<char>* players[2];  // Player array to hold two players
                Numerical_Board<char>* B = new Numerical_Board<char>();  // Create a new wordX_0 board game
                string playerXName, player2Name;

                cout << "Welcome to Numerical TicTacToe Game. :)\n";

                // Set up player 1
                cout << "Enter Player 1 name: ";
                cin >> playerXName;
                cout << "Choose Player 1 type:\n";
                cout << "1. Human\n";
                cout << "2. Random Computer\n";
                cin >> choice;

                switch(choice) {
                    case 1:
                        players[0] = new Odd_Numerical_Player(playerXName);  // Human player
                        break;
                    case 2:
                        players[0] = new Odd_Numerical_Random_Player<char>('1');  // Random computer player
                        break;
                    default:
                        cout << "Invalid choice for Player 1. Exiting the game.\n";
                        delete B;
                        return 1;
                }

                // Set up player 2
                cout << "Enter Player 2 name: ";
                cin >> player2Name;
                cout << "Choose Player 2 type:\n";
                cout << "1. Human\n";
                cout << "2. Random Computer\n";
                cin >> choice;

                switch(choice) {
                    case 1:
                        players[1] = new Even_Numerical_Player(player2Name);  // Human player
                        break;
                    case 2:
                        players[1] = new Even_Numerical_Random_Player<char>('2');  // Random computer player
                        break;
                    default:
                        cout << "Invalid choice for Player 2. Exiting the game.\n";
                        delete B;
                        for (int i = 0; i < 2; ++i) {
                            delete players[i];
                        }
                        return 1;
                }

                // Create the game manager and run the game
                GameManager<char> x_o_game(B, players);
                x_o_game.run();  // Run the game

                // Clean up resources
                delete B;
                for (int i = 0; i < 2; ++i) {
                    delete players[i];
                }


                break;
            }
            case 6:

                break;
            case 7: {
                int choice;
                Player<char>* players[2];
                ultimateTicTacToe<char>* B = new ultimateTicTacToe<char>();
                string playerXName, player2Name;

                cout << "Welcome to ultimate tic tac toe  Game. :)\n";

                // Set up player 1
                cout << "Enter Player X name: ";
                cin >> playerXName;
                cout << "Choose Player X type:\n";
                cout << "1. Human\n";
                cout << "2. Random Computer\n";
                cin >> choice;

                switch(choice) {
                    case 1:
                        players[0] = new ultimateTicTacToePlayer<char>(playerXName, 'X');
                        break;
                    case 2:
                        players[0] = new ultimateTicTacToeRandomPlayer<char>('X');
                        break;
                    default:
                        cout << "Invalid choice for Player 1. Exiting the game.\n";
                        return 1;
                }

                // Set up player 2
                cout << "Enter Player O name: ";
                cin >> player2Name;
                cout << "Choose Player O type:\n";
                cout << "1. Human\n";
                cout << "2. Random Computer\n";
                cin >> choice;

                switch(choice) {
                    case 1:
                        players[1] = new ultimateTicTacToePlayer<char>(player2Name, 'O');
                        break;
                    case 2:
                        players[1] = new ultimateTicTacToeRandomPlayer<char>('O');
                        break;
                    default:
                        cout << "Invalid choice for Player 2. Exiting the game.\n";
                        return 1;
                }

                // Create the game manager and run the game
                GameManager<char> x_o_game(B, players);
                x_o_game.run();

                // Clean up
                delete B;
                for (int i = 0; i < 2; ++i) {
                    delete players[i];
                }



                break;
            }
            case 8:

                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
        if(x == 9){
            cout << "Exiting the program" <<endl;
            break;
        }
        cin.ignore();

    }
    return 0;
};






