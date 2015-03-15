#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "tokens.h"


void hashPrint(void);
void hashInit(void);
int hashAddress(char * text);
HASH_NODE * hashInsert(char * text, int type);

// Inicializa a tabela hash
void hashInit(void)
{
	int i;

	for(i=0; i < HASH_SIZE; i++)
	{
		hashTable[i] = NULL;
	}
}

// Calcula o endereço da tabela
int hashAddress(char * text)
{
	int address = 1;
	int i;

	for(i=0; i < strlen(text); i++)
		address = (address * text[i]) % HASH_SIZE + 1;

	return address - 1;
}

// Insere nodo na tabela hash
HASH_NODE * hashInsert(char * text, int type)
{

	int address;

	HASH_NODE * newNode;

	address = hashAddress(text);

	newNode = (HASH_NODE*) calloc(1, sizeof(HASH_NODE));

	newNode->type = type;
	
	// Verifica qual é o tipo (deve tirar '' ou "")
	if(type == LIT_CHAR || type == LIT_STRING)
	{
		newNode->text = (char*) calloc(strlen(text), sizeof(char));
		strncpy(newNode->text, text+1, strlen(text)-2);
	}
	else
	{
		newNode->text = (char*) calloc(strlen(text)+1, sizeof(char));
		strcpy(newNode->text, text);
	}

	// Insere no início da lista
	newNode->next = hashTable[address];
	hashTable[address] = newNode;

	return newNode;

}

// Imprime valores diferentes de null
void hashPrint(void)
{
	int i;
	HASH_NODE * aux;

	for(i=0 ; i < HASH_SIZE ; i++)
	{
		aux = hashTable[i];

		if(aux != NULL)
		{
			do
			{

				switch(aux->type)
				{
					case TK_IDENTIFIER:
						printf("Posicao: %d | text: %s | type: IDENTIFIER", i, aux->text);
					break;
					case LIT_INTEGER:
						printf("Posicao: %d | text: %s | type: INTEGER", i, aux->text);
					break;
					case LIT_FALSE:
						printf("Posicao: %d | text: %s | type: FALSE", i, aux->text);
					break;
					case LIT_TRUE:
						printf("Posicao: %d | text: %s | type: TRUE", i, aux->text);
					break;
					case LIT_CHAR:
						printf("Posicao: %d | text: %s | type: CHAR", i, aux->text);
					break;
					case LIT_STRING:
						printf("Posicao: %d | text: %s | type: STRING", i, aux->text);
					break;
					default:
					break;
			
				}
				
				aux = aux->next;
				printf("\n");

			}
			while(aux != NULL);

				
		}
		
	}
}

// int main(int argc, char const *argv[])
// {
// 	hashInit();
// 	hashInsert("String 1",280);
// 	hashInsert("String 1",280);
// 	hashInsert("String 1",280);
// 	hashPrint();
// 	return 0;
// }