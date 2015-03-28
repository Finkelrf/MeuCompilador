/*
Integrantes do grupo:
Igor Ladeira Pereira - 218760
Rafael Finkelstein - 194640
*/

#include <stdio.h>
#include <stdlib.h>
#include "lex.yy.h"
#include "hash.h"
#include "y.tab.h"


int main (int argc, char ** argv) {
	int tok;
	extern FILE* yyin;

	initMe();

	if (argc < 2) {
		fprintf (stderr, "File name not specified. Call: etapa1 file_name\n");
		exit(1);
	}
	if ((yyin = fopen (argv[1], "r")) == 0) {
		fprintf (stderr, "Cannot open source file %s\n", argv[1]);
		exit(1);
	}

	
	while (isRunning()) {
		yyparse();
	}
	
	printf("\n\n");
	printf("HashTable:\n");
	hashPrint();

	exit(0);

}
