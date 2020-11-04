
namespace bapi4 {
	// структура для задания строки матрицы
	typedef struct Node {
		int y; //Какой столбец
		double a;
		struct Node *next;
	}Node;

	struct listNode {
		Node *h = nullptr;
		int c = 0;
		void add(int, double);
		void sort();
	};

	typedef struct Line {
		int x; // какой строк
		listNode a;// массив элеметов
		struct Line *next; // след. строк
		int p = 0; // количество элементов строго положительных
		int o = 0; // количество элементов отрицательных
	}Line;

	struct listLine {
		Line *h = nullptr;
		int c = 0;
		void add(int, int, double);
		void sort();
	};

	typedef struct Matrix {
		int m, n; // размер матрицы
		listLine lines;
	}Matrix;


	// заблон фунций ввода одного значения
	template <class T>
	int getNum(T &a)
	{
		std::cin >> a;
		if (!std::cin.good())
			return 0;
		return 1;
	}
	// прототипы фунций
	int isgreater(int, int);
	Node* newNode(int, double);
	void delNode(Node *);
	Line* newLine(int, int, int);
	void delLine(Line *);
	Matrix* newMatrix(int, int);
	void delMatrix(Matrix *); // освобождение занятой памяти
	Matrix* inputMatrix(); // ввод матрицы
	Matrix* changedMatrix(Matrix &);
	void output(const char *msg, Matrix &);//вывод матрицы
}
