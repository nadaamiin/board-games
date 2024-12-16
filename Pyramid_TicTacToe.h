#ifndef BOARD_GAMES_PYRAMID_TICTACTOE_H
#define BOARD_GAMES_PYRAMID_TICTACTOE_H

#include <iostream>
#include <iomanip>
#include "BoardGame_Classes.h"

using namespace std;

bool isRandom0 = false;
template <typename T>
class PyramidTicTacToe : public Board<T> {
public:
    PyramidTicTacToe();
    void display_board() override;
    bool update_board(int x, int y, T symbol) override;
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class Pyramid_player : public Player<T> {
public:
    Pyramid_player(string name, T symbol);
    void getmove(int& x, int& y) override;
};

template <typename T>
class Pyramid_randomPlayer : public RandomPlayer<T> {
public:
    Pyramid_randomPlayer(T symbol);
    void getmove(int& x, int& y) override;
};




// ---------------Implementation

template <typename T>
PyramidTicTacToe<T>::PyramidTicTacToe() {
    this->rows = 3;
    this->columns = 5;
    int count = 1;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; ++i) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; ++j) {
            this->board[i][j] = ' ';
            if ((i == 0 && j == 2) || (i == 1 && j >= 1 && j <= 3) || i == 2) {
                this->board[i][j] = '0' + count;
                count++;
            }
            this->n_moves = 0;
        }
    }
}

template <typename T>
void PyramidTicTacToe<T>::display_board() {
    cout << setw(14) << "| " << this->board[0][2] << " |\n";
    cout << setw(8) << "| " << this->board[1][1] << " | | "
         << this->board[1][2] << " | | " << this->board[1][3] << " |\n";
    cout << "| " << this->board[2][0] << " | | " << this->board[2][1] << " | | "
         << this->board[2][2] << " | | " << this->board[2][3] << " | | "
         << this->board[2][4] << " |\n";
}

template <typename T>
bool PyramidTicTacToe<T>::update_board(int x, int y, T symbol) {
    if (((x == 0 && y == 2) ||
         (x == 1 && y >= 1 && y <= 3) ||
         (x == 2 && y >= 0 && y <= 4)) &&
        (this->board[x][y] != 'X' && this->board[x][y] != 'O' || symbol == 0)) {
        int count = 0;
        if (x == 0 && y == 2) count = 1;
        else if (x == 1 && y == 1) count = 2;
        else if (x == 1 && y == 2) count = 3;
        else if (x == 1 && y == 3) count = 4;
        else if (x == 2 && y == 0) count = 5;
        else if (x == 2 && y == 1) count = 6;
        else if (x == 2 && y == 2) count = 7;
        else if (x == 2 && y == 3) count = 8;
        else if (x == 2 && y == 4) count = 9;
        if (symbol == 0) {
            this->n_moves--;

            this->board[x][y] = '0' + count;
        } else {
            this->n_moves++;
            this->board[x][y] = toupper(symbol);
        }
        if(isRandom0) {
            cout << "--> Random player adds in (" << count << ')' << endl;
        }
        return true;
    }
    return false;
}

template <typename T>
bool PyramidTicTacToe<T>::is_win() {
    if ((this->board[0][2] == this->board[1][1] && this->board[0][2] == this->board[2][0] && this->board[0][2] != ' ') ||
        (this->board[0][2] == this->board[1][3] && this->board[1][3] == this->board[2][4] && this->board[0][2] != ' ')) {
        return true;
    }
    if ((this->board[0][2] == this->board[1][2] && this->board[1][2] == this->board[2][2] && this->board[0][2] != ' ') ||
        (this->board[1][1] == this->board[1][2] && this->board[1][2] == this->board[1][3] && this->board[1][1] != ' ')) {
        return true;
    }
    for (int i = 0; i < this->columns - 2; ++i) {
        if (this->board[2][i] == this->board[2][i + 1] &&
            this->board[2][i] == this->board[2][i + 2] &&
            this->board[2][i] != ' ') {
            return true;
        }
    }
    return false;
}

template <typename T>
bool PyramidTicTacToe<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool PyramidTicTacToe<T>::game_is_over() {
    return (is_win() || is_draw());
}

template <typename T>
Pyramid_player<T>::Pyramid_player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Pyramid_player<T>::getmove(int& x, int& y) {
    int index;
    cout << "--> (" << this->getname() << ')';
    cout << " Enter the index of box you want to add in:";
    cin >> index;

    if (index == 1) {
        x = 0;
    } else if (index == 2 || index == 3 || index == 4) {
        x = 1;
    } else if (index >= 5 && index <= 9) {
        x = 2;
    }

    if (index == 5) {
        y = 0;
    } else if (index == 1 || index == 3 || index == 7) {
        y = 2;
    } else if (index == 6 || index == 2) {
        y = 1;
    } else if (index == 8 || index == 4) {
        y = 3;
    } else if (index == 9) {
        y = 4;
    }
}

template <typename T>
Pyramid_randomPlayer<T>::Pyramid_randomPlayer(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void Pyramid_randomPlayer<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % 5;
    isRandom0 = true;
}

#endif //BOARD_GAMES_PYRAMID_TICTACTOE_H
