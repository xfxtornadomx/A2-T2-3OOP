cmake_minimum_required(VERSION 3.27)
project(Assignment_Demo_2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Assignment_Demo_2
        3x3X_O.h
        BoardGame_Classes.h
        main.cpp
        pyramidBoard.h
        wordX_O.h
        ultimateTicTacToe.h
        numerical.h
        connect4.h
        reverse.h
        5x5X_O.h
        SUS.h)
