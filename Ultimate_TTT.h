#ifndef BOARD_GAMES_ULTIMATE_TTT_H
#define BOARD_GAMES_ULTIMATE_TTT_H

#include <iostream>
#include <iomanip>
#include "BoardGame_Classes.h"

using namespace std;
static int counter = 0;

template <typename T>
class Ultimate_TTT : public Board<T> {
    T** sub_board;
public:
    Ultimate_TTT() {
        this->rows = 3;
        this->columns = 3;
        int count = 1;
        this->board = new char*[this->rows];
        for (int i = 0; i < this->rows; ++i) {
            this->board[i] = new char[this->columns];
            for (int j = 0; j < this->columns; ++j) {
                this->board[i][j] = '0' + count;
                this->sub_board[i][j] = '0' + count;
                count++;
            }
            this->n_moves = 0;
        }
    }
    void display_board() override{
        if(counter % 2 == 0) {
            for (int i = 0; i < this->rows; i++) {
                cout << "\n|";
                for (int j = 0; j < this->columns; j++) {
                    cout << setw(2) << this->board[i][j] << setw(2) << " |";
                }
                cout << "\n-------------";
            }
            cout << endl;
        }else{
            for (int i = 0; i < this->rows; i++) {
                cout << "\n|";
                for (int j = 0; j < this->columns; j++) {
                    cout << setw(2) << this->sub_board[i][j] << setw(2) << " |";
                }
                cout << "\n-------------";
            }
            cout << endl;
        }
    }
    bool update_board(int x, int y, T symbol) override{
        // Only update if move is valid
        if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == ' ' ||
        isdigit(this->board[x][y]) || symbol == 0)) {
            if (symbol == 0){
                this->n_moves--;
                this->board[x][y] = ' ';
            }
            else {
                this->n_moves++;
                this->board[x][y] = toupper(symbol);
            }
            return true;
        }
        return false;
    }
    bool is_win() override{

    }

    bool is_draw() override{

    }
    bool is_complete(){
        if(is_win()){
            counter+=2;
        }
    }

    bool game_is_over() override{

    }


};

template <typename T>
class Ultimate_player : public Player<T>{
    Ultimate_player(string name, T symbol) : Player<T>(name, symbol){}
    void getmove(int& x, int& y) override{
        int index;
        cout << "Enter the box you want to play in:";
        cin >> index;
        /// Assign each number in the board to its corresponding index
        if(index == 1 || index == 2 || index == 3){
            x = 0;
        }else if(index == 4 || index == 5 || index == 6){
            x = 1;
        }else if(index == 7 || index == 8 || index == 9){
            x = 2;
        }
        if(index == 1 || index == 4 || index == 7){
            y = 0;
        }else if(index == 2 || index == 5 || index == 8){
            y = 1;
        }else if(index == 3 || index == 6 || index == 9){
            y = 2;
        }
    }

};

#endif //BOARD_GAMES_ULTIMATE_TTT_H
