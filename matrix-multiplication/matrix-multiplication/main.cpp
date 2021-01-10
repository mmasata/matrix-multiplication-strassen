#include "strassen.hpp"
#include <iostream>
#include <exception>
#include <string>
#include <math.h>
#include <fstream>
#include <chrono>



template <typename TimePoint>
std::chrono::milliseconds to_ms(TimePoint tp) {
	return std::chrono::duration_cast<std::chrono::milliseconds>(tp);
}

/*
	Enum trida dostupnych prikazu.
*/
enum allowed_commands {
	files,
	direct,
	version,
	author,
	help,
	unknown
};

/*
	Misto stringu se nam vrati enum type, abychom mohli pracovat nasledne se switchem.
*/
allowed_commands commandToEnum(std::string const& stringValue) {
	if (stringValue == "--files") return allowed_commands::files;
	if (stringValue == "--direct") return allowed_commands::direct;
	if (stringValue == "--version") return allowed_commands::version;
	if (stringValue == "--author") return allowed_commands::author;
	if (stringValue == "--help") return allowed_commands::help;
	return allowed_commands::unknown;
}

/*
	Vrati napovedu k programu do output streamu.
*/
void printHelp(std::ostream& os) {
	/*
		Budou parametry
		--files [file1] [file2] - pokud budeme chtit nasobit matice z souboru (txt)
		--direct [matrix1_xy] [matrix2_xy] - pokud primo, nadefinuje se delka a sirka prvni a druhe matice ve tvaru NUMBERxNUMBER
		--version - vraci verzi moji aplikace
		--author - autora aplikace
	*/
	os << "Matrix multiplication command line application" << std::endl;
	os << "\n It accepts text files with matrix or directly from commandline" << std::endl;
	os << "Commands:" << std::endl;
	os << "--author: return author of this tool" << std::endl;
	os << "--version: return version of this tool" << std::endl;
	os << "--files [path1] [path2]: Use matrix from files and multiply them. Accept only text files with correct format" << std::endl;
	os << "--direct [matrix_X_Y] [matrix_X_Y]: define matrixes X and Y size in format of NUMBERxNUMBER" << std::endl;
}

/*
	Vrati autora tohoto semestralniho projektu.
*/
void printAuthor(std::ostream& os) {
	os << "Author: Martin Masata" << std::endl;
	os << "Email: masatma1@fel.cvut.cz" << std::endl;
}

/*
	Vrati verzi programu.
*/
void printVersion(std::ostream& os) {
	os << "Current version is " << "1.0.0" << std::endl;
}

/*
	V pripade pocitani matice vyhodi chybu, protoze chybi argumenty.
*/
void printMatrixParametersMissing(std::ostream& os, allowed_commands command) {
	os << "Matrix multiplication type: " << ((command == 0) ? "--files" : "--direct") << " have not enough additional arguments." << std::endl;
}

/*
	Metoda, ktera ulozi vyslednou matici do ciloveho souboru
*/
void saveMatrixToFile(std::string filePath, matrix* matrix) {
	std::ofstream resultFile(filePath);
	int** data = matrix->data;
	for (int i = 0; i < matrix->rows; i++) {
		for (int y = 0; y < matrix->columns; y++) {
			if (y != matrix->columns - 1) {
				resultFile << data[i][y] << " ";
			}
			else {
				resultFile << data[i][y];
			}
		}
		resultFile << "\n";
	}
	resultFile.close();
	std::cout << "\nMatice byla ulozena do souboru." << std::endl;
}


