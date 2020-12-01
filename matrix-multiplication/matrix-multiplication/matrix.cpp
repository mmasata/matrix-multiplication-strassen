#include "matrix.hpp"
#include <iostream>

/*
	Vytvori matici, dle textoveho souboru.
	Konstruktor prijima cestu k souboru ve stringu.
*/
matrix::matrix(std::string filePath)
{
	//TODO
}

/*
	Vytvorci templatu dle vstupnich ciselnych parametru.
	Konstruktor prijima int radku a sloupcu.
*/
matrix::matrix(int rows, int columns, int** data)
{
	this->rows = rows;
	this->columns = columns;
	this->data = data;
}

/*
	Konstruktor pro inicializaci dvoudimenzionalniho pole
*/
matrix::matrix(int rows, int columns)
{
	int** data = new int* [rows];
	for (int i = 0; i < rows; ++i) {
		data[i] = new int[columns];
	}

	this->rows = rows;
	this->columns = columns;
	this->data = data;
}

/*
	Destruktor matice.
*/
matrix::~matrix()
{
	//musime smazat vsechny pole v dvoudimenzionalnim poli
	for (int i = 0; i < rows; i++) {
		delete[] this->data[i];
	}
	delete[] this->data;
}


/*
	Zpracuje data z textoveho souboru.
*/
void matrix::initDataFromFile()
{
	//TODO
}

std::ostream& operator<<(std::ostream& os, matrix* mat)
{
	os << "Matrix result is:" << std::endl;
	for (int i = 0; i < mat->rows; i++) {
		for (int y = 0; y < mat->columns; y++) {
			os << mat->data[i][y];
			if (mat->columns - 1 != y) {
				os << " ";
			}
		}
		os << std::endl;
	}
	return os;
}
