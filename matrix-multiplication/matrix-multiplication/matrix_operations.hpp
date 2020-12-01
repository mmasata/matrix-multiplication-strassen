#include "matrix.hpp"


matrix* addMatrix(matrix* left, matrix* right, int rows, int columns);
matrix* substractMatrix(matrix* left, matrix* right, int rows, int columns);
void fillSubmatrix(matrix* origin, matrix* submatrix, int rowsFrom, int rowsTo, int columnsFrom, int columnsTo);
void fillOriginFromSubmatrixes(matrix* origin, matrix* submatrix, int rowsFrom, int rowsTo, int columnsFrom, int columnsTo);