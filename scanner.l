/*
Integrantes do grupo:
Igor Ladeira Pereira - 218760
Rafael Finkelstein - 194640
*/



%{

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "y.tab.h"

int globalLineNumber = 1;
int running = 1;

int getLineNumber(void);
int isRunning(void);
%}



%x COMMENT

%%



word		{ return KW_WORD; }	
bool		{ return KW_BOOL; }
byte		{ return KW_BYTE; }
if			{ return KW_IF; }
then		{ return KW_THEN; }
else		{ return KW_ELSE; }
loop		{ return KW_LOOP; }		
input		{ return KW_INPUT; }
return		{ return KW_RETURN; }
output		{ return KW_OUTPUT; }	

TRUE		{ yylval.symbol=hashInsert(yytext, LIT_TRUE); return LIT_TRUE; }
FALSE		{ yylval.symbol=hashInsert(yytext, LIT_FALSE); return LIT_FALSE; }

["][^"]*["]					{yylval.symbol=hashInsert(yytext, LIT_STRING); return LIT_STRING; }
[A-Za-z_][A-Za-z_0-9]*		{yylval.symbol=hashInsert(yytext, TK_IDENTIFIER); return TK_IDENTIFIER; }
'.' 						{yylval.symbol=hashInsert(yytext, LIT_CHAR); return LIT_CHAR; }
[0-9]+						{yylval.symbol=hashInsert(yytext, LIT_INTEGER); return LIT_INTEGER; }

[<][=]		{ return OPERATOR_LE; }
[>][=]		{ return OPERATOR_GE; }
[=][=]		{ return OPERATOR_EQ; }
[!][=]		{ return OPERATOR_NE; }
[&][&]		{ return OPERATOR_AND; }
[|][|]		{ return OPERATOR_OR; }

[-,;:()\[\]{}+\-*/<>=!&$]	{ return yytext[0]; }

[ \t]
\n				{ globalLineNumber++; }

"//".*
"/*"			{ BEGIN(COMMENT); }
<COMMENT>\n		{ globalLineNumber++; }
<COMMENT>.
<COMMENT>"*/"	{ BEGIN(INITIAL); }


['][^']*[']		{ printf("token error: %s at line %d\n", yytext, getLineNumber()); return TOKEN_ERROR; }
.				{ printf("token error: %s at line %d\n", yytext, getLineNumber()); return TOKEN_ERROR; }

%%


int yywrap (void) {
	running = 0;	
	return 1;
}

int getLineNumber(void) {
	return globalLineNumber;
}

int isRunning(void) {
	return running;
}

void initMe(void) {
	hashInit();
}

