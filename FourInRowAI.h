#ifndef BOARD_GAMES_FOURINROWAI_H
#define BOARD_GAMES_FOURINROWAI_H
#include "BoardGame_Classes.h"
#include <limits>
#include <algorithm>
using namespace std;
static bool fisrtMove = true;

template <typename T>
class ConnectFour_AI_Player : public Player<T> {
//If isMaximizing is true:
//The current player is trying to maximize their score. This player aims to find the best possible move for themselves.
//If isMaximizing is false:
//The current player is trying to minimize their opponent's score. This player aims to block the opponent's best moves or create difficulties for them.
private:
    int calculateMinMax(T s, bool isMaximizing) {
        if (this->boardPtr->is_win()) {
            return isMaximizing ? -1 : 1; // AI loses (-1) or wins (+1)
        } else if (this->boardPtr->is_draw()) {
            return 0; // Draw
        }

        int bestValue = isMaximizing ? numeric_limits<int>::min() : numeric_limits<int>::max();
        T aiSymbol = 'O';         // AI is always 'O'
        T opponentSymbol = 'X';   // Opponent is always 'X'

        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 7; ++j) {
                if (this->boardPtr->update_board(i, j, s)) {
                    // Recursively calculate MinMax for the opponent
                    int value = calculateMinMax(isMaximizing ? opponentSymbol : aiSymbol, !isMaximizing);
                    this->boardPtr->update_board(i, j, 0); // Undo move

                    // Update the best value based on maximizing/minimizing
                    if (isMaximizing) {
                        bestValue = max(bestValue, value);
                    } else {
                        bestValue = min(bestValue, value);
                    }
                }
            }
        }

        return bestValue;
    }

    pair<int, int> getBestMove() {
        if (fisrtMove) {
            fisrtMove = false;
            if (this->boardPtr->update_board(0, 3,'O')) {
                return {0, 3};
            }
            if (this->boardPtr->update_board(0, 4,'O')) {
                return {0, 4};
            }
        }

        int bestValue = numeric_limits<int>::min();
        pair<int, int> bestMove = {-1, -1};
        T opponentSymbol = (this->symbol == 'X') ? 'O' : 'X';

        // First, check the middle columns (3 and 4) for availability
        // Modify here to prioritize columns 3 and 4 before proceeding further.

        // Check if we can win in the next move
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 7; ++j) {
                if (this->boardPtr->update_board(i, j, this->symbol)) {
                    if (this->boardPtr->is_win()) {
                        this->boardPtr->update_board(i, j, 0); // Undo move
                        return {i, j}; // Winning move found
                    }
                    this->boardPtr->update_board(i, j, 0); // Undo move
                }
            }
        }

        // Second, check if the opponent can win in their next move and block them
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 7; ++j) {
                if (this->boardPtr->update_board(i, j, opponentSymbol)) {
                    if (this->boardPtr->is_win()) {
                        this->boardPtr->update_board(i, j, 0); // Undo move
                        return {i, j}; // Block opponent's winning move
                    }
                    this->boardPtr->update_board(i, j, 0); // Undo move
                }
            }
        }

        // If no immediate win or block, use MinMax to find the best move
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 7; ++j) {
                if (this->boardPtr->update_board(i, j, this->symbol)) {
                    int moveValue = calculateMinMax(this->symbol, false);
                    this->boardPtr->update_board(i, j, 0); // Undo move

                    if (moveValue > bestValue) {
                        bestMove = {i, j};
                        bestValue = moveValue;
                    }
                }
            }
        }

        return bestMove;
    }

public:
    ConnectFour_AI_Player(T symbol);

    void getmove(int& x, int& y) override{
        isAI2 = true;
        pair<int, int> bestMove = getBestMove();
        y = bestMove.second;
        cout << "AI chooses column: " << y << endl;
    }

};

// Constructor for the templated class
template <typename T>
ConnectFour_AI_Player<T>::ConnectFour_AI_Player(T symbol) : Player<T>(symbol) {
    this->name = "AI Player";
}

#endif //BOARD_GAMES_FOURINROWAI_H
