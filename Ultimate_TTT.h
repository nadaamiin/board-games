#ifndef BOARD_GAMES_ULTIMATE_TTT_H
#define BOARD_GAMES_ULTIMATE_TTT_H

#include <iostream>
#include <iomanip>
#include <vector>
#include "BoardGame_Classes.h"

using namespace std;

template <typename T>
class Sub_boards{
private:
    vector<vector<T>> sub_board;
    char winner;
    int moves;
public:
    // Initialize the sub board with numbers to make it easy for the players
    Sub_boards() : sub_board(3, vector<T>(3)), winner(' '), moves(0){
        int count = 1;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                sub_board[i][j] = '0' + count;
                count++;
            }
        }
    }
    void display_subBoard(int row){
        // If there is a winner print the symbol of the winner in the center
        if (winner != ' ') {
            if (row == 1) {
                cout << setw(8) << winner << setw(12);
            }
            else {
                cout << setw(8) << " " << setw(12);
            }
        }
        else if(is_subDraw()){
            if (row == 1) {
                cout << setw(8) << "Draw" << setw(12);
            }else {
                cout << setw(8) << " " << setw(12);
            }
        }
        // If there is no winner or draw print the sub-board
        else {
            for (int i = 0; i < 3; i++) {
                cout << "[" << setw(2) << sub_board[row][i] << setw(2) << "]";
            }
        }
    }
    bool update_subBoard(int x, int y, T symbol, int index){
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

        // Only update if move is valid
        if (!(x < 0 || x >= 3 || y < 0 || y >= 3) && (sub_board[x][y] == ' ' ||
        isdigit(sub_board[x][y]) || symbol == 0)) {
            if (symbol == 0){
                moves--;
                sub_board[x][y] = ' ';
            }
            else {
                moves++;
                sub_board[x][y] = toupper(symbol);
            }
            return true;
        }
        return false;
    }
    char sub_win() {
        // Check rows
        for (int i = 0; i < 3; i++) {
            if (sub_board[i][0] == sub_board[i][1] && sub_board[i][1] == sub_board[i][2]
            && sub_board[i][0] != ' ') {
                winner = sub_board[i][0];
                return winner;
            }
        }

        // Check columns
        for (int i = 0; i < 3; i++) {
            if (sub_board[0][i] == sub_board[1][i] && sub_board[1][i] == sub_board[2][i]
            && sub_board[0][i] != ' ') {
                winner = sub_board[0][i];
                return winner;
            }
        }

        // Check diagonals
        if ((sub_board[0][0] == sub_board[1][1] && sub_board[1][1] == sub_board[2][2]
            && sub_board[0][0] != ' ') ||
            (sub_board[0][2] == sub_board[1][1] && sub_board[1][1] == sub_board[2][0]
            && sub_board[0][2] != ' ')) {
            winner = sub_board[1][1];
            return winner;
        }

        return ' ';
    }
    // Getter to access winner attribute
    char get_winner() {
        return winner;
    }
    bool is_subDraw() {
        return (moves == 9 && sub_win() == ' ');
    }
};

template <typename T>
class Ultimate_TTT : public Board<T> {
private:
    vector<vector<Sub_boards<T>>> sub_board;
public:
    Ultimate_TTT() : sub_board(3, vector<Sub_boards<T>>(3)){
        this->rows = 3;
        this->columns = 3;
        int count = 1;
        this->board = new char*[this->rows];
        for (int i = 0; i < this->rows; ++i) {
            this->board[i] = new char[this->columns];
            for (int j = 0; j < this->columns; ++j) {
                this->board[i][j] = 0;
                count++;
            }
            this->n_moves = 0;
        }
    }
    void display_board() override{
        cout << endl << setw(13) << 0 << " " << setw(19) << 1 << " " << setw(19) << 2 << endl;
        for (int i = 0; i < 3; i++) {
            for (int k = 0; k < 3; ++k) {
                if (k == 1) {
                    cout << setw(3) << i << "  ";
                } else {
                    cout << setw(5) << " ";
                }
                for (int j = 0; j < 3; j++) {
                    sub_board[i][j].display_subBoard(k);
                    if(j < 2) cout << "  |  ";
                }
                cout << endl;
            }
            if(i < 2){
                cout << setw(5) << " " << "--------------------------------------------------------\n";
            }
        }
    }
    bool update_board(int x, int y, T symbol) override{
        // Validate that x and y are within the main board
        if (x < 0 || x >= 3 || y < 0 || y >= 3) {
            return false;
        }
        // Object to access the sub-board methods and attributes
        Sub_boards<T>& newBoard = sub_board[x][y];

        // If There is a winner in the sub-board prevent the players to choose it
        if (newBoard.get_winner() != ' ') {
            cout << "This sub-board has already been won by " << newBoard.get_winner() << "!" << endl;
            return false;
        }
        // If There is a draw in the sub-board prevent the players to choose it
        if(newBoard.is_subDraw()){
            cout << "This sub-board is a draw, you can't add your symbol here" << endl;
            return false;
        }

        // Let the user enter the index of the box in sub-board
        int index;
        cout << "Enter the number of the box you want to play in:";
        cin >> index;

        // Update the sub-board
        if (newBoard.update_subBoard(x, y, symbol, index)) {
            // Check if the sub-board has a winner
            char subWinner = newBoard.sub_win();
            if (subWinner == 'X' || subWinner == 'O') {
                // Update the overall board with the sub-winner
                this->board[x][y] = subWinner;
            }
            // Increment the number of moves if any update happen in any sub-board
            this->n_moves++;
            return true;
        }
        return false;
    }

    bool is_win() override{
        // Check rows for a winner
        for (int i = 0; i < 3; i++) {
            if (this->board[i][0] == this->board[i][1] &&
                this->board[i][1] == this->board[i][2] &&
                this->board[i][0] != 0) {  // Ensure it's not empty
                return true;
            }
        }

        // Check columns for a winner
        for (int i = 0; i < 3; i++) {
            if (this->board[0][i] == this->board[1][i] &&
                this->board[1][i] == this->board[2][i] &&
                this->board[0][i] != 0) {  // Ensure it's not empty
                return true;
            }
        }

        // Check diagonals for a winner
        if ((this->board[0][0] == this->board[1][1] &&
             this->board[1][1] == this->board[2][2] &&
             this->board[0][0] != 0) ||  // Main diagonal
            (this->board[0][2] == this->board[1][1] &&
             this->board[1][1] == this->board[2][0] &&
             this->board[0][2] != 0)) {  // Anti-diagonal
            return true;
        }

        return false;    }

    bool is_draw() override{
        return (this->n_moves == 81 && !is_win());
    }

    bool game_is_over() override{
        return is_win() || is_draw();
    }

};

template <typename T>
class Ultimate_player : public Player<T>{
public:
    Ultimate_player(string name, T symbol) : Player<T>(name, symbol){}
    void getmove(int& x, int& y) override{
        cout << "Enter the index of the box you want to play in(row then column):";
        cin >> x >> y;
    }
};

#endif // BOARD_GAMES_ULTIMATE_TTT_H
