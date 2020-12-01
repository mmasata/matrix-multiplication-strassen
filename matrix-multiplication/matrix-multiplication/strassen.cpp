#include "strassen.hpp"
#include <exception>
#include "matrix_operations.hpp"

/*
	Vypocita a nasledne vrati vysledek.
*/
matrix* multiplyMatrix(matrix* left, matrix* right) {
	if (validateColumnsAndRowsSize(left, right)) {
		matrix* result = doStrassen(left, right, left->columns);
		return result;
	}
	else {
		throw std::exception("Columns of first matrix are not same as rows of second matrix.");
	}
}

/*
	Validator zda lze nasobit matice mezi sebou.
*/
bool validateColumnsAndRowsSize(matrix* left, matrix* right)
{
	//pocet sloupcu prvni matice musi byt rovno poctu radku druhe matice
	return (left->columns == right->rows);
}

matrix* doStrassen(matrix* left, matrix* right, int size)
{
	if (size == 1) {
		//pri matici 1x1 se jedna v podstate o obycejna cisla, tudiz pravidla nasobeni budou totozna
		matrix* result = new matrix(1, 1);
		result->data[0][0] = left->data[0][0] * right->data[0][0];
		return result;
	}
	else {
		int currSize = size / 2;

		//bude obsahovat rows 1 az polovina, columns 1 az polovina
		int additionalParam = 0;
		matrix* A11 = new matrix(currSize, currSize);
		fillSubmatrix(left, A11, 0, (size / 2) - additionalParam, 0, (size / 2) - additionalParam);
		//bude obsahovat rows 1 az polovina, columns polovina az konec
		matrix* A12 = new matrix(currSize, currSize);
		fillSubmatrix(left, A12, 0, (size / 2) - additionalParam, (size / 2), size);

		//bude obsahovat rows polovina az konec, columns 1 az polovina
		matrix* A21 = new matrix(currSize, currSize);
		fillSubmatrix(left, A21, size / 2, size, 0, (size / 2) -additionalParam);

		//bude obsahovat rows polovina az konec, columns polovina az konec
		matrix* A22 = new matrix(currSize, currSize);
		fillSubmatrix(left, A22, size / 2, size, size / 2, size);

		//bude obsahovat rows 1 az polovina, columns 1 az polovina
		matrix* B11 = new matrix(currSize, currSize);
		fillSubmatrix(right, B11, 0, (size / 2) - additionalParam, 0, (size / 2) - additionalParam);

		//bude obsahovat rows 1 az polovina, columns polovina az konec
		matrix* B12 = new matrix(currSize, currSize);
		fillSubmatrix(right, B12, 0, (size / 2) - additionalParam, (size / 2), size);

		//bude obsahovat rows polovina az konec, columns 1 az polovina
		matrix* B21 = new matrix(currSize, currSize);
		fillSubmatrix(right, B21, size / 2, size, 0, (size / 2) - additionalParam);

		//bude obsahovat rows polovina az konec, columns polovina az konec
		matrix* B22 = new matrix(currSize, currSize);
		fillSubmatrix(right, B22, size / 2, size, size / 2, size);
		

		//(A11+A22)*(B11+B22)
		matrix* P = doStrassen(addMatrix(A11, A22, currSize, currSize), addMatrix(B11, B22, currSize, currSize), currSize);
		//(A21+A22)*B11
		matrix* Q = doStrassen(addMatrix(A21, A22, currSize, currSize), B11, currSize);
		//A11*(B12-B22)
		matrix* R = doStrassen(A11, substractMatrix(B12, B22, currSize, currSize), currSize);
		//A22*(B21-B11)
		matrix* S = doStrassen(A22, substractMatrix(B21, B11, currSize, currSize), currSize);
		//(A11+A12)*B22
		matrix* T = doStrassen(addMatrix(A11, A12, currSize, currSize), B22, currSize);
		//(A21-A11)*(B11+B12)
		matrix* U = doStrassen(substractMatrix(A21, A11, currSize, currSize), addMatrix(B11, B12, currSize, currSize), currSize);
		//(A12-A22)*(B21+B22)
		matrix* V = doStrassen(substractMatrix(A12, A22, currSize, currSize), addMatrix(B21, B22, currSize, currSize), currSize);

		//P+S-T+V
		matrix* C11 = addMatrix(substractMatrix(addMatrix(P, S, currSize, currSize), T, currSize, currSize), V, currSize, currSize);
		//R+T
		matrix* C12 = addMatrix(R, T, currSize, currSize);
		//Q+S
		matrix* C21 = addMatrix(Q, S, currSize, currSize);
		//P+R-Q+U
		matrix* C22 = addMatrix(substractMatrix(addMatrix(P, R, currSize, currSize), Q, currSize, currSize), U, currSize, currSize);

		matrix* C = new matrix(size, size);
		fillOriginFromSubmatrixes(C, C11, 0, (size / 2) - additionalParam, 0, (size / 2) - additionalParam);
		fillOriginFromSubmatrixes(C, C12, 0, (size / 2) - additionalParam, (size / 2), size);
		fillOriginFromSubmatrixes(C, C21, size / 2, size, 0, (size / 2) - additionalParam);
		fillOriginFromSubmatrixes(C, C22, size / 2, size, size / 2, size);
		

		//delete all matrixes
		delete A11;
		delete A12;
		delete A21;
		delete A22;
		delete B11;
		delete B12;
		delete B21;
		delete B22;
		delete P;
		delete Q;
		delete R;
		delete S;
		delete T;
		delete U;
		delete V;
		delete C11;
		delete C12;
		delete C21;
		delete C22;

		//return result
		return C;
	}
}
