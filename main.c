#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"

int main(int argc, char const *argv[])
{
	int code;
	extern FILE * yyin;

	initMe();

	printf("\n");

	if(argc < 2)
	{
		fprintf(stderr, "Insira o nome do arquivo\n");
	}

	if(!(yyin = fopen(argv[1],"r")))
	{
		fprintf(stderr, "Nao foi possivel abrir o arquivo\n");
	}

	while(isRunning())
	{

		code = yylex();

		if(code)
			printf("linha %d token %d\n", getLineNumber(), code);

	}

	printf("\n\n");
	printf("Tabela hash:\n\n");
	hashPrint();

	return 0;
}