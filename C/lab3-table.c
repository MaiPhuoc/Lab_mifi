#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#define SIZE 10
typedef struct Person {
    int key; //priority
    int offset1;
    int offset2; // information person will be written in file
    int len1; // 1 --> for person's name
    int len2;  // 2 --> for number of passport
}Person;

typedef struct Table {
    int SZ; //size of table
    int n; // size of vector, 1 vector = 1 person
    Person *first;
    FILE *fd;
}Table;

int getInt(int*);
char *getstring();
int D_Load(Table*);
int load (Table *, char *);
int create(Table *, char *, int );
int D_ADD(Table*);
void sor(Table *);
int insert(Table *, int, char *,char *);
int D_FIND_MAX(struct Table*);
char *findName(Table, int);
char *findPass(Table, int);
int D_DEL_MAX(Table *);
int del(Table *);
int D_PRINT(Table *);
void print(Table *, int, int);
int D_CHANGE_PRIO(Table *);
int change_priority(Table *, int , int);
int save(Table *);
int delTable(Table *);
void run_test();

int dialog(const char *msgs[], int N);
const char *msgs[] = { "0. Exit", "1. Add", "2. Delete max", "3. Search max", "4. Change priority", "5. Print" };
const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
int(*fptr[])(struct Table*) = {NULL, D_ADD, D_DEL_MAX, D_FIND_MAX, D_CHANGE_PRIO, D_PRINT};
char *errmsgs[3] = {"Person successly added", "Table overflow"};

int main(){
    Table table = {0,0,NULL,NULL};
    run_test();
    int rc;
    if(D_Load(&table)==0)
        return 1;

    while ((rc = dialog(msgs, NMsgs))) {
        system("cls");
		fptr[rc](&table);}
    save(&table);

    printf("That's all. Bye!\n");
    delTable(&table);

    return 0;
}

int dialog(const char *msgs[], const int Nmsgs) {
	char *errmsg = "\n";
	int rc, i, n;
	do {
		printf("%s", errmsg);
		errmsg = "Repeat please\n";
		for (i = 0; i < Nmsgs; printf("%s\n", msgs[i]), i++);
		printf("Enter item: --> ");
		n = getInt(&rc);
		if (!n) rc = 0;

	} while (rc < 0 || rc >= Nmsgs);
	return rc;
}

int getInt(int *a) {
	int n;
	do {
		n = scanf("%d", a);
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
        l = strlen(buf) + strlen(str) + 1;
		p = (char *)realloc(str,l);
		if (p == NULL){
			free(str); return NULL;
		}
		str = p;
		strcat(str, buf);}
		} while (n > 0);
	return str;
}

int load (Table *ptab, char *fname){
    ptab->fd = fopen(fname, "r+b");
    if (ptab->fd == NULL)
        return 0;
    fread(&ptab->SZ, sizeof(int), 1, ptab->fd);
    ptab->first = (Person *)calloc(ptab->SZ, sizeof(Person));
    fread(&ptab->n, sizeof(int), 1, ptab->fd);
    fread(ptab->first, sizeof(Person), ptab->n, ptab->fd);
    return 1;
}

int create(Table *ptab, char *fname, int sz){
    ptab->SZ = sz;
    ptab->n = 0;
    if ((ptab->fd = fopen(fname, "w+b")) == 0){
        ptab->first = NULL;
        return 0;
    }
    ptab->first = (Person *)calloc(ptab->SZ, sizeof(Person));
    fwrite(&ptab->SZ, sizeof(int), 1, ptab->fd);
    fwrite(&ptab->n, sizeof(int), 1, ptab->fd);
    fwrite(ptab->first, sizeof(Person), ptab->SZ, ptab->fd);
    return 1;
}

int D_Load(Table *ptab){
    int SZ;
    char *fname = NULL;
    printf("Enter file name: -->");
    fname = getstring();
    if(fname == NULL)
        return 0;
    if (load(ptab, fname) == 0){
        printf("Enter number of person: -->");
        if(getInt(&SZ) == 0)
            return 0;
        create(ptab, fname, SZ);
    }
    free(fname);
    return 1;
}

int D_ADD(Table *ptab){
    int k, rc, d;
    char *name = NULL, *passport = NULL;
    printf("Enter priority: -->\n");
    d = getInt(&k);
    if(d == 0)
        return 0;
    printf("Enter full name:\n");
    scanf("%*c");
    name = getstring();
    if(name == NULL)
        return 0;
    printf("Enter number of passport\n");
    passport = getstring();
    if(passport == NULL)
        return 0;
    rc = insert(ptab, k, name, passport);
    free(name);
    free(passport);
    sor(ptab);
    printf("%s: %d\n",errmsgs[rc],k);
    return 1;
}

int insert(Table *ptab, int k, char *name, char *pass){
    if(ptab->n >= ptab->SZ)
        return 1;
    ptab->first[ptab->n].key = k;
    // write person's name to file
    ptab->first[ptab->n].len1 = strlen(name) + 1;
    fseek(ptab->fd, 0, SEEK_END);
    ptab->first[ptab->n].offset1 = ftell(ptab->fd);
    fwrite(name, sizeof(char), ptab->first[ptab->n].len1, ptab->fd);
    // write number of passport to file
    ptab->first[ptab->n].len2 = strlen(pass) + 1;
    fseek(ptab->fd, 0, SEEK_END);
    ptab->first[ptab->n].offset2 = ftell(ptab->fd);
    fwrite(pass, sizeof(char), ptab->first[ptab->n].len2, ptab->fd);
    ++(ptab->n);
    return 0;
}

