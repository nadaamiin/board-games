#include <iostream>
#include "BoardGame_Classes.h"
#include "Misere_Tic_Tac_Toe.h"
#include "MinMaxPlayer.h"

using namespace std;

int main() {
    int choice;
    Player<char>* players[2];
    Misere_Tic_Tac_Toe <char>* B = new Misere_Tic_Tac_Toe<char>();
    string player1Name, player2Name;


    cout << "Welcome to FCAI  Misere X-O Game. :)\n";

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
            players[0] = new Misere_Player<char>(player1Name, 'X');
            break;
        case 2:
            players[0] = new Misere_Random_Player<char>('X');
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
            players[1] = new Misere_Player<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new Misere_Random_Player<char>('O');
            break;
        case 3:
            players[1] = new X_O_MinMax_Player<char>('O');
            players[1]->setBoard(B);
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return 1;
    }

    globalPlayers[0] = players[0];
    globalPlayers[1] = players[1];

    // Create the game manager and run the game
    GameManager<char> misere_tic_tac_toe_Game(B, players);
    misere_tic_tac_toe_Game.run();

    // Clean up
    delete B;
    for (auto &player: players) {
        delete player;
    }


    return 0;
}