/*
	Bude cekat na vystupni data, dokud nebude matice naplnena.
*/
matrix* parseDirectData(std::string arg, std::ostream& os) {
	try {
		int rows = 0;
		int columns = 0;
		for (int y = 0; y < arg.length(); y++) {
			if (arg[y] == 'x' && y != arg.length()-1) {
				rows = std::stoi(arg.substr(0, y));
				columns = std::stoi(arg.substr(y+1, arg.length()-y));
				break;
			}
			if (y == (arg.length() - 1)) {
				throw std::exception("Matrix cannot be created. Parse error of ROWSxCOLUMNS format. 1");
			}
		}


		if (rows != columns || !((rows != 0) && ((rows & (rows - 1)) == 0))) {
			//neresime tyto matice, budto neni ctvercova, nebo to neni mocnina 2
			throw std::exception("Program solve only matrix with same size rows and columns and row/column number is powe of 2.");
		}

		//zinicializujeme dvoudimenzionalni pole
		int** data = new int* [rows];
		for (int i = 0; i < rows; ++i) {
			data[i] = new int[columns];
		}

		//procteme data
		os << "Enter matrix of format: " << rows << "x" << columns << std::endl;
		std::string oneLine;
		int rowsCnt = 0;
		while (std::getline(std::cin, oneLine)) {
			int columnsCnt = 0;

			int lastDelimiter = 0;
			for (int z = 0; z < oneLine.length(); z++) {
				if (oneLine[z] == ' ') {
					int currentValue = std::stoi(oneLine.substr(lastDelimiter, z-lastDelimiter));
					data[rowsCnt][columnsCnt] = currentValue;
					lastDelimiter = z + 1;
					if (columnsCnt == (columns - 1)) {
						break;
					}
					columnsCnt++;
				}
				else if (oneLine.length() - 1 == z) {
					int currentValue = std::stoi(oneLine.substr(lastDelimiter, oneLine.length() - lastDelimiter));
					data[rowsCnt][columnsCnt] = currentValue;
				}
			}

			if (rowsCnt == (rows - 1)) {
				break;
			}
			rowsCnt++;
		}
		os << "Matrix completed.\n" << std::endl;
		return new matrix(rows, columns, data);
	}
	catch (std::exception ex) {
		throw std::exception("Matrix cannot be created. Parse error of ROWSxCOLUMNS format. 2");
	}
}

/*
	Hlavni funkce nasobice matic.
*/
int main(int argc, char* argcv[]) {
	try {
		//musi obsahovat vice jak jeden argument, jinak ukoncujeme
		if (argc > 1) {
			//vratime help informace a ukoncime
			std::string argValue = argcv[1];
			allowed_commands command = commandToEnum(argValue);
			switch (command) {
			case help:
				printHelp(std::cout);
				break;
			case files:
				//v tomto pripade musi byt delka argc=4
				if (argc < 4) {
					printMatrixParametersMissing(std::cout, files);
					return 1;
				}
				else {
					//zalozime left a right matici a predame strassenovi
					matrix* left = new  matrix(argcv[2]);
					matrix* right = new  matrix(argcv[3]);
					auto start = std::chrono::high_resolution_clock::now();
					matrix* result = multiplyMatrix(left, right);
					auto end = std::chrono::high_resolution_clock::now();
					if (argc > 4) {
						//je tu posledni, optional parameter, a to cilovy soubor, kam vyslednou matici ulozime
						saveMatrixToFile(argcv[4], result);
					}
					std::cout << result;
					std::cout << "Needed " << to_ms(end - start).count() << " ms to finish.\n";
					//uvolnime z pameti
					delete left;
					delete right;
					delete result;
				}
				break;
			case direct:
				//v tomto pripade musi byt delka argc=4
				if (argc < 4) {
					printMatrixParametersMissing(std::cout, direct);
					return 1;
				}
				else {
					//v direct pripade, musi nyni nechat uzivatele zapsat rucne matice, dle velikosti co si zvolil
					matrix* left = parseDirectData(argcv[2], std::cout);
					matrix* right = parseDirectData(argcv[3], std::cout);
					auto start = std::chrono::high_resolution_clock::now();
					matrix* result = multiplyMatrix(left, right);
					auto end = std::chrono::high_resolution_clock::now();
					if (argc > 4) {
						//je tu posledni, optional parameter, a to cilovy soubor, kam vyslednou matici ulozime
						saveMatrixToFile(argcv[4], result);
					}
					std::cout << result;
					std::cout << "Needed " << to_ms(end - start).count() << " ms to finish.\n";
					//uvolnime z pameti
					delete left;
					delete right;
					delete result;
				}
				break;
			case version:
				printVersion(std::cout);
				break;
			case author:
				printAuthor(std::cout);
				break;
			default:
				std::cerr << "Unknown argument." << std::endl;
				return 1;
			}
			return 0;
		}
		else {
			std::cerr << "There is not argument." << std::endl;
			return 1;
		}
	}
	catch (std::exception ex) {
		std::cerr << ex.what() << std::endl;
		return 1;
	}
}
