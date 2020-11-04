#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <locale.h>
typedef struct node{
	int key;
	struct node * left;
	struct node * right;
	struct node * parent;
	char color;
	char * info;
} node;

typedef struct cache{
	int key;
	node * elem;
} cache;

const int sizec = 5;
node * root = NULL;
struct cache table[sizec];

node * grandparent(node *); //
node * uncle(node *);//
void left_rotate(node *);
void right_rotate(node *);
void rotateright(node *);
void rotateleft(node *);
node * search(node *, int);
node * maxelem(node *);
node * insert(int, char *);
void insert_case1(node *);
void insert_case2(node *);
void insert_case3(node *);
void insert_case4(node *);
void insert_case5(node *);
node * sibling(node *);//
node * search_next(node *);//
void deletenode(node *);
void deleteFixup(node *);
char *getstr();
void printtable(node *);
void showtree(node *, int);
int hash(int);
void addtobuf(int, node *);
void delfrombuf(int);
node * searchinbuf(int);
void showbuf();


void addtobuf(int k, node * ptr)
{
	table[hash(k)].key = k;
	table[hash(k)].elem = ptr;
	return;
}

void delfrombuf(int k)
{
	node * tmp;
	int i = hash(k);
	for (int j = 0; j < sizec; j++)
	if (table[j].elem)
		table[j].elem = search(root, table[j].key);
	if (table[i].key == k){
		tmp = table[i].elem;
		table[i].elem = NULL;
		//free(tmp);
	}
}

node * searchinbuf(int k)
{
	if (table[hash(k)].elem && table[hash(k)].key == k)
		return table[hash(k)].elem;
	else
		return NULL;
}

void showbuf()
{
	int i;
	printf("Буфер:\n");
	for (i = 0; i < sizec; i++){
		if (table[i].elem)
			printf("%d       %s\n", table[i].key, table[i].elem->info);
	}
}

node * grandparent(node * n)  //ПОИСК ДЕДУШКИ
{
	if ((n != NULL) && (n->parent != NULL))
		return n->parent->parent;
	else
		return NULL;
}

node * uncle(node *n) //ПОИСК ДЯДИ
{
	node *g = grandparent(n);
	if (g == NULL)
		return NULL; // No grandparent means no uncle
	if (n->parent == g->left)
		return g->right;
	else
		return g->left;
}

void left_rotate(node *x)
{
	/*node *pivot = n->right;
	pivot->parent = n->parent; /* при этом, возможно, pivot становится корнем дерева
	if (n->parent != NULL) {
	if (n->parent->left == n)
	n->parent->left = pivot;
	else
	n->parent->right = pivot;
	}
	n->right = pivot->left;
	if (pivot->left != NULL)
	pivot->left->parent = n;
	n->parent = pivot;
	pivot->left = n;*/
	node * y = x->right;
	node * p = x->parent;
	x->right = y->left;
	if (y->left)
		y->left->parent = x;
	y->parent = p;
	if (p == NULL)
		root = y;
	else{
		if (p->left == x)
			p->left = y;
		else
			p->right = y;
	}
	y->left = x;
	x->parent = y;
}

void right_rotate(node *x)
{
	/*node *pivot = n->left;
	pivot->parent = n->parent; /* при этом, возможно, pivot становится корнем дерева
	if (n->parent != NULL) {
	if (n->parent->left == n)
	n->parent->left = pivot;
	else
	n->parent->right = pivot;
	}
	n->left = pivot->right;
	if (pivot->right != NULL)
	pivot->right->parent = n;
	n->parent = pivot;
	pivot->right = n;*/
	node * y = x->left;
	node * p = x->parent;
	x->left = y->right;
	if (y->right)
		y->right->parent = x;
	y->parent = p;
	if (p == NULL)
		root = y;
	else{
		if (p->right == x)
			p->right = y;
		else
			p->left = y;
	}
	y->right = x;
	x->parent = y;
}

