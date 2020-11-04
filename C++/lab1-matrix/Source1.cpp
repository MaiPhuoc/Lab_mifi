#include <iostream>
#include "D:\Programing\C++\lab1a\lab1a\Header.h"

namespace bapi4 {
	Node* newNode(int y, double a) {
		Node *myNode = new Node;
		myNode->y = y;
		myNode->a = a;
		myNode->next = nullptr;
		return myNode;
	}

	void listNode::add(int y, double a) {
		if (!h) {
			h = newNode(y, a);
		}
		else {
			Node *t;
			for (t = h; t; t = t->next)
				if (t->y == y) {
					t->a = a;
					return;
				}
			for (t = h; t->next; t = t->next);
			t->next = newNode(y, a);
		}
		c++;
	}

	Line* newLine(int x, int y, double a) {
		Line *myLine = new Line;
		myLine->x = x;
		myLine->a.add(y, a);
		if (a > 0) (myLine->p)++;        // danh dau so luong am duong
		else (myLine->o)++;
		myLine->next = nullptr;
		return myLine;
	}


	void listNode::sort() {
		for (Node* i = h; i->next; i = i->next)
			for (Node* j = i->next; j; j = j->next)
				if (j->y < i->y) {
					std::swap(j->y, i->y);
					std::swap(j->a, i->a);
				}
	}

	void listLine::add(int x, int y, double a) {
		if (!h) {
			h = newLine(x, y, a);
		}
		else {
			Line *t = NULL;
			for (t = h; t; t = t->next) {
				if (t->x == x) {
					(t->a).add(y, a);
					if (a > 0) (t->p)++;        // danh dau so luong am duong
					else (t->o)++;
					return;
				}
			}
			for (t = h; t->next; t = t->next);
			t->next = newLine(x, y, a);
		}
		c++;
	}

	void listLine::sort() {
		for (Line* i = h; i->next; i = i->next)
			for (Line* j = i->next; j; j = j->next)
				if (j->x < i->x) {
					std::swap(j->x, i->x);
					std::swap(j->a, i->a);
					std::swap(j->p, i->p);
					std::swap(j->o, i->o);
				}
		for (Line* i = h; i; i = i->next)
			i->a.sort();
	}

	//функция ввода
	Matrix* inputMatrix()
	{
		Matrix *mat = nullptr;
		int m, n;// позиция
		double p;
		const char *pr = "";// будущее сообщение об ошибке
		bool bl = false;
		int in;
		try {
			mat = new Matrix[1];
		}
		catch (std::bad_alloc &ba)
		{
			std::cout << "Error! " << ba.what() << std::endl;
			delete mat;
			return nullptr;
		}
		//сначала вводим количество строк и столбец
		do {
			std::cout << pr << std::endl;
			std::cout << "Вводите размер прямоугольной матрицы: --> (m x n)";
			pr = "Не правильно, повторите!";
			if (getNum(mat->m) < 0)
				return nullptr;
			if (getNum(mat->n) < 0)
				return nullptr;
		} while (mat->m < 1 || mat->n < 1);
		// дальше вводим строк и сталбец и значение, вместе сотировать
		do {
			std::cout << "\n1 -Вводим.\n0 - Выход!\n";
			if (!getNum(in))
				return nullptr;
			if (in) {
				const char *pr = "";
				do {
					std::cout << pr << std::endl;
					std::cout << "Вводите {x,y,a}, где x,y - координат элементы, a - значение --> " << std::endl;
					if (getNum(m) < 0)
						return nullptr;
					if (getNum(n) < 0)
						return nullptr;
					if (getNum(p) < 0)
						return nullptr;
					pr = "Строк и стольбец надо меньше чем размера матрицы!\n";
					if (p)
						bl = true;
				} while (m < 1 || m > mat->m || n < 1 || n > mat->n || !p);
				mat->lines.add(m, n, p);
			}
			if (!bl)
				std::cout << "Значение равно 0\n";
		} while (in || !bl);
		mat->lines.sort();
		return mat;
	}

	void delMatrix(Matrix *mat) {
		Line *p = mat->lines.h, *t = nullptr;
		while (p) {
			t = p;
			p = p->next;
			delLine(t);
		}
		delete mat;
	}

	void delLine(Line *myLine) {
		Node *p = myLine->a.h, *t = nullptr;
		while (p) {
			t = p;
			p = p->next;
			delNode(t);
		}
		delete myLine;
	}

	void delNode(Node *myNode) {
		delete myNode;
	}

	void output(const char *msg, Matrix &rm) {
		std::cout << msg << std::endl;
		std::cout << "Size of matrix: " << rm.m << " " << rm.n << std::endl;
		for (Line* i = rm.lines.h; i; i = i->next) {
			std::cout << "Row #" << i->x << " <+: " << i->p << "> <-: " << i->o << "> : ";
			for (Node* j = i->a.h; j; j = j->next)
				std::cout << "{" << i->x << ", " << j->y << ", " << j->a << "} ";
			std::cout << std::endl;
		}
	}

	int isgreater(int a, int b)
	{
		if (a >= b)
			return a;
		else
			return b;
	}

	Matrix* changedMatrix(Matrix &mat) {
		Matrix *res = new Matrix;
		res->m = mat.m;
		res->n = mat.n;
		Line* i = mat.lines.h;
		int maxp = i->p, maxo = i->o;
		int posip = i->x, posio = i->x;
		for (i = mat.lines.h; i->next;)
		{
			maxp = isgreater(maxp, i->next->p);
			i = i->next;
			if (i->p == maxp)
				posip = i->x;
		}
		for (i = mat.lines.h; i->next;)
		{
			maxo = isgreater(maxo, i->next->o);
			i = i->next;
			if (i->o == maxo)
				posio = i->x;
		}
		int a = maxp, b = maxo;
		for (Line* i = mat.lines.h; i; i = i->next) {
			for (Node* j = i->a.h; j; j = j->next)
			{
				if (i->x == 1 && i->p != a) {
					res->lines.add(posip, j->y, j->a);
					continue;
				}
				else if (i->p == a) {
					res->lines.add(1, j->y, j->a);
					continue;
				}
				else if (i->o == b && posio != mat.m) {
					res->lines.add(mat.m, j->y, j->a);
					continue;
				}
				else if (i->x == mat.m) {
					res->lines.add(posio, j->y, j->a);
					continue;
				}
				else
					res->lines.add(i->x, j->y, j->a);
			}
			if (i->p == a)
			{
				a = mat.n + 2;
			}
			if (i->o == b)
			{
				b = mat.n + 2;
			}
		}
		res->lines.sort();
		std::cout << "\nМаксимальное количество строго положительных значений: " << maxp << "\nМаксимальное количество отрицательных значений: " << maxo << std::endl;
		return res;
	}
}
