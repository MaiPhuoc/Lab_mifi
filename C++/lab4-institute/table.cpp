#include "stdafx.h"
//#include "table.h"
//#include <iostream>
//#include <string>
//#include <map>
//#include <exception>
//#include "student.h"
//#include <algorithm>


//namespace Phuoc {
//	ostream & operator<<(ostream &os, const pair<int, const Students> &p)
//	{
//		return os << p.first << " - " << p.second;
//	}
//
//	Table::ConstIterator Table::begin()
//	{
//		return ConstTableIt(arr.begin());
//	}
//	Table::ConstIterator Table::end()
//	{
//		return ConstTableIt(arr.end());
//	}
//
//	Table::Table(const Table &a)
//	{
//		std::map<int, const Students>::const_iterator p;
//		for (p = a.arr.begin(); p != a.arr.end(); ++p)
//			arr.insert(make_pair(p->first, p->second));
//	}
//	Table & Table::operator =(const Table &a)
//	{
//		std::map<int, const Students *>::iterator p;
//		if (this != &a) {
//			for (p = arr.begin(); p != arr.end(); ++p)
//				delete p->second;
//			arr.clear();
//			std::map<int, const Students *>
//				::const_iterator pp;
//			for (pp = a.arr.begin(); pp != a.arr.end(); ++pp)
//				arr.insert(std::make_pair(pp->first, pp->second->clone()));
//		}
//		return *this;
//	}
//	Table::ConstIterator Table::find(const int n) const
//	{
//		std::map<int, Students *>::const_iterator p = arr.find(n);
//		return ConstTableIt(p);
//	}
//
//	bool Table::insert(int n, const Students *f) {
//		bool res = false;
//		std::map<int, Students *>::iterator p = arr.find(n);
//		if (p == arr.end()) {
//			std::pair<std::map<int,Students *>::iterator, bool> pp = arr.insert(std::make_pair(n, f->clone()));
//			if (!pp.second)
//				throw std::exception(
//					"can't insert new item into map");
//			res = true;
//		}
//		return res;
//	}
//
//	bool Table::replace(int, Students *)
//	{
//		return false;
//	}
//
//	bool Table::remove(const Students &)
//	{
//		return false;
//	}
//	
//	int ConstTableIt::operator !=(const ConstTableIt &it) const
//	{
//		return cur != it.cur;
//	}
//	int ConstTableIt::operator ==(const ConstTableIt &it) const
//	{
//		return cur == it.cur;
//	}
//
//	pair<int, const Students> & ConstTableIt::operator *()
//	{
//		return *cur;
//	}
//	pair<int, const Students> * ConstTableIt::operator ->()
//	{
//		return &(*cur);
//	}
//
//	ConstTableIt & ConstTableIt::operator ++()
//	{
//		++cur;
//		return *this;
//	}
//
//	ConstTableIt ConstTableIt::operator ++(int)
//	{
//		ConstTableIt res(*this);
//		++cur;
//		return res;
//	}
//
//}