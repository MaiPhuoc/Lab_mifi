#pragma once
#ifndef _STUDENT_H_
#define _STUDENT_H_
#include <iostream>
#include <string>
#include <exception>

namespace Phuoc {
	using namespace std;
	class Students;
	class Junior;
	class Senior;
	class Graduate;

	class Students {
	protected:
		string lastname, firstname;
		int group;
		
	public:
		virtual ostream& show(ostream&)const;
		virtual istream& get(istream&);
		Students() : lastname(), firstname(), group() {};
		Students(const string &lastname, const string &firstname, int group) : lastname(lastname), firstname(firstname), group(group) {};
		virtual ~Students() {}
		virtual Students *clone()const = 0;
		Students & setParameter(const string &last,const string &first,const int &a) { lastname = last; firstname = first; group = a; return *this; }
		virtual string get_lastname() const { return lastname; }
		virtual string get_firstname() const { return firstname; }
		virtual int get_group() const { return group; }
		virtual int iAm()const = 0;	 // kind of student
		Students & changeGroupStudent(int a) { group = a; return *this; }
		friend ostream& operator <<(ostream&, const Students &);
		friend istream& operator >>(istream&, Students &);
	};

	class Junior : public Students
	{	
	private:
		int scores[5];
	protected:
		virtual ostream& show(ostream&)const;
		virtual istream& get(istream&is);
	public:
		Junior(){}
		Junior(string lastname, string firstname, int group) : Students(lastname, firstname, group) { for (int i = 0; i < 5; i++) scores[i] = 0; }
		Junior(string lastname, string firstname, int group, int a[5]) :Students(lastname, firstname, group) { for (int i = 0; i < 5; i++) scores[i] = a[i]; }
		virtual ~Junior() {}
		virtual Junior & setscore(int sco[5]) { for (int i = 0; i < 5; i++) { scores[i] = sco[i]; }; return *this; };
		virtual string get_lastname() const { return lastname; }
		virtual string get_firstname() const { return firstname; }
		virtual int get_group() const { return group; }
		virtual int get_scores(int i) const { if (i >= 0 && i < 5) return scores[i]; else throw exception("Invalid i"); }
		virtual int iAm()const { return 1; } 
		virtual Students *clone()const {
			return new Junior(*this);
		}
	};

	class Senior : public Junior {
	private:
		int scores[4];
		string research, adress;
		int result;
	protected:
		virtual ostream& show(ostream&)const;
		virtual istream& get(istream&);
	public:
		Senior() {}
		Senior(string lastname, string firstname, int group) : Junior(lastname, firstname, group) { for (int i = 0; i < 4; i++) scores[i] = 0; }
		Senior(string lastname, string firstname, int group, int a[4]) :Junior(lastname, firstname, group) { for (int i = 0; i < 4; i++) scores[i] = a[i]; }
		virtual ~Senior() {}
		virtual Senior & setParameter(const int sco[4],const string &rese, const string &adre,const int &res) { for (int i = 0; i < 4; i++) scores[i] = sco[i]; research = rese; adress = adre; result = res; return *this; };
		int get_scores(int i) const { if (i >= 0 && i < 4) return scores[i]; else throw exception("Invalid i"); }
		string get_research() const { return research; }
		string get_adress() const { return adress; }
		int get_result() const { return result; }
		virtual int iAm()const { return 2; }
		virtual Students *clone()const {
			return new Senior(*this);
		}

	};
	
	class Graduate : public Students {
	private: 
		string project, adress;
		int result;
		bool exam;
	protected:
		virtual ostream& show(ostream&)const;
		virtual istream& get(istream&);
	public:
		Graduate() {}
		Graduate(string lastname, string firstname, int group) : Students(lastname, firstname, group), project(""), adress(""), result(0), exam(0) {}
		Graduate(string lastname, string firstname, int group, string proj, string adre, int re, bool ex) :Students(lastname, firstname, group), project(proj), adress(adre), result(re), exam(ex) { }
		virtual ~Graduate() {}
		virtual Graduate & setParameter(const string &proj, const string &adre, const int &re, const bool &ex) { project = proj; adress = adre; result = re; exam = ex; return *this; };
		string get_project() const { return project; }
		string get_adress() const { return adress; }
		int get_result() const { return result; }
		bool get_exam() const { return exam; }
		virtual int iAm()const { return 3; }
		virtual Students *clone()const {
			return new Graduate(*this);
		}
	};
}
#endif _STUDENT_H_