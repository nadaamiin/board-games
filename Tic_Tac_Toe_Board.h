#ifndef BOARD_GAMES_TIC_TAC_TOE_H
#define BOARD_GAMES_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <random>
#include <ctime>

//Player<char>* winner_p[2];

template <typename T>
class Tic_Tac_Toe_Board  : public Board<char>{
private:
    Player<char>* players[2];  // Add this member to the class

public:

    Tic_Tac_Toe_Board(){
        rows = 5;
        columns = 5;

        // Dynamically allocate the 2D board
        board = new char*[rows];
        for (int i = 0; i < rows; ++i) {
            board[i] = new char[columns];
            // Initialize board with empty spaces
            for (int j = 0; j < columns; ++j) {
                board[i][j] = ' ';
            }
        }
    }

    // Destructor to free dynamically allocated memory
    ~Tic_Tac_Toe_Board() {
        for (int i = 0; i < this->rows; ++i) {
            delete[] this->board[i];
        }
        delete[] this->board;
        // Optionally, reset player pointers to avoid dangling pointers
        players[0] = nullptr;
        players[1] = nullptr;
    }

    // Method to set players
    void setPlayers(Player<char>* player1, Player<char>* player2) {
        this->players[0] = player1;
        this->players[1] = player2;
    }



    // update_board implementation
    bool update_board(int x, int y, char symbol) override {

        //Check if move within boundaries
        if(x < 0 || x>= rows || y < 0 || y >= columns) {
            cerr<< "Invalid move!" << endl;
            return false;
        }

        //Check if the cell is empty to allow move
        if(board[x][y] != ' ')
            return false;

        //cout << "Updating board at (" << x << ", " << y << ") with " << symbol << endl;
        board[x][y] = symbol;   //If valid move place the player symbol in cell
        n_moves++;
       // cout << "Move count: " << n_moves << endl;
        return true;

    }

    //display_board implementation
    void display_board() override{
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                cout<< board[i][j];
                if (j < columns - 1) cout << " | ";
            }
            cout<< endl;
            if (i < rows - 1) cout << "---------------" << endl;
        }

    }

    int playerCount(char symbol){
        int player_count = 0;

        // Horizontal Sequence Counting
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col <= columns - 3; ++col) {
                if (board[row][col] == symbol && board[row][col+1] == symbol && board[row][col+2] == symbol) {
                    player_count++;
                }
            }
        }

        // Vertical Sequence Counting
        for (int col = 0; col < columns; ++col) {
            for (int row = 0; row <= rows - 3; ++row) {
                if (board[row][col] == symbol && board[row+1][col] == symbol && board[row+2][col] == symbol) {
                    player_count++;
                }
            }
        }

        // Diagonal (Top-Left to Bottom-Right) Sequences
        for (int row = 0; row <= rows - 3; ++row) {
            for (int col = 0; col <= columns - 3; ++col) {
                // Check diagonal from top-left to bottom-right
                if (board[row][col] == symbol && board[row+1][col+1] == symbol && board[row+2][col+2] == symbol) {
                    player_count++;
                }
            }
        }

        // Diagonal (Top-Right to Bottom-Left) Sequences
        for (int row = 0; row <= rows - 3; ++row) {
            for (int col = 2; col < columns; ++col) {
                // Check diagonal from top-right to bottom-left
                if (board[row][col] == symbol && board[row+1][col-1] == symbol && board[row+2][col-2] == symbol) {
                    player_count++;
                }
            }
        }

        return player_count;

    }

    //is_win implementation
    bool is_win() override {

        if(n_moves == 24) {
            int count_p1 = playerCount('X');
            int count_p2 = playerCount('O');

            if (count_p1 > count_p2 ) {
                cout<<  "player 1 wins!" << endl;
                // Access and update player names
                string winner_name = players[0]->getname();  // Get Player 1's name
                string& loser_name = const_cast<string&>(static_cast<const string&>(players[1]->getname()));

                loser_name = winner_name; // Set Player 2's name to Player 1's name

                return true;
            }
            else if(count_p1 < count_p2){
                cout<< "Player 2 is the Winner!" << endl;
                return true;
            }

        }

        return false;
    }


    bool is_draw() override{
        return (n_moves == 24 && !is_win());
    }

    bool game_is_over() override{
       return is_win() || is_draw();

    }

};



template <typename T>
class HumanPlayer : public Player<char> {
public:
    // Constructor using parent class constructors
    HumanPlayer(string name, char symbol) : Player<char>(name, symbol) {}

    // Implement getmove method to get user input
    void getmove(int& x, int& y) override {
        cout << this->name << ", enter your move (row [0-4] col [0-4]): ";
        cin >> x >> y;

    }

    // Helper method to set the name
    void setName(const string& newName) {
        this->name = newName;
    }

};

// Random Computer Player Template
template <typename T>
class RandomComputerPlayer : public RandomPlayer<T> {
public:
    // Constructor
    RandomComputerPlayer(T symbol) : RandomPlayer<T>(symbol) {
        this->dimension = 5;
        this->name = "Random Computer Player";
        srand(static_cast<unsigned int>(time(0)));   // Seed the random number generator
    }

    // Generate random move
    void getmove(int& x, int& y) override {
        x = rand() % this->dimension;
        y = rand() % this->dimension;
    }

    // Helper method to set the name
    void setName(const string& newName) {
        this->name = newName;
    }


};


#endif //BOARD_GAMES_TIC_TAC_TOE_H
