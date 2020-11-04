#pragma once
#ifndef APP_H
#define APP_H

#include <iostream>
#include <vector>
#include "student.h"
#include "table.h"
using namespace Phuoc;
using namespace std;

class App
{
public:
	App();
	void run() {
		while (1) {
			std::cout << "1.Create new student\n2.Find student\n3.Delete student\n4.Show information\n5.Change group of student.\n6.Change kind of student.\n0.Quit\n\nMake your choice --> ";
			int chiso;
			getNum(chiso);
			if (chiso <= 0 || chiso > 5)
			{
				std::cout << "That's all!\n";
				break;
			}
			(this->*funcs[chiso - 1])();
		}
		system("Pause");
	}
private:
	typedef void(App::*fptr)();
	std::vector<fptr> funcs;
	Phuoc::Table table;
	int getNum(int &r)
	{
		const char* err = "";
		bool fl = 0;
		do {
			std::cout << err;
			std::cin >> r;
			if (std::cin.eof()) {
				std::cin.clear();
				return 0;
			}
			err = "You entered wrong symbol or negative number. Please, repeat:\n";
			fl = std::cin.good();
			if (r<0)
				fl = 0;
			std::cin.clear();
			if (!fl)
				std::cin.sync();
		} while (!fl);
		return 1;
	}
	
	Students *getStudents(int index){
		Students *stu = nullptr;
		int ans;
		std::cout << "Enter kind of new student -->\n1.Junior\n2.Senior\n3.Graduate\n ---> Your choice: ";
		getNum(ans);
		if (ans == 0 || ans > 3)
			return stu;
		switch (ans) {
		case 1:
			stu = new Junior;
			break;
		case 2:
			stu = new Senior;
			break;
		case 3:
			stu = new Graduate;
			break;
		}
		std::cin >> (*stu);
		std::cin.ignore(80, '\n');
		table.addStudents(Row(&(*stu), index));
		return stu;
	}
	void addStudents()
	{
		int index;
		std::cout << "Enter index of new student --> ";
		getNum(index);
		if (table.checkIndexIn(index))
		{
			std::cout << "This index exists already" << std::endl;
			return;
		}
		Students *ptr = nullptr;
		if(ptr = getStudents(index))
		{
			std::cout << "Add successed!" << std::endl;
		}
	}

	void findStudents()
	{
		Students *res;
		int index;
		std::cout << "Input index student you want to find" << endl;
		getNum(index);
		if (res = table.find_student(index)) {
			cout << "Found!" << endl;
			cout << (*res);
		}
		else {
			std::cout << "Not found!" << endl;
		}
	}

	void showStudents()
	{
		cout << "---------------------Institus-----------------" << endl;
		table.showStudents(std::cout);
		cout << "-----------------------End--------------------" << endl;
	}

	void deleteStudents()
	{
		int index;
		std::cout << "Enter index of a student, which you want to delete: ";
		getNum(index);
		if (!table.checkIndexIn(index))
		{
			std::cout << "There is no such group.\n" << std::endl;
			return;
		}
		else {
			table.deleteStudents(index);
			std::cout << "Delete successed!" << std::endl;
		}
	}

	void changeGroup()
	{
		int index;
		std::cout << "Enter index of a student, which you want to change group: ";
		getNum(index);
		if (!table.checkIndexIn(index))
		{
			std::cout << "There is no such index.\n" << std::endl;
			return;
		}
		else {
			int group;
			std::cout << "Enter new group ";
			getNum(group);
			Row *res = table.find_row(index);
			table.changeGroupStudent(*res, group);
			std::cout << "Change group successed!" << std::endl;
		}
	}

	void changeKind() {
		int index;
		std::cout << "Enter index of a student, which you want to change kind: ";
		getNum(index);
		if (!table.checkIndexIn(index))
		{
			std::cout << "There is no such index.\n" << std::endl;
			return;
		}
		else {
			int kind;
			std::cout << "Enter new kind:\n1. Senior\n2.Graduate ";
			getNum(kind);
			Row *res = table.find_row(index);
			return;
		}
	}

};

#endif // APP_H
