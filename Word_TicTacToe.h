// WordTicTacToe.h
#ifndef BOARD_GAMES_WORD_TICTACTOE_H
#define BOARD_GAMES_WORD_TICTACTOE_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <unordered_set>
#include "BoardGame_Classes.h"

using namespace std;

extern bool isRandom8;

template <typename T>
class WordTicTacToe : public Board<T> {
public:
    WordTicTacToe();
    void display_board() override;
    bool update_board(int x, int y, T symbol);
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class Word_player : public Player<T> {
public:
    Word_player(string name, T symbol);
    void getmove(int& x, int& y) override;
};

template <typename T>
class Word_randomPlayer : public RandomPlayer<T> {
public:
    Word_randomPlayer(T symbol);
    void getmove(int& x, int& y) override;
};


//  -------------------------------------Implementation
bool isRandom8 = false;

template <typename T>
WordTicTacToe<T>::WordTicTacToe() {
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

template <typename T>
void WordTicTacToe<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n|";
        for (int j = 0; j < this->columns; j++) {
            cout << setw(2) << this->board[i][j] << setw(2) << " |";
        }
        cout << "\n-------------";
    }
    cout << endl;
}

template <typename T>
bool WordTicTacToe<T>::update_board(int x, int y, T symbol) {
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == ' ' ||
    isdigit(this->board[x][y]) || symbol == 0)) {
        int count = 0;
        if (x == 0 && y == 0) count = 1;
        else if (x == 0 && y == 1) count = 2;
        else if (x == 0 && y == 2) count = 3;
        else if (x == 1 && y == 0) count = 4;
        else if (x == 1 && y == 1) count = 5;
        else if (x == 1 && y == 2) count = 6;
        else if (x == 2 && y == 0) count = 7;
        else if (x == 2 && y == 1) count = 8;
        else if (x == 2 && y == 2) count = 9;

        if (symbol == 0) {
            this->n_moves--;
            this->board[x][y] = ' ';
        } else {
            this->n_moves++;
            this->board[x][y] = toupper(symbol);
        }

        if (isRandom8 && !game_is_over()) {
            cout << "--> Random player adds in (" << count << ")" << endl;
        }

        return true;
    }
    return false;
}

template <typename T>
bool WordTicTacToe<T>::is_win() {
    unordered_set<string> dataSet;
    ifstream inputFile("dic.txt");

    if (!inputFile) {
        cerr << "Error opening file!" << endl;
        return false;
    }

    string line;
    while (getline(inputFile, line)) {
        if (!line.empty()) {
            dataSet.insert(line);
        }
    }
    inputFile.close();

    for (int i = 0; i < this->rows; i++) {
        string word = "";
        string rev_word = "";
        for (int j = 0; j < this->columns; j++) {
            word += this->board[i][j];
            rev_word += this->board[i][j];
        }
        reverse(rev_word.begin(), rev_word.end());
        if (dataSet.find(word) != dataSet.end() ||
            dataSet.find(rev_word) != dataSet.end()) {
            return true;
        }
    }

    for (int j = 0; j < this->columns; j++) {
        string word = "";
        string rev_word = "";
        for (int i = 0; i < this->rows; i++) {
            word += this->board[i][j];
            rev_word += this->board[i][j];
        }
        reverse(rev_word.begin(), rev_word.end());
        if (dataSet.find(word) != dataSet.end() ||
            dataSet.find(rev_word) != dataSet.end()) {
            return true;
        }
    }

    string diagonal = "";
    string rev_diagonal = "";
    for (int i = 0; i < this->rows; i++) {
        diagonal += this->board[i][i];
        rev_diagonal += this->board[i][i];
    }
    if (dataSet.find(diagonal) != dataSet.end() ||
        dataSet.find(rev_diagonal) != dataSet.end()) {
        return true;
    }

    diagonal = "";
    rev_diagonal = "";
    for (int i = 0; i < this->rows; i++) {
        diagonal += this->board[i][this->columns - i - 1];
        rev_diagonal += this->board[i][this->columns - i - 1];
    }
    if (dataSet.find(diagonal) != dataSet.end() ||
        dataSet.find(rev_diagonal) != dataSet.end()) {
        return true;
    }

    return false;
}

template <typename T>
bool WordTicTacToe<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool WordTicTacToe<T>::game_is_over() {
    return (is_win() || is_draw());
}

template <typename T>
Word_player<T>::Word_player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Word_player<T>::getmove(int& x, int& y) {
    isRandom8 = false;
    int index;
    char letter;
    cout << "--> (" << this->getname() << ')';
    cout << "Enter the character you want to add:";
    cin >> letter;
    while (!isalpha(letter)) {
        cout << "Enter a character please:";
        cin >> letter;
    }
    cout << "Enter the index of box you want to add in:";
    cin >> index;

    if (index == 1 || index == 2 || index == 3) {
        x = 0;
    } else if (index == 4 || index == 5 || index == 6) {
        x = 1;
    } else if (index == 7 || index == 8 || index == 9) {
        x = 2;
    }

    if (index == 1 || index == 4 || index == 7) {
        y = 0;
    } else if (index == 2 || index == 5 || index == 8) {
        y = 1;
    } else if (index == 3 || index == 6 || index == 9) {
        y = 2;
    }
    this->symbol = letter;
}

template <typename T>
Word_randomPlayer<T>::Word_randomPlayer(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void Word_randomPlayer<T>::getmove(int& x, int& y) {
    this->symbol = 'A' + rand() % 26;
    x = rand() % this->dimension;
    y = rand() % this->dimension;
    isRandom8 = true;
}


#endif // BOARD_GAMES_WORD_TICTACTOE_H
