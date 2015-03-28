/*
Integrantes do grupo:
Igor Ladeira Pereira - 218760
Rafael Finkelstein - 194640
*/

#include <stdio.h>
#include <stdlib.h>

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
	}

	
	while (isRunning()) {
		tok = yylex();
		if(tok)
			printf ("found token %d at line %d\n", tok, getLineNumber());
	}
	
	printf("\n\n");
	printf("HashTable:\n");
	hashPrint();

	return 1;

}
