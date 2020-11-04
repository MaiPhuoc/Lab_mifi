#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Item {
	int key;
	int release;
	int ofset;
	int len;
	Item *next;
};

struct Table{
	Item* first;
};

typedef struct TItem{
	int key;
	int release;
	int ofset;
	int len;
}TItem;

int getInt(int *);
int find(Table *, int);
char *GetStr();
void erase(Table *);
char *loadTable(FILE *, Table *, char *);
Table *AddT(Table *, TItem *);
Table *findKey(Table *, int);
Table *Delete(Table *);
void Add(Table *, int , char *info, FILE *, char *fname);
int FindRelease(Table *, int key, int r, FILE *, char *fname);
void printTable(Table *, FILE *, char *);
void printList(Item *, FILE *, char *);
FILE *saveFile(Table *, FILE *, char *);

const char*msgs[] = { "0. Quit", "1. Add", "2. Find", "3.Find release", "4. Delete", "5. Show" };
const  int NMsgs = sizeof(msgs) / sizeof(msgs[0]);

int dialog(const char*msgs[], int);
int dialogAdd(Table *, FILE *, char *), dialogFind(Table *, FILE *, char *), dialogFindRelease(Table *, FILE *, char *), dialogDelete(Table *, FILE *, char *), dialogShow(Table *, FILE *, char *);

int(*fptr[])(Table *, FILE *, char *) = { NULL, dialogAdd, dialogFind, dialogFindRelease, dialogDelete, dialogShow };

int main()
{
	Table table = {NULL};
	int rc;
	char *fname , *fname2 = NULL;
	FILE *fd = NULL, *ft = NULL;
	printf("Enter name of file:");
	fname2 = GetStr();
	fname = "test.dat";
	fname2 = loadTable(ft, &table, fname2);

	while (rc = dialog(msgs, NMsgs))
	if (!fptr[rc](&table, fd, fname))
			break;
	ft = saveFile(&table, ft, fname2);
	erase(&table);
	return 0;
}

char *loadTable(FILE *ft, Table *tbl, char *fname2)
{
	int n = 0;
	TItem *cur = NULL;
	if (ft = fopen(fname2, "rb")) {
		while (!feof(ft)) {
			cur = (TItem *)calloc(1, sizeof(TItem));
			fread(cur, sizeof(TItem), 1, ft);
			if (cur->key == 0)
				break;
			tbl = AddT(tbl, cur);
		}
		fclose(ft);
	}
	return fname2;
}

Table *AddT(Table *tbl, TItem *cur)
{
	Item  *ptr;
	ptr = (Item *)calloc(1, sizeof(Item));
	ptr->key = cur->key;
	ptr->release = cur->release;
	ptr->ofset = cur->ofset;
	ptr->len = cur->len;
	ptr->next = tbl->first;
	tbl->first = ptr;

	tbl->first = ptr->next;
//	ptr = tbl->first;
	return tbl;
}

int dialog(const char* msgs[], const  int NMsgs)
{
	int i,rc,n;
	const char *err = "";
	do{
		printf("%s\n", err);
		err = "Error! Repeat enter!!";
		for (i = 0; i < NMsgs; ++i)
			puts(msgs[i]);
		puts("Choice the action: ");
		n = getInt(&rc);

		if (n == 0)
			rc = 0;

	} while (rc<0 || rc >=NMsgs);
	return rc;
}

int getInt(int *pa)
{
	int n;
	do
	{
		n = scanf("%d", pa);

		if (n == 0){
			printf("error!\n");
			scanf("%*[^\n]");
		}
	} while (n == 0);
	return n < 0 ? 0 : 1;
}

/*Table *findKey(Table *table, int k)
{
	Item *ptr = table->first;
	Table *newTable = { NULL };
	Item *ptrnew;

	while (ptr) {
		if (ptr->key == k) {
			ptrnew = (Item*)calloc(sizeof(Item), 1);
			ptrnew->key = ptr->key;
			ptrnew->ofset = ptr->ofset;
			ptrnew->len = ptr->len;
			ptrnew->release = ptr->release;
			ptrnew->next = newTable->first;
			newTable->first = ptrnew;
		}
		ptr = ptr->next;
	}
	return newTable;
}*/

int dialogFind(Table *table, FILE *fd, char *fname)
{
	int k;
	Item *ptr = table->first;
	Table newTable = { NULL };
	Item *ptrnew;


	printf("Enter key: ");
	getInt(&k);
//	newTable = findKey(table, k);

	while (ptr) {
		if (ptr->key == k) {
			ptrnew = (Item*)calloc(sizeof(Item), 1);
			ptrnew->key = ptr->key;
			ptrnew->ofset = ptr->ofset;
			ptrnew->len = ptr->len;
			ptrnew->release = ptr->release;
			ptrnew->next = newTable.first;
			newTable.first = ptrnew;
		}
		ptr = ptr->next;
	}

	if (&newTable == NULL)
		printf("Key is not found!\n");
	else {
		printTable(&newTable, fd, fname);
		erase(&newTable);
	}
	return 1;
}

int dialogFindRelease(Table *table, FILE *fd, char *fname)
{
	int k, r;

	printf("Enter key: ");
	getInt(&k);
	printf("Enter release: ");
	getInt(&r);

	if (FindRelease(table, k, r, fd, fname) == 0)
		printf("Key is not found!\n");
	return 1;
}

