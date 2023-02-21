cmake_minimum_required(VERSION 3.20)
project(alu-simulator)

add_compile_options(-Wall -Wextra -pedantic -g -std=c++17)

add_executable(test-gates
  test-gates.cpp
  truth.cpp
  gates.cpp
  wire.cpp
)
