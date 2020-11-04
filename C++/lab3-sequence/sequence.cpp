#include "stdafx.h"
#include "sequence.h"
namespace Prog3_1 {

	Sequences::Sequences(int size, int *d)
	{
		length = size;
		if ((length <=SZ) )
			for (int i = 0; i < length; i++)
				ar[i] = d[i];
		else
			throw std::exception("Overflow!");
	}

	Sequences Sequences::connect(const Sequences &s1, const Sequences &s2)
	{
		Sequences res(s1);
		if (s1.getSize() + s2.getSize() <= SZ)
			for (int i = 0; i < s2.getSize(); i++)
				res.add(s2.ar[i]);
		else
			throw std::exception("Those sequences are not available to connect because of too much elements");
		*this = res;
		return *this;
	}

	Sequences Sequences::getSequenceinoder()
	{
		Sequences res;
		int head = 0, end = 1;
		for (int i = 0; i < length - 2; i++) {
			if (ar[i] <= ar[i + 1] && ar[i + 1] <= ar[i + 2])
			{
				head = i;
				do {
					i++;
				} while (ar[i] <= ar[i + 1]);
				end = i + 1;
				break;
			}
			else if (ar[i] >= ar[i + 1] && ar[i + 1] >= ar[i + 2])
			{
				head = i;
				do {
					i++;
				} while (ar[i] >= ar[i + 1]);
				end = i + 1;
				break;
			}
		}
		if (end - head >= 3)
			for (int j = head; j < end; j++) {
				res.add(ar[j]);
			}
		return res;
		
	}

	Sequences  Sequences::add(int a)
	{
		if (length <= SZ - 1) {
			ar[length] = a;
			length++;
		}
		else 
			throw std::exception("Sequences is full of elements!");
		return *this;

	}

	Sequences  Sequences::add(Sequences a)
	{
		if ((length + a.length) < SZ)
		{
			for (int i = 0; i < a.length; i++)
				(*this).add(a.ar[i]);
		}
		else 
			throw std::exception("Those sequences are not available to add because of too much elements");
		return *this;
	}

	void Sequences::arrange()
	{
		int tmp;
		for (int i = 0; i < length - 1; i++)
			for (int j = i + 1; j < length; j++)
				if (ar[i] > ar[j])
				{
					tmp = ar[i];
					ar[i] = ar[j];
					ar[j] = tmp;
				}
	}

	void Sequences::NumberGroup()
	{
		Sequences tmp(*this);
		int count = 1;
		tmp.arrange();
		std::cout << "Number\t" << "Times" << std::endl;
		for (int i = 0; i < tmp.length;) {
			for (int j = i + 1; j < tmp.length; j++) {
				if (tmp.ar[i] == tmp.ar[j])
					count++;
				else
				{
					std::cout << tmp.ar[i] << "\t" << count << std::endl;
					break;
				}
			}
			i += count;
			count = 1;
		}
	}

	int Sequences::Frequence(int a)
	{
		int count = 0;
		for (int i = 0; i < length; i++)
			if (ar[i] == a)
				count++;		
		return count;
	}

	std::ostream & Sequences::print(std::ostream &s) const
	{
		if (length == 0)
			s << "Sequences is empty";
		else
			for (int i = 0; i < length; i++)
				s << ar[i] << ' ';
		s << std::endl;
		return s;
	}

}