#ifndef BOARD_GAMES_WORD_TICTACTTOE_H
#define BOARD_GAMES_WORD_TICTACTTOE_H

#include <iostream>
#include <iomanip>
#include "BoardGame_Classes.h"

using namespace std;
template <typename T>
class WordTicTacToe : public Board<T>{
public:
    WordTicTacToe() {
        this->rows = 3;
        this->columns = 3;
        int count = 1;
        this->board = new char*[this->rows];
        for (int i = 0; i < this->rows; ++i) {
            this->board[i] = new char[this->columns];
            for (int j = 0; j < this->columns; ++j) {
                this->board[i][j] = '0' + count;
                count++;
            }
            this->n_moves = 0;
        }
    }
    void display_board() override{
        for (int i = 0; i < this->rows; i++) {
            cout << "\n|";
            for (int j = 0; j < this->columns; j++) {
                cout << setw(2) << this->board[i][j] << setw(2) << " |";
            }
            cout << "\n-------------";
        }
        cout << endl;
    }
    bool update_board(int x, int y, T symbol){
        // Only update if move is valid
        if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == ' ' || symbol == 0)) {
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
    bool is_win(){
    }
    bool is_draw(){
        return (this->n_moves == 9 && !is_win());
    }
    bool game_is_over(){
        return is_win() || is_draw();
    }

};

#endif //BOARD_GAMES_WORD_TICTACTTOE_H
