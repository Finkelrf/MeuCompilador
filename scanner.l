%{
#include "tokens.h"
#include "hash.h"

int globalLineNumber=1;
int running = 1;

int getLineNumber(void);
int isRunning(void);
void initMe(void);
%}



%x COMMENT

%%



word			{ return KW_WORD;}	
bool			{ return KW_BOOL;}
byte			{ return KW_BYTE;}
if			{ return KW_IF;}
then			{ return KW_THEN;}
else			{ return KW_ELSE;}
loop			{ return KW_LOOP;}		
input			{ return KW_INPUT;}
return			{ return KW_RETURN;}
output			{ return KW_OUTPUT;}	

TRUE			{ return LIT_TRUE;}
FALSE			{ return LIT_FALSE;}

["][^"]*["]		{ hashInsert(yytext,LIT_STRING);printf("Add na hash table\n");return LIT_STRING;}
[A-Za-z_][A-Za-z_0-9]*	{ hashInsert(yytext,TK_IDENTIFIER);printf("Add na hash table\n");return TK_IDENTIFIER;}
'.' 			{ hashInsert(yytext,LIT_CHAR);printf("Add na hash table\n");return LIT_CHAR;}
[0-9]+			{ hashInsert(yytext,LIT_INTEGER);printf("Add na hash table\n");return LIT_INTEGER;}

[<][=]			{ return OPERATOR_LE;}
[>][=]			{ return OPERATOR_GE;}
[=][=]			{ return OPERATOR_EQ;}
[!][=]			{ return OPERATOR_NE;}
[&][&]			{ return OPERATOR_AND;}
[|][|]			{ return OPERATOR_OR;}

[-,;:()\[\]{}+\-*/<>=!&$]	{ return yytext[0];}

\n			{globalLineNumber++;}

"//".*
"/*"			{BEGIN(COMMENT);}
<COMMENT>\n		{globalLineNumber++;}
<COMMENT>.
<COMMENT>"*/"	{BEGIN(INITIAL);}

[\t ]			//invisible characters, do nothing		
.			{printf("token error: %s at line %d\n", yytext, getLineNumber()); return TOKEN_ERROR;}
['][^']*[']		{printf("token error: %s at line %d\n", yytext, getLineNumber()); return TOKEN_ERROR;}

%%

// int main (int argc, char ** argv) {
// 	int tok = 0;
	
// 	while (running) {
// 		tok = yylex();
// 		switch (tok) {
// 			case KW_WORD: printf("KW_WORD\n"); break;
// 			case KW_BOOL: printf("KW_BOOL\n"); break; 
// 			case KW_BYTE: printf("KW_BYTE\n"); break;
// 			case KW_IF: printf("KW_IF\n"); break;
// 			case KW_THEN: printf("KW_THEN\n"); break;
// 			case KW_ELSE: printf("KW_ELSE\n"); break;
// 			case KW_LOOP: printf("KW_LOOP\n"); break;
// 			case KW_INPUT: printf("KW_INPUT\n"); break;
// 			case KW_RETURN: printf("KW_RETURN\n"); break;
// 			case KW_OUTPUT: printf("KW_OUTPUT\n"); break;
// 			case LIT_TRUE: printf("LIT_TRUE\n"); break;
// 			case LIT_FALSE: printf("LIT_FALSE\n"); break;
// 			case LIT_STRING: printf("LIT_STRING\n"); break;
// 			case TK_IDENTIFIER: printf("TK_IDENTIFIER\n"); break;
// 			case LIT_CHAR: printf("LIT_CHAR\n"); break;
// 			case LIT_INTEGER: printf("LIT_INTEGER\n"); break;
// 			case OPERATOR_LE: printf("OPERATOR_LE\n"); break;
// 			case OPERATOR_GE: printf("OPERATOR_GE\n"); break;
// 			case OPERATOR_EQ: printf("OPERATOR_EQ\n"); break;
// 			case OPERATOR_NE: printf("OPERATOR_NE\n"); break;
// 			case OPERATOR_AND: printf("OPERATOR_AND\n"); break;
// 			case OPERATOR_OR: printf("OPERATOR_OR\n"); break;
// 			default: printf("%d Caracter especial\n",tok); break;
// 		}
// 	}
	
// 	return 1;

// }

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

void initMe(){
	hashInit();
	return;
}


