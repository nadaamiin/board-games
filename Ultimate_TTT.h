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
    int sub_moves = 0;
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
                    cout << setw(2) << sub_board[i][j] << setw(2) << " |";
                }
                cout << "\n-------------";
            }
            cout << endl;
        }
    }
    bool update_board(int x, int y, T symbol) override{
        //Check is move within bound or not
        if(x < 0 || x>= this->rows || y < 0 || y >= this->columns)
            return false;

        if(counter % 2 == 0){
            if(this->board[x][y] != ' ')
                return false;
            this->board[x][y] = symbol;   //If valid move place the player symbol in cell
            this->n_moves++;
        }
        else{
            if(this->sub_board[x][y] != ' ')
                return false;
            this->sub_board[x][y] = symbol;   //If valid move place the player symbol in cell
            this->n_moves++;

        }
    }

    char sub_win(){
        // Check rows
        for (int i = 0; i < this->rows; i++) {
            if (sub_board[i][0] == sub_board[i][1] && sub_board[i][1] == sub_board[i][2] && sub_board[i][0] != ' ') {
                if(sub_board[i][0] == 'X') {
                    counter++;
                    return 'X';
                }
                else {
                    counter++;
                    return 'O';
                }
            }
        }

        // Check columns
        for (int i = 0; i < this->columns; i++) {
            if (sub_board[0][i] == sub_board[1][i] && sub_board[1][i] == sub_board[2][i] && sub_board[0][i] != ' ') {
                if(sub_board[0][i] == 'X') {
                    counter++;
                    return 'X';
                }
                else {
                    counter++;
                    return 'O';
                }
            }
        }

        // Check diagonals
        //if X is the winner
        if ((sub_board[0][0] == sub_board[1][1] && sub_board[1][1] == sub_board[2][2] && sub_board[0][0] == 'X') ||
            (sub_board[0][2] == sub_board[1][1] && sub_board[1][1] == sub_board[2][0] && sub_board[0][2] == 'X')) {
            counter++;
            return 'X';
        }
        //if O is the winner
        else if ((sub_board[0][0] == sub_board[1][1] && sub_board[1][1] == sub_board[2][2] && sub_board[0][0] == 'O') ||
                 (sub_board[0][2] == sub_board[1][1] && sub_board[1][1] == sub_board[2][0] && sub_board[0][2] == 'O')) {
            counter++;
            return 'O';
        }
    }

    bool is_win() override{
        // Check rows
        for (int i = 0; i < this->rows; i++) {
            if (this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != ' ') {
                counter++;
                return true;
            }
        }

        // Check columns
        for (int i = 0; i < this->columns; i++) {
            if (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != ' ') {
                counter++;
                return true;
            }
        }

        // Check diagonals
        if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != ' ') ||
            (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != ' ')) {
            counter++;
            return true;
        }

        return false;

    }

    bool is_draw() override{
        return (this->n_moves == 9 && !is_win());
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
