#ifndef BOARD_GAMES_WORD_TICTACTTOE_H
#define BOARD_GAMES_WORD_TICTACTTOE_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <set>
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
    bool is_win(){
        set<string> dataSet; // Create a set to store unique lines
        ifstream inputFile("dic.txt"); // Open the file

        if (!inputFile) { // Check if the file is successfully opened
            cerr << "Error opening file!" << endl;
            return 1;
        }

        string line;
        while (getline(inputFile, line)) { // Read each line
            if (!line.empty()) { // Skip empty lines
                dataSet.insert(line); // Add the line to the set
            }
        }
        inputFile.close(); // Close the file

        string word;
        // Check rows and columns
        for (int i = 0; i < this->rows; i++) {
            word = this->board[i][0] + this->board[i][1] + this->board[i][2];
            auto it = dataSet.find(word);
            // Check if the element was found
            if (it != dataSet.end()) {
                return true;
            }
            return false;

        }
        for (int j = 0; j < this->columns; j++) {
            word = this->board[0][j] + this->board[1][j] + this->board[2][j];
            auto it = dataSet.find(word);
            // Check if the element was found
            if (it != dataSet.end()) {
                return true;
            }
            return false;

        }
        word = this->board[0][0] + this->board[1][1] + this->board[2][2];
        auto it1 = dataSet.find(word);
        // Check if the element was found
        if (it1 != dataSet.end()) {
            return true;
        }
        return false;

        word = this->board[0][2] + this->board[1][1] + this->board[2][0];
        auto it2 = dataSet.find(word);
        // Check if the element was found
        if (it2 != dataSet.end()) {
            return true;
        }
        return false;
    }
    bool is_draw(){
        return (this->n_moves == 9 && !is_win());
    }
    bool game_is_over(){
        return (is_win() || is_draw());
    }
};
template <typename T>
class Word_player : public Player<T>{
public:
    Word_player(string name, T symbol) : Player<T>(name, symbol){}
    void getmove(int& x, int& y) override{
        int index;
        char letter;
        cout << "Enter the character you want to add:";
        cin >> letter;
        cout << "Enter the index of box you want to add in:";
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
            y = 2;
        }else if(index == 3 || index == 6 || index == 9){
            y = 1;
        }
        this->symbol = letter;
    }
};
template <typename T>
class Word_randomPlayer : public RandomPlayer<T> {
public:
    Word_randomPlayer(T symbol) : RandomPlayer<T>(symbol) {
        this->dimension = 3;
        this->name = "Random Computer Player";
        srand(static_cast<unsigned int>(time(nullptr)));  // Seed the random number generator
    }
    void getmove(int& x, int& y) override{
        x = rand() % this->dimension;  // Random number between 0 and 2
        y = rand() % this->dimension;
    }
};



#endif //BOARD_GAMES_WORD_TICTACTTOE_H
