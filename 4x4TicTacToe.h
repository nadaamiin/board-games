#ifndef BOARD_GAMES_4X4TICTACTOE_H
#define BOARD_GAMES_4X4TICTACTOE_H
#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>
using namespace std;

template <typename T>
class TicTacToe4x4_Board:public Board<T> {
public:
    TicTacToe4x4_Board() {
        this->rows = this->columns = 4;
        this->board = new char*[this->rows];

        for (int i = 0; i < this->rows; i++) {
            this->board[i] = new char[this->columns];
        }

        this->board[0][0] = 'O';
        this->board[0][1] = 'X';
        this->board[0][2] = 'O';
        this->board[0][3] = 'X';
        this->board[3][0] = 'X';
        this->board[3][1] = 'O';
        this->board[3][2] = 'X';
        this->board[3][3] = 'O';

        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                if ((i == 0 || i == 3) && (j == 0 || j == 1 || j == 2 || j == 3)) {
                    continue;
                }
                this->board[i][j] = 0;
            }
        }
        this->n_moves = 0;
    }

    bool update_board(int x, int y, T symbol) override {
        int currentX, currentY;

        cout << "Enter the current position (row and column) of the piece you want to move:\n";
        cin >> currentX >> currentY;
        cout << "Enter the target position (row and column) for your move:\n";
        cin >> x >> y;

        if (currentX < 0 || currentX >= this->rows || currentY < 0 || currentY >= this->columns) {
            return false;
        }

        if (this->board[currentX][currentY] != symbol) {
            return false;
        }

        // Validate the target position
        if (x < 0 || x >= this->rows || y < 0 || y >= this->columns) {
            return false;
        }

        // Check if the target cell is empty
        if (this->board[x][y] != 0) {
            return false;
        }

        if((x == currentX+1 && y == currentY) || (x == currentX && y == currentY+1) || (x == currentX-1 && y == currentY) || (x == currentX && y == currentY-1)){
            // Move the symbol
            this->board[currentX][currentY] = 0; // Clear the current position
            this->board[x][y] = symbol;          // Place the symbol in the target position

            // Increment the move count
            this->n_moves++;
            return true; // Move successful

        }else{
            return false;
        }

    }


    void display_board() override {
        cout << "   ";
        for (int j = 0; j < this->columns; j++) {
            cout << setw(3) << j << "  ";
        }
        cout << "\n";

        for (int i = 0; i < this->rows; i++) {
            cout << i << " |";
            for (int j = 0; j < this->columns; j++) {
                if (this->board[i][j] == 0) {
                    cout << setw(3) << " " << " |";
                }
                else {
                    cout << setw(3) << this->board[i][j] << " |";
                }
            }
            cout << "\n    " << "--------------------" << "\n";
        }
        cout << endl;
    }
    bool is_win() override {
        // Check rows and columns
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j <= this->columns - 4; j++) {
                // Check row
                if (this->board[i][j] != 0 &&
                    this->board[i][j] == this->board[i][j + 1] &&
                    this->board[i][j + 1] == this->board[i][j + 2] &&
                    this->board[i][j + 2] == this->board[i][j + 3]) {
                    return true;
                }
            }
        }

        for (int j = 0; j < this->columns; j++) {
            for (int i = 0; i <= this->rows - 4; i++) {
                // Check column
                if (this->board[i][j] != 0 &&
                    this->board[i][j] == this->board[i + 1][j] &&
                    this->board[i + 1][j] == this->board[i + 2][j] &&
                    this->board[i + 2][j] == this->board[i + 3][j]) {
                    return true;
                }
            }
        }

        // Check diagonals
        for (int i = 0; i <= this->rows - 4; i++) {
            for (int j = 0; j <= this->columns - 4; j++) {
                // Principal diagonal
                if (this->board[i][j] != 0 &&
                    this->board[i][j] == this->board[i + 1][j + 1] &&
                    this->board[i + 1][j + 1] == this->board[i + 2][j + 2] &&
                    this->board[i + 2][j + 2] == this->board[i + 3][j + 3]) {
                    return true;
                }
                // Bottom-left to top-right diagonal
                if (this->board[i + 3][j] != 0 &&
                    this->board[i + 3][j] == this->board[i + 2][j + 1] &&
                    this->board[i + 2][j + 1] == this->board[i + 1][j + 2] &&
                    this->board[i + 1][j + 2] == this->board[i][j + 3]) {
                    return true;
                }
            }
        }

        return false;
    }

    bool is_draw()override{
        return (this->n_moves == 16 && !is_win());
    }
    bool game_is_over() override{
        return is_win() || is_draw();
    }

};

template <typename T>
class TicTacToe4x4_Player : public Player<T> {
public:
    TicTacToe4x4_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class TicTacToe4x4_Random_Player : public RandomPlayer<T>{
public:
    TicTacToe4x4_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};

template <typename T>
TicTacToe4x4_Player<T>::TicTacToe4x4_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void TicTacToe4x4_Player<T>::getmove(int& x, int& y) {
}


template <typename T>
TicTacToe4x4_Random_Player<T>::TicTacToe4x4_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 4;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}
template <typename T>
void TicTacToe4x4_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}

#endif
