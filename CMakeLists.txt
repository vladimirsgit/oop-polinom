cmake_minimum_required(VERSION 3.25)
project(PolinomOOP)

set(CMAKE_CXX_STANDARD 17)

add_executable(PolinomOOP Polinom.h Complex.cpp Complex.h main.cpp UserInterface.cpp)