int D_FIND_MAX(Table *ptab){
   int n, i;
   n = (*ptab).first[(*ptab).n - 1].key; //key of the last person
   if(n > 0){
        printf("No\t Priority\t Name\t\t Passport\n");
       for(i = 0; i < (*ptab).n; i++){
            if((*ptab).first[i].key == n){
                print(ptab, n, i);
            }
       }
    }
   else
        printf("Table is empty!\n");
   return 1;
}

char *findName(Table ptab,int i){
    char *name = NULL;
    name = (char *)malloc(ptab.first[i].len1);
    fseek(ptab.fd, ptab.first[i].offset1, SEEK_SET);
    fread(name, sizeof(char), ptab.first[i].len1, ptab.fd);
    return name;
}

char *findPass(Table ptab,int i){
    char *pass = NULL;
    pass = (char *)malloc(ptab.first[i].len2);
    fseek(ptab.fd, ptab.first[i].offset2, SEEK_SET);
    fread(pass, sizeof(char), ptab.first[i].len2, ptab.fd);
    return pass;
}

int D_DEL_MAX(Table *ptab){
    if((*ptab).n > 0){
        del(ptab);
        printf("Deleted highest priority!\n");
    }
    else
        printf("Table is empty!\n");
   return 1;
}

int del(Table *ptab){
    int n, i , last;
    last = (*ptab).n;
    n = (*ptab).first[last - 1].key;
    for(i = 0; i < last; i++){
        if((*ptab).first[i].key == n){
            --(ptab->n);
            continue;
        }
    }
    return 1;
}

void sor(Table *ptab){
    int i,j;
    if(ptab->n > 0){
        for (i = 0; i < ptab->n -1; i++){
            for(j = i + 1  ; j < ptab->n; j++){
                if (ptab->first[i].key > ptab->first[j].key){
                    Person temp;
                    temp = ptab->first[i];
                    ptab->first[i] = ptab->first[j];
                    ptab->first[j] = temp;
                }
            }
        }
    }
}

int D_PRINT(Table *ptab){
    int i, k;
    printf("No\t Priority\t Name\t\t Passport\n");
    for(i = 0; i < (*ptab).n; i++){
        k = ptab->first[i].key;
        print(ptab, k, i);
    }
   return 1;
}

void print(Table *ptab, int k, int i){
    char *name = NULL, *pass = NULL;
    name = findName(*ptab, i);
    pass = findPass(*ptab, i);
    printf("%d\t %d       \t %s\t\t %s\n",i, k, name, pass);
    free(name);
    free(pass);
}

int D_CHANGE_PRIO(Table *ptab){
    int n, i, k;
    D_PRINT(ptab);
    printf("Choose the number you want to change.\n");
    if ((n = getInt(&i)) == 0) return 0;
    printf("Number %d will change priority to?\n", i);
    if ((n = getInt(&k)) == 0) return 0;
    if (change_priority(ptab, i, k)){
        printf("Number %d changed!\n", i);
        sor(ptab);
        return 1;
    }
    else
        return 0;
}

int change_priority(Table *ptab, int i, int k ){
    int n = (*ptab).n;
    if (i < 0 && i >= n) return 0;
        else {
        ptab->first[i].key = k;
        return 1;
        }
}

int save(Table *ptab){
    fseek(ptab->fd, sizeof(int), SEEK_SET);
    fwrite(&ptab->n, sizeof(int), 1, ptab->fd);
    fwrite(ptab->first, sizeof(Person), ptab->n, ptab->fd);
    fclose(ptab->fd);
    ptab->fd = NULL;
    return 1;
}

int delTable(Table *ptab){
    free(ptab->fd);
    free(ptab->first);
    return 1;
}

void run_test(){
    printf("=== RunTests ===\n");
    //create
    Table ptest = {0,0,NULL,NULL};
    char *nametest = "run_test1";
    char *name1 = "mai", *name2 = "ha", *name3 = "le", *pas1 = "A01", *pas2 = "B02", *pas3 = "C03";
    char *t,*p;
    create(&ptest, nametest, 2);
    //test function ADD
    assert((insert(&ptest, 1, name1, pas1)) == 0);
    assert((insert(&ptest, 2, name2, pas2)) == 0);
    assert((insert(&ptest, 1, name3, pas3)) == 1);
    //test function DEL_MAX
    assert((del(&ptest) ==1) && (ptest.n == 1));
//    t = findName(ptest,0);
    assert(*(t = findName(ptest,0)) == *name1);
    assert(*(p = findPass(ptest,0)) == *pas1);
    assert((change_priority(&ptest, 0, 3) == 1) && (ptest.first[0].key == 3));
    assert((save(&ptest) == 1));
    assert((delTable(&ptest) == 1));

    printf("=== RunTests OK ===\n");
}
