#ifndef BOARD_GAMES_FOURINROW_H
#define BOARD_GAMES_FOURINROW_H

#include "BoardGame_Classes.h"

template <typename T>
class Connect_Four_Board:public Board<T> {
public:
    Connect_Four_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class Connect_Four_Player : public Player<T> {
public:
    Connect_Four_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class Connect_Four_Random_Player : public RandomPlayer<T>{
public:
    Connect_Four_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};

//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

template <typename T>
Connect_Four_Board<T>::Connect_Four_Board() {
    this->columns = 7;
    this->rows = 6;
    // Allocate memory for the rows (6 rows)
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        // Allocate memory for the columns in each row (7 columns)
        this->board[i] = new char[this->columns];
        // Initialize each cell to 0 (representing an empty state)
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    // Initialize the number of moves to 0
    this->n_moves = 0;
}

template <typename T>
bool Connect_Four_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
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
void Connect_Four_Board<T>::display_board() {
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

template <typename T>
bool Connect_Four_Board<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns - 3; j++) {
            // Check row
            if (this->board[i][j] == this->board[i][j+1] && this->board[i][j+1] == this->board[i][j+2] &&
                this->board[i][j+2] == this->board[i][j+3] && this->board[i][j] != 0) {
                return true;
            }
        }
    }

    for (int j = 0; j < this->columns; j++) {
        for (int i = 0; i < this->rows - 3; i++) {
            // Check column
            if (this->board[i][j] == this->board[i+1][j] && this->board[i+1][j] == this->board[i+2][j] &&
                this->board[i+2][j] == this->board[i+3][j] && this->board[i][j] != 0) {
                return true;
            }
        }
    }

    // Check diagonals
    for (int i = 0; i < this->rows - 3; i++) {
        for (int j = 0; j < this->columns - 3; j++) {
            // Principal diagonal
            if (this->board[i][j] == this->board[i+1][j+1] && this->board[i+1][j+1] == this->board[i+2][j+2] &&
                this->board[i+2][j+2] == this->board[i+3][j+3] && this->board[i][j] != 0) {
                return true;
            }
            // Bottom-left to top-right
            if (this->board[i+3][j] == this->board[i+2][j+1] && this->board[i+2][j+1] == this->board[i+1][j+2] &&
                this->board[i+1][j+2] == this->board[i][j+3] && this->board[i+3][j] != 0) {
                return true;
            }
        }
    }

    return false;
}


// Return true if 9 moves are done and no winner
template <typename T>
bool Connect_Four_Board<T>::is_draw() {
    return (this->n_moves == 42 && !is_win());
}

template <typename T>
bool Connect_Four_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
Connect_Four_Player<T>::Connect_Four_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Connect_Four_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x (0 - 5)\n and y (0 - 6): \n";
    cin >> x >> y;
}

// Constructor for X_O_Random_Player
template <typename T>
Connect_Four_Random_Player<T>::Connect_Four_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 6;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void Connect_Four_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}

#endif  BOARD_GAMES_FOURINROW_H
