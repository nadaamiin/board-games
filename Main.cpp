#include <iostream>
#include <string>
#include "BoardGame_Classes.h"
#include "Tic_Tac_Toe_Board.h"
#include "MinMaxPlayer.h"

using namespace std;

int main() {
    int choice;
    Player<char>* players[2];
    Tic_Tac_Toe_Board <char>* B = new Tic_Tac_Toe_Board<char>();

    string player1Name, player2Name;


    cout << "Welcome to FCAI Tic Tac Toe Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> player1Name;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. Smart Computer (AI)\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new HumanPlayer<char>(player1Name, 'X');
            break;
        case 2:
            players[0] = new RandomComputerPlayer<char>('X');
            break;
        case 3:
            players[0] = new X_O_MinMax_Player<char>('X');
            players[0]->setBoard(B);
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return 1;
    }


    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. Smart Computer (AI)\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new HumanPlayer<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new RandomComputerPlayer<char>('O');
            break;
        case 3:
            players[1] = new X_O_MinMax_Player<char>('O');
            players[1]->setBoard(B);
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return 1;
    }

    // Set the board pointer for both players
    players[0]->setBoard(B);
    players[1]->setBoard(B);

    B->setPlayers(players[0], players[1]);

    // Create the game manager and run the game
    GameManager<char> ttt_game(B, players);
    //winner_p[0] = players[0];
    //winner_p[1] = players[1];

    ttt_game.run();

    // Clean up
    delete B;
    for (auto &player: players) {
        delete player;
    }


    return 0;
}