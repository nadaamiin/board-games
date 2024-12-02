#ifndef BOARD_GAMES_PYRAMID_TICTACTOE_H
#define BOARD_GAMES_PYRAMID_TICTACTOE_H
#include <iostream>
#include <iomanip>
#include "BoardGame_Classes.h"

using namespace std;
template <typename T>
class PyramidTicTacToc : public Board<T> {
public:
    PyramidTicTacToc() {
        this->rows = 3;
        this->columns = 5;
        int count = 1;
        this->board = new char*[this->rows];
        for (int i = 0; i < this->rows; ++i) {
            this->board[i] = new char[this->columns];
            for (int j = 0; j < this->columns; ++j) {
                this->board[i][j] = ' ';
                if((i == 0 && j == 2) || (i == 1 && j >= 1 && j <= 3) || i == 2){
                    this->board[i][j] = '0' + count;
                    count++;
                }
                this->n_moves = 0;
            }
        }
    }
//    ~PyramidTicTacToc() {
//        for (int i = 0; i < this->rows; ++i) {
//            delete[] this->board[i];
//        }
//        delete[] this->board;
//    }
    void display_board() override{
        // Row 1
        cout << setw(14) << "| " << this->board[0][2] << " |\n";
        // Row 2
        cout << setw(8) << "| " << this->board[1][1] << " | | "
             << this->board[1][2] << " | | " << this->board[1][3] << " |\n";
        // Row 3
        cout << "| " << this->board[2][0] << " | | " << this->board[2][1] << " | | " << this->board[2][2] << " | | "
             << this->board[2][3] << " | | " << this->board[2][4] << " |\n";
    }
    bool update_board(int x, int y, T symbol) override{
        if((x == 0 && y == 2) ||
           (x == 1 && y >= 1 && y <= 3) ||
           (x == 2 && y >= 0 && y <= 4) &&
           (this->board[x][y] != 'X' || this->board[x][y] != 'Y' || symbol == 0)){
            if (symbol == 0){
                this->n_moves--;
                this->board[x][y] = 0;
            }
            else {
                this->n_moves++;
                this->board[x][y] = toupper(symbol);
            }
            return true;
        }
        return false;
    }
    /// Returns true if there is any winner
    bool is_win(){}

    /// Return true if all moves are done and no winner
    bool is_draw(){
        return (this->n_moves == 9 && !is_win());
    }

    /// Return true if the game is over
    bool game_is_over(){
        return is_win() || is_draw();
    }


};
#endif //BOARD_GAMES_PYRAMID_TICTACTOE_H
