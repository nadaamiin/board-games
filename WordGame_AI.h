#ifndef BOARD_GAMES_WORDGAME_AI_H
#define BOARD_GAMES_WORDGAME_AI_H

#include "BoardGame_Classes.h"
#include "Word_TicTacToe.h"
#include <limits>
#include <algorithm>
#include <fstream>
#include <unordered_set>
#include <string>

using namespace std;

template <typename T>
class Word_MinMax_Player : public Player<T> {
public:
    Word_MinMax_Player(T symbol);

    void getmove(int& x, int& y) override;

private:
    int calculateMinMax(T s, bool isMaximizing);
    std::pair<int, int> getBestMove();
    char selectCharacter(int x, int y, T symbol);
    bool is_word_valid(int x, int y);

//    unordered_set<string> loadDictionary();

    unordered_set<string> dictionary; // Store valid words from the dictionary
};

//--------------------------------------- IMPLEMENTATION

// Constructor for the templated class
template <typename T>
Word_MinMax_Player<T>::Word_MinMax_Player(T symbol) : Player<T>(symbol) {
    this->name = "AI Word Player";
//    dictionary = loadDictionary(); // Load the dictionary
}

// Load dictionary words into a set
//template <typename T>
//unordered_set<string> Word_MinMax_Player<T>::loadDictionary() {
//    unordered_set<string> dataSet;
//    ifstream inputFile("dic.txt");
//
//    if (!inputFile) {
//        cerr << "Error opening dictionary file!" << endl;
//        return dataSet;
//    }
//
//    string line;
//    while (getline(inputFile, line)) {
//        if (!line.empty()) {
//            dataSet.insert(line);
//        }
//    }
//    inputFile.close();
//    return dataSet;
//}
template <typename T>
bool Word_MinMax_Player<T>::is_word_valid(int x, int y) {
    // Combine letters in the row, column, and diagonals containing (x, y)
    string rowWord, colWord, diag1Word, diag2Word;

    // Get the row word
    for (int j = 0; j < 3; ++j) {
        char c = this->boardPtr->get_cell(x, j); // Retrieve the character at (x, j)
        if (c != 0) rowWord += c; // Add to the row string if not empty
    }

    // Get the column word
    for (int i = 0; i < 3; ++i) {
        char c = this->boardPtr->get_cell(i, y); // Retrieve the character at (i, y)
        if (c != 0) colWord += c; // Add to the column string if not empty
    }

    // Get the main diagonal word (if (x, y) is on the main diagonal)
    if (x == y) {
        for (int i = 0; i < 3; ++i) {
            char c = this->boardPtr->get_cell(i, i); // Retrieve the diagonal cell
            if (c != 0) diag1Word += c;
        }
    }

    // Get the anti-diagonal word (if (x, y) is on the anti-diagonal)
    if (x + y == 2) {
        for (int i = 0; i < 3; ++i) {
            char c = this->boardPtr->get_cell(i, 2 - i); // Retrieve the anti-diagonal cell
            if (c != 0) diag2Word += c;
        }
    }

    // Check if any of the words are valid
    return (dictionary.count(rowWord) > 0 || dictionary.count(colWord) > 0 ||
            dictionary.count(diag1Word) > 0 || dictionary.count(diag2Word) > 0);
}


// Method to get the best move for the player
template <typename T>
void Word_MinMax_Player<T>::getmove(int& x, int& y) {
    std::pair<int, int> bestMove = getBestMove();
    x = bestMove.first;
    y = bestMove.second;
    this->symbol = selectCharacter(x, y, this->symbol); // Choose a valid character
}

// Minimax algorithm to evaluate the board
template <typename T>
int Word_MinMax_Player<T>::calculateMinMax(T currentSymbol, bool isMaximizing) {
    // Check terminal states (win/draw)
    if (this->boardPtr->is_win()) {
        return isMaximizing ? -1 : 1; // Negative score for a maximizing player on loss
    } else if (this->boardPtr->is_draw()) {
        return 0; // Draw results in a neutral score
    }

    int bestValue = isMaximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();

    // Iterate through all possible moves
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (this->boardPtr->is_empty(i, j)) { // Check if cell is empty
                for (char c = 'A'; c <= 'Z'; ++c) { // Try all letters
                    if (this->boardPtr->update_board(i, j, c)) { // Make a move
                        if (is_word_valid(i, j)) { // Check if a valid word is formed
                            // Recursive evaluation of the next state
                            int value = calculateMinMax(currentSymbol, !isMaximizing);
                            bestValue = isMaximizing
                                        ? std::max(bestValue, value)
                                        : std::min(bestValue, value);

                            // Undo the move
                            this->boardPtr->update_board(i, j, 0);
                        }
                    }
                }
            }
        }
    }

    return bestValue;
}

// Select a character for the given move without directly accessing board
template <typename T>
char Word_MinMax_Player<T>::selectCharacter(int x, int y, T symbol) {
    string row, column, diagonal1, diagonal2;

    for (int i = 0; i < 3; ++i) {
        row += this->boardPtr->get(i, y);      // Get the ith element of the column
        column += this->boardPtr->get(x, i);  // Get the jth element of the row
        diagonal1 += this->boardPtr->get(i, i);
        diagonal2 += this->boardPtr->get(i, 2 - i);
    }

    for (char c = 'A'; c <= 'Z'; ++c) {
        if (dictionary.count(row + c) || dictionary.count(column + c) ||
            dictionary.count(diagonal1 + c) || dictionary.count(diagonal2 + c)) {
            return c;
        }
    }
    return 'A'; // Default if no match is found
}

// Find the best move using the minimax algorithm
template <typename T>
std::pair<int, int> Word_MinMax_Player<T>::getBestMove() {
    int bestValue = std::numeric_limits<int>::min();
    std::pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (this->boardPtr->is_empty(i, j)) { // Check if cell is empty
                for (char c = 'A'; c <= 'Z'; ++c) { // Try all letters
                    if (this->boardPtr->update_board(i, j, c)) {
                        if (is_word_valid(i, j)) { // Check if a valid word is formed
                            int moveValue = calculateMinMax(this->symbol, false);
                            if (moveValue > bestValue) {
                                bestValue = moveValue;
                                bestMove = {i, j};
                            }

                            // Undo the move
                            this->boardPtr->update_board(i, j, 0);
                        }
                    }
                }
            }
        }
    }

    return bestMove;
}

#endif //BOARD_GAMES_WORDGAME_AI_H