node * search(node * ptr, int key)  //ПОИСК ПО КЛЮЧУ   СЛОЖНОСТЬ :  О(h) где h - высота дерева
{
	if (ptr == NULL)
		return NULL;
	if (key == ptr->key){
		addtobuf(key, ptr);
		return  ptr;
	}
	else if (key < ptr->key)
		ptr = search(ptr->left, key);
	else
		ptr = search(ptr->right, key);
	return ptr;
}

node * maxelem(node * ptr) //SEARCH FOR THE MAXIMUM KEY complexity :  О(h) where h is the height of the tree
{
	if (!ptr)
		return NULL;
	while (ptr->right != NULL)
		ptr = ptr->right;
	return ptr;
}

node * insert(int key, char * info)    //INSERT COMPLEXITY :  О(h) = O(log2(n)) where h is the height of the tree, n - number of internal tree nodes
{
	//if (search(key) != NULL)
	//return NULL;
	node * ptr = root;
	node * par;
	if (ptr == NULL){
		ptr = (node *)malloc(sizeof(node));
		ptr->key = key;
		ptr->right = NULL;
		ptr->left = NULL;
		ptr->info = info;
		ptr->parent = NULL;
		ptr->color = 'b';
		root = ptr;
	}
	else
	{
		ptr = root;
		par = NULL;
		while (ptr)
		{
			par = ptr;
			if (key < ptr->key)
				ptr = ptr->left;
			else
				ptr = ptr->right;
		}
		ptr = (node *)malloc(sizeof(node));
		if (key < par->key){
			ptr->key = key;
			ptr->left = NULL;
			ptr->right = NULL;
			ptr->parent = par;
			ptr->info = info;
			ptr->color = 'r';
			par->left = ptr;
		}
		else
		{
			ptr->key = key;
			ptr->left = NULL;
			ptr->right = NULL;
			ptr->parent = par;
			ptr->info = info;
			ptr->color = 'r';
			par->right = ptr;
		}

	}

	insert_case1(ptr);
	//insertFixup(ptr);
	return ptr;
}



void insert_case1(node *n)
{
	if (n->parent == NULL)
		n->color = 'b';
	else
		insert_case2(n);
}

void insert_case2(node *n)
{
	if (n->parent->color == 'b')
		return; /* Tree is still valid */
	else
		insert_case3(n);
}

void insert_case3(node *n)
{
	node *u = uncle(n), *g;
	if ((u != NULL) && (u->color == 'r') && (n->parent->color == 'r')) {
		n->parent->color = 'b';
		u->color = 'b';
		g = grandparent(n);
		g->color = 'r';
		insert_case1(g);
	}
	else {
		insert_case4(n);
	}
}

void insert_case4(node *n)
{
	node *g = grandparent(n);
	if ((n == n->parent->right) && (n->parent == g->left)) {
		left_rotate(n->parent);
		n = n->left;
	}
	else if ((n == n->parent->left) && (n->parent == g->right)) {
		right_rotate(n->parent);
		n = n->right;
	}
	insert_case5(n);
}

void insert_case5(node *n)
{
	node *g = grandparent(n);
	n->parent->color = 'b';
	g->color = 'r';
	if ((n == n->parent->left) && (n->parent == g->left)) {
		right_rotate(g);
	}
	else {
		left_rotate(g);
	}
}

node * sibling(node *n)  //SEARCH BROTHER
{
	if (n == n->parent->left)
		return n->parent->right;
	else
		return n->parent->left;
}

node * search_next(node * ptr)  //SEARCH NEXT KEY
{
	node * tmp;
	if (ptr->right){
		ptr = ptr->right;
		while (ptr->left)
			ptr = ptr->left;
		return ptr;
	}
	else{
		tmp = ptr->parent;
		while (tmp && ptr == tmp->right){
			ptr = tmp;
			tmp = ptr->parent;
		}
	}
	return ptr;
}

