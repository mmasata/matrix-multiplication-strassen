#pragma once
#include <string>
#include <iostream>

class matrix {
	public:
		int** data = nullptr;
		int rows;
		int columns;

		matrix() = default;
		matrix(std::string filePath);
		matrix(int rows, int columns, int** data);
		matrix(int rows, int columns);
		~matrix();
	private:
		void initDataFromFile();
};
std::ostream& operator<<(std::ostream& os, matrix* mat);