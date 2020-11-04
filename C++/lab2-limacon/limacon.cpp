#include "stdafx.h"
#include <strstream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "D:\Programing\Cplusplus\lab2-limacon\lab2-limacon\limacon.h"
namespace Prog2 {

	Limacon::Limacon(double a0, double R0 ) {
		p.a = a0;
		p.R = R0;
	}

	char *Limacon::form() const
	{
		char *f0 = "Your limacon's dot\n";
		char *f1 = "Your limacon's circle\n";
		char *f2 = "Your limacon's closed curve\n";
		char *f3 = "Your limacon's cardioid\n";
		char *f4 = "Your limacon have loop\n";
		if (p.a == 0 && p.R == 0) {
			return f0;
		}
		else if (p.a == 0 || p.R == 0)
		{
			return f1;
		}
		else if (p.a == abs(2 * p.R))
		{
			return f3;
		}
		else if (p.a > abs(2 * p.R))
		{
			return f2;
		}
		else  return f4;
	}

	char *Limacon::frm() const
	{
		char *s1 = "(x ^ 2 + y ^ 2 - 2 *  * x) ^ 2 -  ^ 2 * (x ^ 2 + y ^ 2) = 0\n";
		int l = strlen(s1) + 1;
		size_t Size = 20;
		char num[20];
		sprintf_s(num, 20, "%.2f", p.a);
		l += strlen(num);
		sprintf_s(num, 20, "%.2f", p.R);
		l += strlen(num);

		char *s = new char[l];

		if (p.R == 0)
			sprintf_s(s, l, "(x ^ 2 + y ^ 2) ^ 2 ");
		else
			sprintf_s(s, l, "(x ^ 2 + y ^ 2 - 2 * %.2f * x) ^ 2", p.R);
		int k = strlen(s);
		if (p.a == 0)
			sprintf_s(s + k, l - k, " = 0");
		else
			sprintf_s(s + k, l - k, " - %.2f ^ 2 * (x ^ 2 + y ^ 2) = 0\n", p.a);
		return s;
	}
}