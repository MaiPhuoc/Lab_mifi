#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include <stdlib.h>
#include <assert.h>
#define MAX 20
typedef struct comp{
    float RE;
    float IM;
}comp;
typedef struct
{
    int n;
    comp *ar;
}line;
typedef struct
{
    int m;
    line *pt;
}Matrix;
comp sum_comp(comp *a, comp *b);
comp mul_comp(comp *a, comp *b);
void getsize(int *m,int *n);
void input_matrix(Matrix *rm);
void print_matrix(Matrix rm);
void free_matrix(Matrix rm);
void sum_matrix(Matrix rm1, Matrix rm2, Matrix *rm_sum);
void multi_matrix(Matrix rm1, Matrix rm2, Matrix *rm_mul);
void trans_matrix(Matrix rm, Matrix *rm_t);
int clean_stdin();
int getInt();
float getFloat();
void test_comp();
int main()
{
    Matrix *rm,rmS,rmM,rmT;
    int k,i;
    int a,b,c,d,e;
    int lenh;
    printf("This is program to get:\n - sum matrix\n - multi matrix\n - transpose matrix\n which is member number is complex.\n\n");
    test_comp();
    printf("How many matrix you want to enter?\n");
    k=getInt();
    if(k<=0) return 0;
    rm =(Matrix *)malloc((k-1)*sizeof(Matrix));
    printf("NOTE: Please input real number in formal: z = a + bi\n");
    for(i=0;i<k;i++)
        {   printf("Input %c[m][n]\n",65+i);
            input_matrix(&rm[i]);
        }
    begin:
    system("cls");
    for(i=0;i<k;i++)
        {
            printf("Your input %c[m][n]\n",65+i);
            print_matrix(rm[i]);
        }
    printf("MENU:\n");
    printf("1. Press 1 to plus 2 matrix.\n");
    printf("2. Press 2 to multiply 2 matrix.\n");
    printf("3. Press 3 to inverse matrix.\n");
    printf("4. Press 4 to end.\n");
    scanf("%d",&lenh);
    switch(lenh)
    {
    case 1:
        {
        printf("\nWhich the matrix you want to have a sum?\n(Matrix A -> press 0, B -> press 1 ... so on)\n");
        a=getInt();
        b=getInt();
        if((a>=k)||(b>=k))
        {
            printf("Sorry, we don't have that matrix in data\n");
            system("pause");
            goto begin;
        }
        else if((rm[a].m==rm[b].m) && (rm[a].pt[0].n==rm[b].pt[0].n))
            {
                sum_matrix(rm[a],rm[b],&rmS);
                printf("Matrix sum is\n");
                print_matrix(rmS);
                free_matrix(rmS);
            }
        else
        {
            printf("\nSorry, your matrix are not enable to add!\n");
        }
        system("pause");
        goto begin;
        break;}
    case 2:
        {
        printf("\nWhich the matrix you want to have a multiplication?\n(Matrix A -> press 0, B -> press 1 ... so on)\n");
        c=getInt();
        d=getInt();
        if((c>=k)||(d>=k)) {
            printf("Sorry, we don't have that matrix in data\n");
            system("pause");
            goto begin;
        }
        else
        if((rm[c].pt[0].n== rm[d].m))
            {
            multi_matrix(rm[c],rm[d],&rmM);
            printf("Matrix multiplication is\n");
            print_matrix(rmM);
            free_matrix(rmM);
            }
        else
        {
            printf("\nSorry, your matrix are not enable to multiply, choice anothers!\n");
        }
        system("pause");
        goto begin;
        break;}
    case 3:
        {
        printf("\nWhich the matrix you want to have a transpose?\n(Matrix A -> press 0, B -> press 1 ... so on)\n");
        e = getInt();
        if(e>=k)
        printf("Sorry, we don't have that matrix in data\n");
        else
            {
            trans_matrix(rm[e],&rmT);
            printf("Matrix transpose is\n");
            print_matrix(rmT);
            free_matrix(rmT);
            }
        system("pause");
        goto begin;
        break;}
    case 4:
        return 0;
    default:
        {printf("Please choose from 1-4^^!\n");
        system("pause");
        goto begin;
        break;}
    }
// FREEEEE
    for(i=0;i<k;i++){
    free_matrix(rm[i]);}
    return 0;
}
comp sum_comp(comp *a, comp *b){
    comp m = {(*a).RE + (*b).RE, (*a).IM + (*b).IM};
    return m;
}
comp mul_comp(comp *a, comp *b){
    comp n = {((*a).RE)*((*b).RE) -  ((*a).IM)*((*b).IM),((*a).IM)*((*b).RE) +  ((*a).RE)*((*b).IM)};
    return n;
}
void getsize(int *m,int *n){
    printf("m = ");
    *m = getInt();
    assert((*m)<=MAX);
    printf("\nn = ");
    *n = getInt();
    assert((*n)<=MAX);
}
void input_matrix(Matrix *rm){
    srand (time(NULL));
    int m,n,i,j;
    char aut;
        getsize(&m,&n);
        rm->m=m;
        rm->pt=(line*)calloc(m,sizeof(line));
        for(i=0;i<m;i++)
        {
            rm->pt[i].n= n;
            rm->pt[i].ar=(comp *)calloc(n,sizeof(comp));
        }
        printf("Do you want to input auto?(Y/N)");
        scanf("%c",&aut);
        if(aut=='Y'||aut=='y')
            {srand (time(NULL));
            for(i=0;i<m;i++)
            {
                for(j=0;j<n;j++)
                {
                    rm->pt[i].ar[j].RE=((float)rand()/(float)(RAND_MAX)) *10.0;
                    rm->pt[i].ar[j].IM=((float)rand()/(float)(RAND_MAX)) *10.0;
                }
            }}
        else{
            for(i=0;i<m;i++)
            {
                for(j=0;j<n;j++)
                {
                    printf("a[%d][%d]=\n",i,j);
                    rm->pt[i].ar[j].RE=getFloat();
                    rm->pt[i].ar[j].IM=getFloat();
                }
            }}
    printf("Matrix created\n\n");
}
void print_matrix(Matrix rm){
    int i,j,m,n;
    m = rm.m;
    n = rm.pt[0].n;
        for(i=0;i<m; i++)
        {
            for(j=0;j<n;j++)
            {
                printf("%.1f + %.1fi%c",rm.pt[i].ar[j].RE,rm.pt[i].ar[j].IM,j+1==n?'\n':'\t');
            }
        }
}
void sum_matrix(Matrix rm1, Matrix rm2, Matrix *rm_sum){
    int i,j,m,n;
    m = rm1.m;
    n = rm1.pt[0].n;
    rm_sum->pt=(line*)calloc(m,sizeof(line));
    rm_sum->m = m;
    for(i=0;i<m;i++){
        rm_sum->pt[i].ar = (comp *)calloc(n,sizeof(comp));
        rm_sum->pt[i].n = n;
        };
     for(i=0;i<m; i++)
        {
            for(j=0;j<n;j++)
            {
                rm_sum->pt[i].ar[j].RE = sum_comp(&rm1.pt[i].ar[j],&rm2.pt[i].ar[j]).RE;
                rm_sum->pt[i].ar[j].IM = sum_comp(&rm1.pt[i].ar[j],&rm2.pt[i].ar[j]).IM;
            }

        }
}
void multi_matrix(Matrix rm1, Matrix rm2, Matrix *rm_mul){
    int i,j,k;
    int m,n,p;
    m = rm1.m;
    n = rm2.m;
    p = rm2.pt[0].n;
//    Create matrix multification
    rm_mul->pt=(line*)calloc(m,sizeof(line));
    rm_mul->m = m;
    for(i=0;i<m;i++){
        rm_mul->pt[i].ar = (comp *)calloc(p,sizeof(comp));
        rm_mul->pt[i].n = p;
        };
//    Multiflication
    for(i=0; i<m; i++)
    {
        for(j=0; j<p; j++)
        {
            for(k=0; k<n; k++)
                {
                rm_mul->pt[i].ar[j].RE +=  mul_comp(&(rm1.pt[i].ar[k]),&(rm2.pt[k].ar[j])).RE;
                rm_mul->pt[i].ar[j].IM +=  mul_comp(&(rm1.pt[i].ar[k]),&(rm2.pt[k].ar[j])).IM;
                }
        }
    }
}
void trans_matrix(Matrix rm, Matrix *rm_t){
    int i,j,m,n;
    m = rm.m;
    n = rm.pt[0].n;
//    Creat memory for transposed matrix
    rm_t->pt=(line*)calloc(n,sizeof(line));
    rm_t->m = n;
    for(i=0;i<n;i++){
        rm_t->pt[i].ar = (comp *)calloc(m,sizeof(comp));
        rm_t->pt[i].n = m;
        };
//    WorK
    for(i=0;i<m; i++)
        {
            for(j=0;j<n;j++)
            {
                rm_t->pt[j].ar[i].RE = rm.pt[i].ar[j].RE;
                rm_t->pt[j].ar[i].IM = rm.pt[i].ar[j].IM;
                }
        };
}
void free_matrix(Matrix rm){
    int i;
    for(i=0;i<rm.m;i++)
        free(rm.pt[i].ar);
    free(rm.pt);
}
int clean_stdin(){
    while(getchar()!='\n'){}
    return 1;
}
int getInt(){
    char c;
    int n;
    while((scanf("%d%c",&n,&c)!=2|| c!='\n')&&clean_stdin())
        printf("Invalid input, please write the integer number!\n");
    return n;
}
float getFloat(){
    char c;
    float n;
    while((scanf("%f%c",&n,&c)!=2|| c!='\n')&&clean_stdin())
        printf("Invalid input, please write the real number!\n");
    return n;
}
void test_comp(){
    printf("=== RunTests ===\n");
    comp *a,*b;
    a = (comp *)malloc(2*sizeof(comp));
    b = (comp *)malloc(2*sizeof(comp));
        a[0].RE = 1;
        a[0].IM = 2;
        b[0].RE = 3;
        b[0].IM = 4;
        a[1].RE = -5.2;
        a[1].IM = 0;
        b[1].RE = -1.0;
        b[1].IM = 2;
    /***********
     *TEST SUM *
     ***********/
    assert((sum_comp(&a[0],&b[0])).RE== 4);
    assert((sum_comp(&a[0],&b[0])).IM== 6);
    assert((float)(sum_comp(&a[1],&b[1]).RE)== (float)(-6.2));
    assert((float)(sum_comp(&a[1],&b[1]).IM)== (float)(2.0));
     /************
      *TEST MULTI*
      ************/
    assert((mul_comp(&a[0],&b[0])).RE == -5);
    assert((mul_comp(&a[0],&b[0])).IM == 10);
    assert((float)(mul_comp(&a[1],&b[1]).RE) == (float)(5.2));
    assert((float)(mul_comp(&a[1],&b[1]).IM) == (float)(-10.4));

    printf("=== RunTests OK ===\n");
    free(a);
    free(b);
}
