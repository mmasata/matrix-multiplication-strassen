#include "matrix_operations.hpp"


/*
	Secteni dvou matic
*/
matrix* addMatrix(matrix* left, matrix* right, int rows, int columns)
{
	matrix* result = new matrix(rows, columns);
	for (int i = 0; i < rows; i++) {
		for (int y = 0; y < columns; y++) {
			result->data[i][y] = left->data[i][y] + right->data[i][y];
		}
	}
	return result;
}

/*
	Odecteni dvou matic
*/
matrix* substractMatrix(matrix* left, matrix* right, int rows, int columns)
{
	matrix* result = new matrix(rows, columns);
	for (int i = 0; i < rows; i++) {
		for (int y = 0; y < columns; y++) {
			result->data[i][y] = left->data[i][y] - right->data[i][y];
		}
	}
	return result;
}

/*
	Naplneni submatice z puvodni matice
*/
void fillSubmatrix(matrix* origin, matrix* submatrix, int rowsFrom, int rowsTo, int columnsFrom, int columnsTo)
{
	int subCounterRow = 0;
	int x = rowsFrom;
	for (x; x < rowsTo; x++) {
		int subCounterCol = 0;
		int y = columnsFrom;
		for (y; y < columnsTo; y++) {
			submatrix->data[subCounterRow][subCounterCol] = origin->data[x][y];
			subCounterCol++;
		}
		subCounterRow++;
	}
}

/*
	Naplneni matice ze submatic
	Zpatecni operace k fillSubmatrix
*/
void fillOriginFromSubmatrixes(matrix* origin, matrix* submatrix, int rowsFrom, int rowsTo, int columnsFrom, int columnsTo)
{
	int subCounterRow = 0;
	int x = rowsFrom;
	for (x; x < rowsTo; x++) {
		int subCounterCol = 0;
		int y = columnsFrom;
		for (y; y < columnsTo; y++) {
			origin->data[x][y] = submatrix->data[subCounterRow][subCounterCol];
			subCounterCol++;
		}
		subCounterRow++;
	}
}
