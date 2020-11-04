%{
#include <stdlib.h>
#include "calc4.h"
#include "y.tab.h"
void yyerror(char *);
%}
%%

[0-9]+ {
	yylval.iValue = atoi(yytext);
	return INTEGER;
}
[-()<>=+*/;:{}.] {
	return *yytext;
}
">=" return GE;
"<=" return LE;
"==" return EQ;
"!=" return NE;
"while" return WHILE;
"if" return IF;
"else" return ELSE;
"print" return PRINT;
"goto" return GOTO;
[ \t\n]+ ; /* ignore whitespace */
[a-z]+ {
yylval.sIndex = yytext ;
return VARIABLE;
}
. yyerror("Unknown character");
%%
int yywrap(void) {
return 1;
}