#include "stdafx.h"
#include "student.h"
#include "iostream"

namespace Phuoc {
	using namespace std;
	std::ostream & Students::show(ostream &os) const
	{
		os << "Name: " << lastname << " " << firstname << " -- Group " << group << endl;
		return os;
	}
	istream & Students::get(istream &is)
	{
		std::cout << "Input lastname, name and group of student:" << std::endl;
		is >> lastname >> firstname >> group;
		//Students(lastname, firstname, group);
		return is;
	}
	std::ostream & Phuoc::Junior::show(ostream &os) const
	{
		//os << "Junior ---> Name: " << lastname << " " << firstname << " -- Group " << group << endl;
		os << "Junior --->" << endl;
		Students::show(os);
		os << "Result exam last year: " << scores[0] << " - " << scores[1] << " - " << scores[2] << " - " << scores[3] << " - " << scores[4]<< endl;
		return os;
	}
	istream & Junior::get(istream &is)
	{
		//std::cin.clear();
		Students::get(is);
		std::cout << "Input 5 scores:" << std::endl;
		for (int i = 0; i < 5; i++)
			is >> scores[i];
		//Junior(Students::get_lastname(), Students::get_firstname(), Students::get_group(), scores[5]);
		return is;
	}
	std::ostream & Phuoc::Senior::show(ostream &os) const
	{
		//os << "Senior ---> Name: " << lastname << " " << firstname << " -- Group " << group << endl;
		os << "Senior ---> " << endl;
		Students::show(os);
		os << "Result exam last year: " << scores[0] << " - " << scores[1] << " - " << scores[2] << " - " << scores[3] << endl; 
		os << "Research: " << "\"" << research << "\"" << " -- In adress: " << "\"" << adress << "\"" << " with evaluation of the professor: " << result << "." << endl;
		return os;
	}
	istream & Senior::get(istream &is)
	{
		//std::cin.clear();
		Students::get(is);
		std::cout << "Input 4 scores:" << std::endl;
		for (int i = 0; i < 4; i++)
			is >> scores[i];
		std::cout << "Input research, adress, result:" << std::endl;
		is >> research >> adress >> result;
		//Senior(Students::get_lastname(), Students::get_firstname(), Students::get_group(), scores[4], research, adress, result);
		return is;

	}
	std::ostream & Phuoc::Graduate::show(ostream &os) const
	{
		//os << "Graduate -> Name: " << lastname << " " << firstname << " -- Group " << group << endl;
		os << "Graduate ---> " << endl;
		Students::show(os);
		os << "Project: " << "\"" << project << "\"" << " -- In adress: " << "\"" << adress << "\"" << " with evaluation of the professor: " << result << "." << endl;
		os << "State Examination Commission: " << exam << " (Note: 1--> Passed,  0 --> Not passed )" << endl;
		return os;
	}

	istream & Graduate::get(istream &is)
	{
		Students::get(is);
		std::cout << "Input project, adress, result and exam:" << std::endl;
		is >> project >> adress >> result >> exam;
		//Graduate(Students::get_lastname(), Students::get_firstname(), Students::get_group(), project, adress, result, exam);
		return is;
	}

	ostream & operator<<(ostream &os, const Students &stu)
	{
		return stu.show(os);
	}

	istream & operator>>(istream &is, Students &stu)
	{
		return stu.get(is);
	}

}


