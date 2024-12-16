cmake_minimum_required(VERSION 3.28)
project(board_games)

set(CMAKE_CXX_STANDARD 23)

add_executable(board_games
        BoardGame_Classes.h
        Pyramid_TicTacToe.h
        Word_TicTacToe.h
        FourInRow.h
        NumericalTicTacToe.h
        Ultimate_TTT.h
        main.cpp
        Tic_Tac_Toe_Board.h
        Misere_Tic_Tac_Toe.h
        Pyramid_AI.h
        Pyramid_AI.h
        WordGame_AI.h
)
