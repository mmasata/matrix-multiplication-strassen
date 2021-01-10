#pragma once
#include <string>
#include <iostream>
#include <exception>

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
		void initDataFromFile(std::fstream& file);
};
std::ostream& operator<<(std::ostream& os, matrix* mat);

class matrix_exception : public std::exception {
public:
	matrix_exception(std::string s) : text(std::move(s)) {}
	virtual const char* what() const noexcept override {
		return text.c_str();
	}
protected:
	std::string text;
};

class matrix_parse_exception : public matrix_exception {
public:
	using matrix_exception::matrix_exception;
};

class matrix_invalid_size_exception : public matrix_exception {
public:
	using matrix_exception::matrix_exception;
};

class missing_argument_exception : public matrix_exception {
public:
	using matrix_exception::matrix_exception;
};

class unknown_argument_exception : public matrix_exception {
public:
	using matrix_exception::matrix_exception;
};