void deletenode(node * ptr)  //Delete complexity:  О(h) = O(log2(n)) where h is the height of the tree, n is the number of internal tree nodes
{
	node *y, *par, *p;
	if (ptr->left == NULL || ptr->right == NULL)
		y = ptr;
	else
		y = search_next(ptr);
	if (y->left)
		p = y->left;
	else
		p = y->right;
	par = y->parent;
	if (p)
		p->parent = par;
	if (root->left == y && y->left == NULL && y->right == NULL)
		root->right->color = 'r';
	else if (root->right == y && y->left == NULL && y->right == NULL)
		root->left->color = 'r';
	if (y->parent && y->parent->color == 'r' && (y->parent->left == NULL || y->parent->right == NULL) && y->parent->parent && y->parent->parent == root)
		y->parent->color = 'b';
	if (par == NULL)
		root = p;
	else
	if (par->left == y)
		par->left = p;
	else
		par->right = p;
	if (y != ptr){
		ptr->key = y->key;
		ptr->info = y->info;
	}
	if (!root)    //возможно нужно подправить
		return;
	if (y->color == 'b')
		deleteFixup(p);
	free(y);
	/*node *x, *y;
	if (!z || z == NULL)
	return;
	if (z->left == NULL || z->right == NULL) {
	y = z;
	}
	else {
	y = z->right;
	while (y->left != NULL) y = y->left;
	}
	if (y->left != NULL)
	x = y->left;
	else
	x = y->right;
	x->parent = y->parent;
	if (y->parent)
	if (y == y->parent->left)
	y->parent->left = x;
	else
	y->parent->right = x;
	else
	root = x;
	if (y != z) {
	z->key = y->key;
	z->info = y->info;
	}
	if (y->color == 'b')
	deleteFixup(x);
	free(y);*/
}

