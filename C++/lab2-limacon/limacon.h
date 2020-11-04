#pragma once
#ifndef _LIMACON_H_
#define _LIMACON_H_
//#include "gtest\gtest_prod.h"
#include <math.h>
namespace Prog2 {

	struct Point {
		double a, R;
		Point(double a0 = 1, double R0 = 1) :a(a0), R(R0) {}
	};
	class Limacon {
	private:
		Point p;
	public:
		Limacon(double a0 = 1, double R0 = 1);
		Limacon(const Point &p0) :p(p0) {};
		Limacon& setP(const Point &p0) { p = p0; return *this; }
		Limacon& setR(double R0) { p.R = R0;  return *this; }
		Limacon& seta(double a0) { p.a = a0; return *this; }
		Point getP() const { return p; }
		double getR() const { return p.R; }
		double geta() const { return p.a; }
		char *form() const;
		double area() const {
			if (p.a >= (2 * p.R)) return (3.14159*( (p.R) * (p.R) * 2 + (p.a) * (p.a))); else return ((3.14159*((p.R) * (p.R) * 2 + (p.a) * (p.a))) / 2);
		}
		double distance(double pi1) const { return p.a + 2*(p.R)*cos(pi1); }
		double radius() const { return p.R; }
		char *frm() const;
	};
}
#endif
