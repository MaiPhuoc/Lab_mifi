#pragma once
#ifndef _STACK_S_1_H_
#define _STACK_S_1_H_
#include <iostream>
namespace Prog3_1 {
	class Sequences {
	private:
		static const int SZ = 100;
		int length;
		int ar[SZ];
	public:
		Sequences ():length(0) {}
		Sequences(int a) :length(1) { ar[0] = a; }
		Sequences(int size, int *d);
		Sequences connect(const Sequences&, const Sequences& );
		Sequences getSequenceinoder();
		Sequences add(int); //==Sequences setNumber(int);
		Sequences add(Sequences);
		void arrange();
		void NumberGroup();
		int Frequence(int);
		int getSize() const { return length; }
		int getMaxSize() const { return SZ; }
		std::ostream & print(std::ostream&) const;
	};
}
#endif