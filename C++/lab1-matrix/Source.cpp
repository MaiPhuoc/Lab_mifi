#include <iostream>
#include "D:\Programing\C++\lab1a\lab1a\Header.h"
#include <clocale>
#include <cstdlib>

using namespace bapi4;

int main() {
	setlocale(LC_ALL, "Russian");
	Matrix *rm = NULL, *rmres = NULL;
	rm = inputMatrix();
	if (!rm) {
		std::cout << "incorrect data" << std::endl;
		return 1;
	}
	output("Sourced matrix", *rm);
	rmres = changedMatrix(*rm);
	output("\nMatrix after change positions:", *rmres);
	delMatrix(rm);
	delMatrix(rmres);
	system("PAUSE");
	return 0;
}

