#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

typedef struct comp{
    float RE;
    float IM;
}comp;

typedef struct Tree {
    struct Node *root;
}Tree;

typedef struct Node {
    int key;
    char *info;
    struct Node *l, // left subtree
                *r; // right subtree
}Node;

int getInt(int *);
char *getstring();
int add_tree(struct Tree *, int, char *);
void print_tree_node_LRC(struct Node *);
void print_tree_node_RLC(struct Node *);
int del_tree(struct Tree *, int);
void free_tree(struct Tree *);
void free_tree_node(struct Node *);
char *search(struct Tree *, int);
Node *findMin(struct Tree *, int);
void padding(char, int);
void putTree(Node *, int);
Node *find(struct Tree *, int);

const char *msgsTree[] = {"0. Quit", "1. Tree", "2. Map Tree", "3. Where", "4. Merger"}; // MENU main
const int NMsgsTree = sizeof(msgsTree) / sizeof(msgsTree[0]);
int dialogTree(const char *msgsTree[], int);
int ADD(struct Tree *, int);
int MAP(struct Tree *, int);
int WHERE(struct Tree *, int);
int MERGER(struct Tree *, int);
int(*fptrTree[])(Tree *, int) = {NULL, ADD, MAP, WHERE, MERGER};

const char *msgs[] = {"0. Quit", "1. Add", "2. Find", "3. Delete", "4. Show", "5. Find min", "6. Print Tree"}; // MENU with tree
const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
int dialog(const char *msgs[], int);
int D_Add(Tree *);
int D_Find(Tree *);
int D_Delete(Tree *);
int D_Show(Tree *);
int D_Find_Min(Tree *);
int D_Print_Tree(Tree *);
int(*fptr[])(Tree *) = {NULL, D_Add, D_Find, D_Delete, D_Show, D_Find_Min, D_Print_Tree};
int main() {
    Tree *T;
    int n, i, rc;
    printf("How many tree you want to enter?\n");
    if (!getInt(&n)){
        printf("Something wrong!\n");
        return 0;
    }
        T = (Tree *)malloc(n*sizeof(Tree));
    for (i = 0; i < n; i++)
        T[i].root = NULL;
    while ((rc = dialogTree(msgsTree, NMsgsTree)))
        {system("cls");
        if (!fptrTree[rc](T, n))
            break;
        }
    printf("That's all. Bye!\n");
    for(i = 0; i < n; i++)
        free_tree(&T[i]);
    return 0;
}

int getInt(int *a) {
	int n;
	do {
		n = scanf("%d",a);
		if (n < 0) return 0;
		if (!n)
		{
			printf("Error. Repeat input\n");
			scanf("%*[^\n]");
			scanf("%*c");
		}
	} while (n == 0);
	return 1;
}

char *getstring(){
	int n, l;
	char buf[80];
	char *str = NULL, *p;
	str = (char *)malloc(1);
	if (str == NULL)
		return NULL;
        strcpy(str,"");
	do {
		n = scanf("%79[^\n]",buf);          // ^\n la khac phim enter
		if (n == -1){free(str); return NULL;}// Ctrl+Z
		if (n == 0)
            scanf("%*c");
        else{
        l = strlen(buf)+strlen(str)+1;
		p = (char *)realloc(str,l);
		if (p == NULL){
			free(str); return NULL;
		}
		str = p;
		strcat(str, buf);}
		} while (n > 0);
	return str;
}

int dialog(const char *msgs[],const int Nmsgs) {
	char *errmsg = "\n";
	int rc, i, n;
	do {
		printf("%s",errmsg);
		errmsg = "Repeat please\n";
		for (i = 0; i < Nmsgs; printf("%s\n", msgs[i]), i++);
		printf("Enter item: --> ");
		n = getInt(&rc);
		if (!n) rc = 0;

	} while (rc < 0 || rc >= Nmsgs);
	return rc;
}

int dialogTree(const char *msgsTree[],const int NmsgsTree) {
	char *errmsg = "\n";
	int rc, i, n;
	do {
		printf("%s",errmsg);
		errmsg = "Repeat please\n";
		for (i = 0; i < NmsgsTree; printf("%s\n", msgsTree[i]), i++);
		printf("Enter item: --> ");
		n = getInt(&rc);
		if (!n) rc = 0;

	} while (rc < 0 || rc >= NmsgsTree);
	return rc;
}

int ADD(struct Tree *T, int n){
    int rc, i;
    printf("Which tree you want to do with? (0, 1, 2, 3...) \n-->");
    if(!getInt(&i) || i < 0 || i > n){
        printf("Something wrong!\n");
        return 0;}
    while ((rc = dialog(msgs, NMsgs))){
        system("cls");
        if (!fptr[rc](&(T[i]))){
            break;
            system("cls");
        }
    }
    return 1;
}

int MAP(struct Tree *T, int n){
//    Tree Treemap;
    if(D_Print_Tree(T)){
    printf("Tree map with function 2x+1:\n");
//    map_tree(&Treemap, &T);
    }
    return 1;
}

//int map_tree(Tree *Tmap, *T){
//    int i;
//    char *info = NULL;
//    struct Node **pq;
//}
//
//void take_key(struct Node *q){
//    if (q == NULL) return;
//    take_key(q->l);
//    keynewq->key;
//}

int WHERE(struct Tree *T, int n){return 1;}
int MERGER(struct Tree *T, int n){return 1;}

