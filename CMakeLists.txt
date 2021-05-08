cmake_minimum_required(VERSION 3.15)
project(P2_Placzek)

set(CMAKE_CXX_STANDARD 14)

add_executable(P2_Placzek main.cpp Column.cpp Player.cpp tools.cpp enums.hpp enums.cpp Game.cpp Dice.cpp Board.cpp Board.hpp CList.cpp CList.hpp BadPlayer.hpp)