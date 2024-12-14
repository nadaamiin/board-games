#ifndef BOARD_GAMES_SUS_H
#define BOARD_GAMES_SUS_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>
using namespace std;
static bool isRandom9 = false;
Player<char>* globalPlayers_SUS[2];

template <typename T>
class SUS_Board:public Board<T> {
public:
    int player1Points = 0;
    int player2Points = 0;
    SUS_Board (){
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
    bool update_board (int x , int y , T symbol) override{
        if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| symbol == 0)) {
            if (symbol == 0){
                this->n_moves--;
                this->board[x][y] = 0;
            }
            else {
                this->n_moves++;
                this->board[x][y] = toupper(symbol);
            }

            return true;
        }else{
            if(!isRandom9){
                cerr << "Invalid move! \n";
            }
        }
        return false;
    }
    void display_board () override{
        // Print the column indices
        cout << "   ";
        for (int j = 0; j < this->columns; j++) {
            cout << setw(3) << j << "  "; // Column numbers at the top
        }
        cout << "\n";

        // Print each row with its content
        for (int i = 0; i < this->rows; i++) {
            cout << i << " |"; // Row index at the start
            for (int j = 0; j < this->columns; j++) {
                char display_char = this->board[i][j] == 0 ? ' ' : this->board[i][j]; // Empty space for 0
                cout << setw(3) << display_char << " |";
            }
            cout << "\n    " << "________________" << "\n"; // Separator line
        }
        cout << endl;
    }

    int playerCounter() {
        int player_count = 0;

        for (int i = 0; i < this->rows; i++) {
            // Check row
            if (this->board[i][0] == 'S' && this->board[i][1] == 'U' && this->board[i][2] == 'S') {
                this->n_moves % 2 == 0 ? player1Points++ : player2Points++;
                player_count++;
            }
            // Check column
            if (this->board[0][i] == 'S' && this->board[1][i] == 'U' && this->board[2][i] == 'S') {
                this->n_moves % 2 == 0 ? player1Points++ : player2Points++;
                player_count++;
            }
        }

        // Check diagonals
        if ((this->board[0][0] == 'S' && this->board[1][1] == 'U' && this->board[2][2] == 'S') ||
            (this->board[0][2] == 'S' && this->board[1][1] == 'U' && this->board[2][0] == 'S')) {
            this->n_moves % 2 == 0 ? player1Points++ : player2Points++;
            player_count++;
        }
        return player_count;
    }


    bool is_win() override {

        if(this-> n_moves == 9) {
            int count_p1 = playerCounter('S');
            int count_p2 = playerCounter('U');

            if (count_p1 > count_p2 ) {
                // Access and update player names
                *globalPlayers_ttt[1] = *globalPlayers_ttt[0];  // This copies the entire player object
                return true;
            }
            else if(count_p1 < count_p2){
                return true;
            }

        }

        return false;
    }


    bool is_draw() override {
        // A draw happens when the board is full and no player has won
        return (this->n_moves == 9 && !is_win());
    }

    bool game_is_over() override {
        // The game ends if there's a win or a draw
        return is_win() || is_draw();
    }

};

template <typename T>
class SUS_Player : public Player<T> {
public:
    SUS_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class SUS_Random_Player : public RandomPlayer<T>{
public:
    SUS_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};

template <typename T>
SUS_Player<T>::SUS_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void SUS_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

template <typename T>
SUS_Random_Player<T>::SUS_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void SUS_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
    isRandom9 = true;
}

#endif //BOARD_GAMES_SUS_H