int D_Add(struct Tree *T){
    int k;
    char *s;
    printf("Input key -->\n");
    if(!getInt(&k)){
        printf("Something wrong!\n");
        return 0;
    };
    printf("Input info:\n");
    scanf("%*c");
        if(!(s = getstring())){
        printf("Something wrong!\n");
        return 0;
    };
    if (add_tree(T,k,s)){
        printf("Added\n");}
    else printf("Error!\n");
    free(s);
    return 1;
}

int add_tree(struct Tree *T, int key, char *info){
    struct Node **pq;
    for (pq = &T->root; *pq; pq = key <= (*pq)->key ? &(*pq)->l : &(*pq)->r);
    if (*pq)
        return 0;
    if ((*pq = malloc(sizeof(struct Node))) == NULL)
        return 0;
    (*pq)->key = key;
    (*pq)->info = strdup(info);
    (*pq)->l = (*pq)->r = NULL;
    return 1;
}

int D_Show(struct Tree *T){
    int t;
    if (T->root == NULL)
        printf("Tree empty!\n");
    else{
        printf("What order you want to print? \nPress 1 to print Left-Right-Center\nPress 2 to print Right-Left-Center\n");
        while(!getInt(&t) || t > 2 || t < 1){
            printf("Error! Please enter number 1 or 2");
        }
        if (t == 1)
            print_tree_node_LRC(T->root);
        if (t == 2)
            print_tree_node_RLC(T->root);
        }
    return 1;
}

void print_tree_node_LRC(struct Node *q){
    if (q == NULL) return;
    print_tree_node_LRC(q->l);
    print_tree_node_LRC(q->r);
    printf("Key %d\t\t %s\n", q->key, q->info);
}

void print_tree_node_RLC(struct Node *q){
    if(q == NULL) return;
    print_tree_node_RLC(q->r);
    print_tree_node_RLC(q->l);
    printf("Key %d\t\t %s\n", q->key, q->info);
}

void free_tree(struct Tree *T){
    free_tree_node(T->root);
    T->root = NULL;
}

void free_tree_node(struct Node *q){
    if(q == NULL) return;
    free_tree_node(q->l);
    free_tree_node(q->r);
    free(q->info);
    free(q);
}

int D_Delete(Tree *T){
    int k;
    printf("Input key-->\n");
    if (!getInt(&k))
        return 0;
    if (del_tree(T,k))
        printf("Deleted!\n");
    else
        printf("Error\n");
    return 1;
}

int del_tree(struct Tree *T, int key){
    struct Node **pq, *q;
    for (pq = &T->root; *pq && (*pq)->key != key; pq = (*pq)->key > key ? &(*pq)->l : &(*pq)->r);
    if (*pq == NULL) {
        return 0;
    }
    q = *pq;
    if ((*pq)->l && (*pq)->r){
        for (pq = &(*pq)->l; (*pq)->r; pq = &(*pq)->r);
            free(q->info);
    }
    if (q != *pq){
        q->key = (*pq)->key;
        q->info = (*pq)->info;
    }
    q = *pq;
    *pq = (*pq)->l ? (*pq)->l : (*pq)->r;
    free(q);
    return 1;
}

int D_Find(Tree *T){
    int k;
    char *s;
    printf("Input key -->\n");
    if(!getInt(&k))
        return 0;
    if((s = search(T,k)))
        printf("Found!\n");
    else
        printf("Not found!\n");
    return 1;
}

char *search(struct Tree *T, int key){
    struct Node *q;
    for (q = T->root; q ; q = key <= q->key ? q->l : q->r){
        if (q->key == key){
            printf("Key: %d\t%s\n",q->key, q->info);
        }
    }
    for (q = T->root; q && q->key != key ; q = key < q->key ? q->l : q->r);
        return q ? q->info : NULL;
}

Node *find(struct Tree *T, int key){
    struct Node *q;
    for (q = T->root; q && q->key != key; q = key <= q->key ? q->l : q->r);
        return q ? q : NULL;
}

int D_Find_Min(Tree *T){
    Node *s;
    int k;
    printf("Input key -->\n");
    if(!getInt(&k))
        return 0;
    if((s = findMin(T,k)))
        printf("Found!\n");
    else
        printf("Not found!\n");
    return 1;
}

Node *findMin(struct Tree *T, int key){
    Node *q = T->root;
    Node *t = T->root;
    int keymin;
    if(!q&&!t)
        return NULL;
    for (t = T->root; t->r ; t = key <= t->key ? t->l : t->r,keymin = t->key){
    }
    for (q = T->root; q ; q = keymin <= q->key ? q->l : q->r)
        if (q->key == keymin)
            printf("Key %d\t\t %s\n", q->key, q->info);
    return t;
}

void padding(char ch,int n)
{
  int i;
  for (i = 0; i < n; i++ )
    putchar(ch);
}

void putTree( struct Node *root, int level )
{
  if (root == NULL){
    padding('\t', level);
    puts (" ");
  }
  else {
    putTree( root->r, level + 1 );
    padding ('\t', level);
    printf ("%d\n", root->key);
    putTree(root->l, level + 1);
  }
}

int D_Print_Tree(Tree *T){
    if (T->root == NULL){
        printf("Tree empty!\n");
        return 0;
    }
    else
        printf("Tree:\n");
    putTree(T->root,0);
    return 1;
}

float myfunc(float x) {
    return 2*(x) + 1;
};


