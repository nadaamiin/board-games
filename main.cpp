#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "FourInRow.h"
#include "NumericalTicTacToe.h"
#include "BoardGame_Classes.h"

using namespace std;

// Define a generic structure to hold the board and players
template <typename T>
struct GameSetup {
    Board<T>* board;
    Player<T>* players[2];
};

template <typename T>
GameSetup<T> choosePlayer(Board<T>* board, T symbol1, T symbol2, int gameType) {
    // Create Player 1
    Player<T>* player1;
    string player1_name;
    cout << "Enter Player 1 name:\n";
    cin >> player1_name;

    if (gameType == 2) {
        player1 = new Connect_Four_Player<T>(player1_name, symbol1);
    } else {
        player1 = new Numerical_TicTacToe_Player<T>(player1_name, symbol1);
    }

    // Choose Player 2 type
    cout << "Choose the type of Player 2:\n1) Human Player\n2) Random Player\n3) AI Player\n";
    int player2Type;
    cin >> player2Type;

    Player<T>* player2;

    if (player2Type == 1) {
        // Human Player: prompt for a name
        string player2_name;
        cout << "Enter Player 2 name: ";
        cin >> player2_name;

        player2 = (gameType == 2)
                  ? static_cast<Player<T>*>(new Connect_Four_Player<T>(player2_name, symbol2))
                  : static_cast<Player<T>*>(new Numerical_TicTacToe_Player<T>(player2_name, symbol2));
    } else if (player2Type == 2) {
        // Random Player
        if (gameType == 2) {
            player2 = new Connect_Four_Random_Player<T>('O');
        } else {
            player2 = new Numerical_TicTacToe_Random_Player<T>(symbol2);
        }
    }
        // Commented out AI Player for future use
        // else if (player2Type == 3) {
        //     player2 = new Numerical_TicTacToe_AI_Player<T>('O');
        // }
    else {
        throw invalid_argument("Invalid player type!");
    }

    return {board, {player1, player2}};
}


int main() {
    srand(static_cast<unsigned>(time(0))); // Seed random number generator

    int choice;
    cout << "__________ Welcome to \"World Of Games!\" __________\n";
    cout << "Choose a game:\n0) Exit\n2) Connect Four\n5) Numerical Tic Tac Toe\n";
    cin >> choice;

    switch (choice) {
        case 0:
            cout << "Thanks for playing! Goodbye.\n";
            return 0;

        case 2: {
            // Connect Four setup
            auto* board = new Connect_Four_Board<char>();
            GameSetup<char> setup = choosePlayer<char>(board, 'X', 'O', 2);

            GameManager<char> game(setup.board, setup.players);
            game.run();

            // Cleanup
            delete setup.players[0];
            delete setup.players[1];
            delete setup.board;
            break;
        }

        case 5: {
            // Numerical Tic Tac Toe setup

            auto* board = new Numerical_TicTacToe_Board<int>();

            GameSetup<int> setup = choosePlayer<int>(board, 1, 2, 5);

            GameManager<int> game(setup.board, setup.players);
            game.run();

            // Cleanup
            delete setup.players[0];
            delete setup.players[1];
            delete setup.board;
            break;
        }

        default:
            cerr << "Invalid choice! Please select a valid option.\n";
            break;
    }

    return 0;
}