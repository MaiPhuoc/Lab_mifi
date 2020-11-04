#include "stdafx.h"
#include <iostream>
#include "D:\Programing\Cplusplus\lab2-limacon\lab2-limacon\limacon.h"


int _tmain(int argc, _TCHAR* argv[])
{
	Prog2::Limacon c(5);
	Prog2::Point p;
	int fl1 = 1;
	char *s = NULL, *form = NULL;
	while (fl1) {
		std::cout << "Your limacon is:" << std::endl;
		s = c.frm();
		std::cout << s << std::endl;
		delete[] s;
		form = c.form();
		std::cout << "form: " << form << std::endl;
		std::cout << "area: " << c.area() << std::endl;
		std::cout << "radius: " << c.radius() << std::endl;
		int fl2 = 1;
		while (fl2) {
			std::cout << "Enter pi for calculate value distance p(pi) or press ctrl+Z to quit:" <<
				std::endl;
			double pi1;
			std::cin >> pi1;
			fl2 = std::cin.good();
			if (!fl2)
				continue;
			try {
				std::cout << "p = " << c.distance(pi1) << std::endl;
			}
			catch (std::exception &ex)
			{
				std::cout << ex.what() << std::endl;
			}
		}
		std::cin.clear();
		std::cout << "Enter new a and R to continue or press ctrl+Z to quit:" << std::endl;
		std::cin >> p.a >> p.R ;
		if (std::cin.good()) {
			c.seta(p.a);
			try {
				c.setR(p.R);
			}
			catch (std::exception &ex)
			{
				std::cout << ex.what() << std::endl;
			}
		}
		else
			fl1 = 0;
	}
	return 0;
}