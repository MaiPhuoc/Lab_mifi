#include <stdio.h>
#include "calc4.h"
#include "y.tab.h"
char lbl = 0;
int ex(nodeType *p) {
if (!p) return 0;
	if (lbl == p->label)
		lbl = 0;
if (!lbl)
	switch(p->type) {
	case typeCon: return p->con.value;
	case typeId: return sym[p->id.i];
	case typeOpr:
		switch(p->opr.oper) {
		case WHILE: while(ex(p->opr.op[0])) ex(p->opr.op[1]); return 0;
		case IF: if (ex(p->opr.op[0]))
			ex(p->opr.op[1]);
		else if (p->opr.nops > 2)
			ex(p->opr.op[2]);
		return 0;
	case PRINT: if (p->opr.op[0]->type == typeId)
		printf ("%s = ",p->opr.op[0]->id.c);
		printf("%d\n", ex(p->opr.op[0])); return 0;
	case ';': ex(p->opr.op[0]); return ex(p->opr.op[1]);
	case '=': return sym[p->opr.op[0]->id.i] = ex(p->opr.op[1]);
	case UMINUS: return -ex(p->opr.op[0]);
	case '+': return ex(p->opr.op[0]) + ex(p->opr.op[1]);
	case '-': return ex(p->opr.op[0]) - ex(p->opr.op[1]);
	case '*': return ex(p->opr.op[0]) * ex(p->opr.op[1]);
	case '/': return ex(p->opr.op[0]) / ex(p->opr.op[1]);
	case '<': return ex(p->opr.op[0]) < ex(p->opr.op[1]);
	case '>': return ex(p->opr.op[0]) > ex(p->opr.op[1]);
	case GE: return ex(p->opr.op[0]) >= ex(p->opr.op[1]);
	case LE: return ex(p->opr.op[0]) <= ex(p->opr.op[1]);
	case NE: return ex(p->opr.op[0]) != ex(p->opr.op[1]);
	case EQ: return ex(p->opr.op[0]) == ex(p->opr.op[1]);
	case GOTO: if (!addr[p->opr.op[0]->id.i])
	printf("Identificator '%s' is not detected: - ignore goto!\n", p->opr.op[0]->id.i);
				else
				lbl = p->opr.op[0]->id.i;
	return 0;
	}
}
else
{
switch(p->type) {
	case typeCon: return 0;
	case typeId: return 0;
		case typeOpr:
		switch(p->opr.oper) {
		case WHILE: do ex(p->opr.op[1]); while (ex(p->opr.op[0])); return 0;
		case IF: ex(p->opr.op[1]);
			if (lbl && p->opr.nops > 2)
				ex(p->opr.op[2]);
			return 0;
		case ';': ex(p->opr.op[0]); return ex(p->opr.op[1]);
		default: return 0;
	}
}
}
return 0;
}
int exec(nodeType *p)
{
do
{
ex(p);
}
while (lbl);
}