int FindRelease(Table * table, int k, int r,  FILE *fd, char *fname){
	Item *ptr = table->first;
	char *info = NULL;

	while (ptr) {
		if (ptr->key == k && ptr->release == r) {

			fd = fopen(fname, "rb");
			info = (char *)malloc(ptr->len);
			fseek(fd, ptr->ofset, SEEK_SET);
			fread(info, sizeof(char), ptr->len, fd);
			printf("key = %d, release = %d, info = %s\n", ptr->key, ptr->release, info);
			free(info);
			fclose(fd);
			return 1;
		}
		ptr = ptr->next;
	}
	return 0;
}

int find(Table *table, int k)
{
	int r = 0;
	Item *ptr = table->first;

while (ptr) {
	if (ptr->key == k && ptr->release>r){
		r = ptr->release;
	}
		ptr = ptr->next;
	}
	return r;
}

int dialogAdd(Table *table, FILE *fd, char *fname)
{
	int key;
	char *info = NULL;
	Item *ptr = NULL;

	printf("Enter key: ");
	getInt(&(key));
	printf("Enter info: ");
	scanf("%*c");
    info = GetStr();
	Add (table, key, info, fd, fname);

	return 1;
}

void Add (Table *table, int key, char *info, FILE *fd, char *fname)
{
	int r = find(table, key) + 1;
	Item *ptr = NULL;
	ptr = (Item *)calloc(sizeof(Item), 1);
	fd = fopen(fname, "ab");
	fseek(fd, 0L, SEEK_END);
	ptr->key = key;
	ptr->release = r;
	ptr->ofset = ftell(fd);
	ptr->len = strlen(info) + 1;
	fwrite(info, sizeof(char), ptr->len, fd);
	ptr->next = table->first;
	table->first = ptr;

	fclose(fd);
	free(info);
}

int dialogShow(Table *table, FILE *fd, char *fname)
{
	Item *ptr = table->first;

	if (ptr)
		printTable(table, fd, fname);
	else
		printf("Table is free\n");
	return 1;
}

void printTable(Table *table, FILE *fd, char *fname)
{
	Item *ptr = table->first;

	if (ptr)
	{
		printList(ptr, fd, fname);
		ptr = ptr->next;
	}
}

void printList(Item *ptr, FILE *fd, char *fname)
{
	char *info = NULL;
	fd = fopen(fname, "rb");
	while (ptr) {
		info = (char *)malloc(ptr->len);
		fseek(fd, ptr->ofset, SEEK_SET);
		fread(info, sizeof(char), ptr->len, fd);
		printf("key = %d, release = %d, info = %s\n", ptr->key, ptr->release, info);
		free(info);
		ptr = ptr->next;
	}
	fclose(fd);
}

int dialogDelete(Table *table, FILE *fd, char *fname)
{
	printf("Delete is succesfull.\n");

	table = Delete(table);
	printf("!\n");
	printTable(table, fd, fname);
	printf("!\n");
	return 1;
}

Table *Delete(Table *table)
{
	Item *ptr = table->first;
	Item *buf, *t;
	Item *ptr1;
	int r, k;

	while (ptr) {
		k = ptr->key;
		r = find(table, k);

		if (ptr->release == r){
			ptr1 = ptr->next;
		t = ptr;
		while (ptr1) {
			if (ptr1->key == k && ptr1->release != r) {
				t->next = ptr1->next;
				buf = ptr1;
				ptr1 = ptr1->next;
				buf->next = NULL;
			}
			else {
				t = t->next;
				ptr1 = ptr1->next;
			}
		}
	}
		if (ptr->release != r){
			ptr1 = ptr;
			t = table->first;
			while (ptr1) {
				if (ptr1->key == k && ptr1->release != r) {
					t->next = ptr1->next;
					buf = ptr1;
					ptr1 = ptr1->next;
					buf->next = NULL;
				}
				else {
					t = t->next;
					ptr1 = ptr1->next;
				}
			}
		}
		ptr = ptr->next;
	}
	return table;
}

char *GetStr()
{
	char *ptr = (char *)malloc(1);
	char buf[81];
	int n, len = 0;
	*ptr = '\0';
	do {
		n = scanf("%80[^\n]", buf);
		if (n < 0) {
			free(ptr);
			ptr = NULL;
			continue;
		}
		if (n == 0)
		{
			scanf("%*c");
		}
		else {
			len += strlen(buf);
			ptr = (char *)realloc(ptr, len + 4);
			strcat(ptr, buf);
		}
	} while (n > 0);
	return ptr;
}

void erase(Table *table)
{
	Item *ptr = table->first;
	Item *buf;

	while (ptr) {
		buf = ptr;
		ptr = ptr->next;
		buf->next = NULL;
		free(buf);
	}
}

FILE *saveFile(Table *table, FILE *ft, char *fname2)
{
	Item *ptr = NULL;
	char *info = NULL;
	if ((ft = fopen(fname2, "wb")) == NULL) {
		printf("Error\n");
		return 0;
	}
	else {
		ptr = table->first;
			while (ptr) {
				fwrite(ptr, sizeof(TItem), 1, ft);
				ptr = ptr->next;
			}
		}
	fclose(ft);
	return ft;
}

