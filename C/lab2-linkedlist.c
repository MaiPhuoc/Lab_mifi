#include <stdio.h>
#include <string.h>


typedef struct Symbol {
	char c;
	struct Symbol *next;
} Symbol;


int getList(Symbol **);
void putList(const char *, Symbol *);
Symbol *deleteList(Symbol *);
Symbol *newString(Symbol *);
Symbol *delSpace(Symbol *);
Symbol *skipWord(Symbol *);
Symbol *delWord(Symbol *);


int getList(Symbol **pptr)
{
	char buf[101], *str;
	Symbol head = { '*', NULL };
	Symbol *last = &head;
	int n, code = 1;
	do {
		n = scanf_s("%100[^\n]", buf, 100);
		if (n < 0) {
			deleteList(head.next);
			head.next = NULL;
			code = 0;
			continue;
		}
		if (n > 0) {
			for (str = buf; *str != '\0'; ++str) {
				last->next = (Symbol *)malloc(sizeof(Symbol));
				last = last->next;
				last->c = *str;
			}
			last->next = NULL;
		}
		else
			scanf_s("%*c");
	} while (n > 0);
	*pptr = head.next;
	return code;
}

void putList(const char *msg, Symbol *ptr)
{
	printf("%s: \"", msg);
	for (; ptr != NULL; ptr = ptr->next)
		printf("%c", ptr->c);
	printf("\"\n");
}

Symbol *deleteList(Symbol *ptr)
{
	Symbol *tmp = NULL;
	while (ptr != NULL) {
		tmp = ptr;
		ptr = ptr->next;
		free(tmp);
	}
	return ptr;
}

Symbol *newString(Symbol *p) {
	Symbol head = { '*', p };
	Symbol *cur = &head, *prev = &head, *tmp;

	while (cur && (cur->next = delSpace(cur->next))) {
		tmp = skipWord(cur->next);
		if (cur->next == tmp) {
			cur->next = delWord(cur->next);
		}
		else {
			cur = tmp;
			prev = cur;
			cur = cur->next;
			if (cur) { cur->c = ' '; }
		}
	}

	if (prev->next) {
		free(prev->next);
		prev->next = NULL;
	}
	return head.next;
}

Symbol *delSpace(Symbol *p) {
	Symbol *tmp;
	while (p && (p->c == ' ' || p->c == '\t')) {
		tmp = p;
		p = p->next;
		free(tmp);
	}
	return p;
}

Symbol *skipWord(Symbol *p)
{
	Symbol *head = p; int ch1 = 1;
	while (p->next && p->next->c != ' ' && p->next->c != '\t') {
		p = p->next;
		ch1++;
	}
	if (ch1 != 3) return head;
	return p;
}


Symbol *delWord(Symbol *p)
{
	Symbol *tmp;
	while (p && p->c != ' ' && p->c != '\t') {
		tmp = p;
		p = p->next;
		free(tmp);
	}
	return p;
}

int main()
{
	Symbol *line = NULL;
	while (puts("enter string"), getList(&line)) {
		putList("Entered string", line);
		line = newString(line);
		putList("Result string", line);
		line = deleteList(line);
	}
	return 0;
}
