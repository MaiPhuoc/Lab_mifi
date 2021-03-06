// Prog3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "sequence.h"
using namespace Prog3_1;
int main()
{
	int ar1[9] = { -2, -5, 3, 6, 44, 3, -5 ,23, 3 };
	Sequences sq;
	Sequences sq0(8);
	Sequences sq1(sizeof(ar1) / sizeof(int), ar1);

	std::cout << "0. Max size of sequences = " << sq.getMaxSize() << std::endl;
	std::cout << "1. Constructor in defauts: Current size = " << sq.getSize() << "; In sequences : \n";
	sq.print(std::cout);
	std::cout << std::endl;

	std::cout << "2. Constructor with one element: Current size = " << sq0.getSize() << "; In sequences : \n";
	sq0.print(std::cout);
	std::cout << std::endl;

	std::cout << "3. Constructor with size and elements: Current size = " << sq1.getSize() << "; In sequences : \n";
	sq1.print(std::cout);
	std::cout << std::endl;

	std::cin.clear();
	Sequences sq4;
	int a;
	std::cout << "3.2. Sequences with element from console: " << std::endl;
	int fl0 = 1;
	std::cout << "Enter number or Ctrl + Z to quit." << std::endl;
	while (fl0) {
		std::cin >> a;
		fl0 = std::cin.good();
		if (!fl0) 
			continue;
		try {
			sq4.add(a);
		}
		catch (std::exception &ex)
		{
			std::cout << ex.what() << std::endl;
		}		
	}
	std::cout << "Current size = " << sq4.getSize() << "; In sequences : \n";
	sq4.print(std::cout);
	std::cout << std::endl;

	std::cout << "4. Add new element to sequences with one element:" << std::endl;
	try {
		sq0.add(99);
	}
	catch (const std::exception &msg)
	{
		std::cout << msg.what() << std::endl;
	}
	sq0.print(std::cout);
	std::cout << std::endl;

	std::cout << "5. Connect two sequences to the new sequenes:" << std::endl;
	try {
		sq.connect(sq1, sq0);
	}
	catch (const std::exception &msg)
	{
		std::cout << msg.what() << std::endl;
	}
	sq.print(std::cout);
	std::cout << std::endl;
	
	std::cout << "6. Take first subsequences in oder:" << std::endl;
	Sequences sqminus = sq.getSequenceinoder();
	sqminus.print(std::cout);
	std::cout << std::endl;

	std::cout << "7. Determine number of different number in sequences" << std::endl;
	sq.NumberGroup();
	std::cout << std::endl;

	std::cout << "8. Frequence of number 3 in the sequences: " << sq.Frequence(3)  <<std::endl;
	std::cin.clear();
	int fl1 = 1;
	while (fl1) {
		std::cout << "8.1. Enter number for calculate frequence or press ctrl+Z to quit:" << std::endl;
		int t;
		std::cin >> t;
		fl1 = std::cin.good();
		if (!fl1)
			continue;
		std::cout << "Frequence = " << sq.Frequence(t) << std::endl;	
	}

	int ar3[9] = { -2, -5, 3, 6, 44, 69, 11 ,23, 10 };
	Sequences sq2(sizeof(ar3) / sizeof(int), ar3);
	std::cout << "9. Sequences add sequences " << std::endl;
	try {
		sq.add(sq2);
	}
	catch (const std::exception &msg)
	{
		std::cout << msg.what() << std::endl;
	}
	sq.print(std::cout);
	std::cout << std::endl;

	system("PAUSE");
	return 0;
}