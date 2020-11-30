#include "strassen.hpp"
#include <iostream>




enum allowed_commands {
	files,
	direct,
	version,
	author,
	help,
	unknown
};

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
	Vrati autora tohoto semestralniho projektu
*/
void printAuthor(std::ostream& os) {
	os << "Author: Martin Masata" << std::endl;
	os << "Email: masatma1@fel.cvut.cz" << std::endl;
}

/*
	Vrati verzi programu
*/
void printVersion(std::ostream& os) {
	os << "Current version is " << "1.0.0" << std::endl;
}

void printMatrixParametersMissing(std::ostream& os, allowed_commands command) {

}


int main(int argc, char* argcv[]) {

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
			if (argc != 4) {
				printMatrixParametersMissing(std::cout, files);
			}
			else {

			}
			break;
		case direct:
			//v tomto pripade musi byt delka argc=4
			if (argc != 4) {
				printMatrixParametersMissing(std::cout, direct);
			}
			else {

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