void deleteFixup(node *x) {
	if (!x)
		return;
	while (x != root && x->color == 'b') {
		if (x == x->parent->left) {
			node *w = x->parent->right;
			if (w->color == 'r') {
				w->color = 'b';
				x->parent->color = 'r';
				rotateleft(x->parent);
				w = x->parent->right;
			}
			if (w->left->color == 'b' && w->right->color == 'b') {
				w->color = 'r';
				x = x->parent;
			}
			else {
				if (w->right->color == 'b') {
					w->left->color = 'b';
					w->color = 'r';
					rotateright(w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = 'b';
				w->right->color = 'b';
				rotateleft(x->parent);
				x = root;
			}
		}
		else {
			node *w = x->parent->left;
			if (w->color == 'r') {
				w->color = 'b';
				x->parent->color = 'r';
				rotateright(x->parent);
				w = x->parent->left;
			}
			if (w->right->color == 'b' && w->left->color == 'b') {
				w->color = 'r';
				x = x->parent;
			}
			else {
				if (w->left->color == 'b') {
					w->right->color = 'b';
					w->color = 'r';
					rotateleft(w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = 'b';
				w->left->color = 'b';
				rotateright(x->parent);
				x = root;
			}
		}
	}
	x->color = 'b';
}


char *getstr()   //string input
{
	char *ptr = (char*)malloc(1);
	char buf[201];
	int n, len = 0;
	*ptr = '\0';
	scanf_s("%*c");
	do{
		n = scanf_s("%200[^\n]", buf, 201);
		if (n < 0){
			free(ptr);
			ptr = NULL;
			continue;
		}
		if (n == 0)
			scanf_s("%*c");
		else{
			len += strlen(buf);
			ptr = (char*)realloc(ptr, len + 1);
			strcat(ptr, buf);
		}
	} while (n > 0);
	return ptr;
}

int hash(int x)  //hash-function
{
	return x % sizec;
}

void printtable(node * ptr)    
{
	if (ptr == NULL) //CONCLUSION IN TABLE FORM
		return;
	if (ptr->left)
		printtable(ptr->left);
	printf("%d            %s\n", ptr->key, ptr->info);
	printtable(ptr->right);
}

void showtree(node * ptr, int len)  //CONCLUSION IN THE FORM OF A TREE
{
	if (ptr == NULL)
		return;
	if (ptr->right)
		showtree(ptr->right, len + 1);
	for (int i = 0; i < len; i++)
		printf("\t");
	printf("%d%c\n", ptr->key, ptr->color);
	showtree(ptr->left, ++len);
}

void rotateleft(node *x) {

	/**************************
	*  rotate node x to left *
	**************************/

	node *y = x->right;

	/* establish x->right link */
	x->right = y->left;
	if (y->left != NULL)
		y->left->parent = x;

	/* establish y->parent link */
	if (y != NULL)
		y->parent = x->parent;
	if (x->parent) {
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	else {
		root = y;
	}

	/* link x and y */
	y->left = x;
	if (x != NULL)
		x->parent = y;
}

void rotateright(node *x) {

	/****************************
	*  rotate node x to right  *
	****************************/

	node *y = x->left;

	/* establish x->left link */
	x->left = y->right;
	if (y->right != NULL)
		y->right->parent = x;

	/* establish y->parent link */
	if (y != NULL)
		y->parent = x->parent;
	if (x->parent) {
		if (x == x->parent->right)
			x->parent->right = y;
		else
			x->parent->left = y;
	}
	else {
		root = y;
	}

	/* link x and y */
	y->right = x;
	if (x != NULL)
		x->parent = y;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	srand((unsigned)time(NULL));
	int select, key;
	char * str;
	node * ptr;
	int i;
	for (i = 0; i < sizec; i++)
		table[i].elem = NULL;
	printf("МЕНЮ\n\n");
	printf("1)Добавить элемент в таблицу\n");
	printf("2)Удалить элемент из таблицы\n");
	printf("3)Поиск информации по ключу\n");
	printf("4)Вывод содержимого таблицы\n");
	printf("5)Вывод информации с максимальным ключом\n");
	printf("6)Выход\n");
	do{
		printf("Ваш выбор: ");
		scanf("%d", &select);
		scanf("%*[^\n]");
		if (select != 1 && select != 2 && select != 3 && select != 4 && select != 5 && select != 6)
		{
			printf("Некорректный номер, попробуйте снова\n");
			continue;
		}
		switch (select){
		case 1:
			printf("Введите ключ элемента\n");
			scanf("%d", &key);
			if (search(root, key)){
				printf("Ошибка: дублирование ключей\n");
				continue;
			}
			printf("Введите информацию\n");
			str = getstr();
			addtobuf(key, insert(key, str));
			printf("Успешная вставка\n");
			break;
		case 2:
			printf("Введите ключ элемента\n");
			scanf("%d", &key);
			scanf("%*[^\n]");
			if (search(root, key) == NULL){
				printf("Неверный ключ элемента\n");
				continue;
			}
			deletenode(search(root, key));
			delfrombuf(key);
			printf("Успешное удаление\n");
			break;
		case 3:
			printf("Введите ключ элемента\n");
			scanf("%d", &key);
			scanf("%*[^\n]");
			if (searchinbuf(key)){
				printf("инфо по ключу %d:      %s\n", key, searchinbuf(key)->info);
				continue;
			}
			if (search(root, key))
				printf("инфо по ключу %d:      %s\n", key, search(root, key)->info);
			else
				printf("Такого элемента не существует\n");
			break;
		case 4:
			printf("Таблица:\n");
			printf("Ключ            Инфо\n");
			printtable(root);
			printf("В виде дерева:\n");
			showtree(root, 0);
			showbuf();
			break;
		case 5:
			printf("Информация с максимальным ключом:\n");
			ptr = maxelem(root);
			if (!ptr)
				printf("Дерево пусто\n");
			else
				printf("ключ %d            инфо: %s\n", ptr->key, ptr->info);
			break;
		case 6:
			//fclose(fd);
			break;
		}
	} while (select != 6);
	printf("Завершение работы...\n");
	return 0;
}
