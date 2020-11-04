
namespace bapi4 {
	// ��������� ��� ������� ������ �������
	typedef struct Node {
		int y; //����� �������
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
		int x; // ����� �����
		listNode a;// ������ ��������
		struct Line *next; // ����. �����
		int p = 0; // ���������� ��������� ������ �������������
		int o = 0; // ���������� ��������� �������������
	}Line;

	struct listLine {
		Line *h = nullptr;
		int c = 0;
		void add(int, int, double);
		void sort();
	};

	typedef struct Matrix {
		int m, n; // ������ �������
		listLine lines;
	}Matrix;


	// ������ ������ ����� ������ ��������
	template <class T>
	int getNum(T &a)
	{
		std::cin >> a;
		if (!std::cin.good())
			return 0;
		return 1;
	}
	// ��������� ������
	int isgreater(int, int);
	Node* newNode(int, double);
	void delNode(Node *);
	Line* newLine(int, int, int);
	void delLine(Line *);
	Matrix* newMatrix(int, int);
	void delMatrix(Matrix *); // ������������ ������� ������
	Matrix* inputMatrix(); // ���� �������
	Matrix* changedMatrix(Matrix &);
	void output(const char *msg, Matrix &);//����� �������
}
