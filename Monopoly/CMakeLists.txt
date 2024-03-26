cmake_minimum_required(VERSION 2.84 FATAL_ERROR)
project(ProgettoFinale)

add_executable(ProgettoFinale src/Caselle.cpp src/Computer.cpp src/Dado.cpp src/GameManagement.cpp src/Human.cpp src/main.cpp src/Player.cpp src/Tabellone.cpp)
include_directories(include)

