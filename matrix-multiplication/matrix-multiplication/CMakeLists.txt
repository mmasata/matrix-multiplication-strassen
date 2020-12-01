# CMakeList.txt : CMake project for matrix-multiplication, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (matrix-multiplication "main.cpp" "strassen.hpp" "strassen.cpp" "matrix.hpp" "matrix.cpp" "matrix_operations.hpp" "matrix_operations.cpp")

# TODO: Add tests and install targets if needed.
