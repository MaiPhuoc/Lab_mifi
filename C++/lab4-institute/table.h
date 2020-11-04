#pragma once
#ifndef TABLE_H
#define TABLE_H
#include <string>
#include <iostream>
#include "student.h"
#include "algorithm"
#include <vector>
#include <algorithm>
#include "myvector.h"

using namespace std;

namespace Phuoc {

	struct Row {
		Students * student;
		int index;
		Row() : student(nullptr), index(0) {}
		Row(Students* stu, int i) : student(stu), index(i) {}
	};

	class Table//контейнерный класс
	{
	private:
		std::vector<Row> students;
	public:
		Table() {}
		void addStudents(const Row &r)
		{

			if (!checkIndexIn(r.index))
			{
				students.push_back(Row(r.student->clone(), r.index));
				std::sort(students.begin(), students.end(), [](const Row& a, const Row& b) -> bool {return a.index < b.index; });
			}
		}

		void showStudents(std::ostream& os) {
			for (const Row& r : students) {
				cout << r.index << endl;
				r.student->show(os);
			}
		}

		bool checkIndexIn(int index)
		{
			for (const Row& row : students)
				if (row.index == index)
					return true;
			return false;
		}

		 Students* find_student(int index)
		{
			for (Row& g : students)
				if (g.index == index)
					return g.student;
				else
					return nullptr;

		}
		 Row* find_row(int index)
		 {
			 for (Row& g : students)
				 if (g.index == index)
					 return &g;
				 else
					 return nullptr;
		 }

		void deleteStudents(int index)
		{
			for (auto i = students.begin(); i != students.end(); ++i)
				if (i->index == index) {
					students.erase(i);
					return;
				}
		}

		void changeGroupStudent(Row r, int group)
		{

			if (checkIndexIn(r.index))
			{
				r.student->changeGroupStudent(group);
			}
		}

		int changeKindStudent(Row r, int kind)
		{

			if (checkIndexIn(r.index))
			{
				if (r.student->iAm() == kind)
				{
					return 1; // the same kind
				}
				else if (r.student->iAm() < kind)
					return 2; // can't change


			}
		}

		/*friend std::ostream& operator << (std::ostream& os, const Table& t)
		{
			for (const Row& r : t.students) {
				os << "Index: " << r.index << std::endl;
				r.student->show(os);
			}
		}*/
	};
	
}

#endif // TABLE_H


//#ifndef _TABLE_H_
//#define _TABLE_H_
//
//#include <iostream>
//#include <string>
//#include <map>
//#include <exception>
//#include "student.h"
//#include <algorithm>
//
//namespace Phuoc {
//	using namespace std;
//	ostream & operator << (ostream &, const  pair<int, Students>&);
//	class Table {
//	private:
//		map<int, const Students> arr;
//	public:
//		Table() {}
//		Table(const Table &);
//		~Table() {};
//		Table & operator =(const Table &);
//		/*int & operator [](const std::string &);
//		int operator [](const std::string &) const;*/
//		friend std::ostream & operator <<(std::ostream &, const Table &);
//		friend class ConstTableIt;
//		typedef ConstTableIt ConstIterator;
//		ConstIterator begin();
//		ConstIterator end();
//	private:
//		ConstIterator find(const int) const;
//		bool insert(int, const Students *);
//		bool replace(int, Students *);
//		bool remove(const Students &);
//	};
//	class ConstTableIt {
//	private:
//		std::map<int, const Students>::iterator cur;
//	public:
//		ConstTableIt() {}
//		ConstTableIt(std::map<int, const Students>::iterator it) :cur(it) {}
//		int operator !=(const ConstTableIt &) const;
//		int operator ==(const ConstTableIt &) const;
//		std::pair<int, const Students> & operator *();
//		std::pair<int, const Students> * operator ->();
//		ConstTableIt & operator ++();
//		ConstTableIt operator ++(int);
//	};
//}
//#endif _TABLE_H_