#pragma once
#include<string>
#include <iostream>
#include "matrix.hpp"


matrix* multiplyMatrix(matrix* left, matrix* right);
bool validateColumnsAndRowsSize(matrix* left, matrix* right);
matrix* doStrassen(matrix* left, matrix* right, int size);

