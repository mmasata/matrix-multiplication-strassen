#include "matrix.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/*
	Vytvori matici, dle textoveho souboru.
	Konstruktor prijima cestu k souboru ve stringu.
*/
matrix::matrix(std::string filePath)
{
	std::fstream file(filePath);
	this->initDataFromFile(file);
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
void matrix::initDataFromFile(std::fstream& file)
{
	std::vector<std::vector<int>> vectorData;
	std::string oneLine;
	int rowNum = 0;
	int colNum = -1;
	if (file.is_open())
	{
		while (getline(file, oneLine))
		{	
			std::vector<int> col;
			int currentCols = 0;
			int lastDelimiter = 0;
			for (int z = 0; z < oneLine.length(); z++) {
				if (oneLine[z] == ' ') {
					int currentValue = std::stoi(oneLine.substr(lastDelimiter, z - lastDelimiter));
					col.push_back(currentValue);
					lastDelimiter = z + 1;
					currentCols++;
				}
				else if (oneLine.length() - 1 == z) {
					int currentValue = std::stoi(oneLine.substr(lastDelimiter, oneLine.length() - lastDelimiter));
					col.push_back(currentValue);
					currentCols++;
				}
			}
			if (colNum == -1) {
				colNum = currentCols;
			}
			else {
				if (colNum != currentCols) {
					//error nesouhlasi pocet sloupcu
					throw std::exception("Number of columns in this row is not same as in the previous one.");
				}
			}
			vectorData.push_back(col);
			rowNum++;

		}
		if (rowNum != colNum || !((rowNum != 0) && ((rowNum & (rowNum - 1)) == 0))) {
			//neresime tyto matice, budto neni ctvercova, nebo to neni mocnina 2
			throw std::exception("Program solve only matrix with same size rows and columns and row/column number is power of 2.");
		}
		file.close();
	}
	std::cout << rowNum << " " << colNum << std::endl;
	int** arrData = new int* [rowNum];
	for (int i = 0; i < rowNum; ++i) {
		arrData[i] = new int[colNum];
		for (int y = 0; y < colNum; y++) {
			arrData[i][y] = vectorData[i][y];
		}
	}

	this->data = arrData;
	this->rows = rowNum;
	this->columns = colNum;
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
