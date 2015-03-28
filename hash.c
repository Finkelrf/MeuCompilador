/*
Integrantes do grupo:
Igor Ladeira Pereira - 218760
Rafael Finkelstein - 194640
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

HASH_NODE *table[HASH_SIZE];

//inicializa a hash
void hashInit (void) {
	int i;

	for (i=0; i < HASH_SIZE; i++)
		table[i] = 0;
}

//imprime os elementos na hash
void hashPrint (void) {
	int i;
	HASH_NODE *n;
	
	for (i=0 ; i < HASH_SIZE ; i++) {
		n = table[i];
		while (n != NULL) {
			printf ("Table [%d] has %s\n", i, n->text);
			n = n->next;
		}
	
	}
}

//calcula um endereço na hash onde o elemento vai ser armazenado
int hashAddress (char *text) {
	int address = 1;
	int i;

	for (i=0; i < strlen(text); i++)
		address = (address * text[i]) % HASH_SIZE + 1;
	
	return address-1;

}

//insere novo nodo na hash
HASH_NODE *hashInsert (char *text, int type) {  
	HASH_NODE *newNode, *auxNode;
	int address;
		
	newNode = (HASH_NODE*) calloc (1, sizeof(HASH_NODE));  //novo nodo a ser adicinado na hash
	auxNode = (HASH_NODE*) calloc (1, sizeof(HASH_NODE));  //utilizado para verificar se o elemento já existe na hash

	address = hashAddress(text); //gera um novo endereço para o elemento a ser armazenado
	
	auxNode->text = (char*) calloc(strlen(text), sizeof(char));
	if (type == LIT_CHAR || type == LIT_STRING) { //se o elemento for char ou string, deve-se remover as aspas
		strncpy(auxNode->text, text+1, strlen(text)-2); //remove as aspas do elemento
		
		if ((auxNode = hashFind(auxNode->text, address, type)) != 0) { //se o elemento já existe na hash, ele não será adicionado novamente
			return auxNode;
		}
		else { //se o elemento ainda não existe na hash, ele é adicionado
			newNode->text = (char*) calloc(strlen(text), sizeof(char));
			strncpy(newNode->text, text+1, strlen(text)-2);
		}
	}
	else { //para os outros tipos de símbolos, não há aspas a serem removidas
		strcpy(auxNode->text, text);

		if ((auxNode = hashFind(auxNode->text, address, type)) != 0)
			return auxNode;
		else {
			newNode->text = (char*) calloc(strlen(text)+1, sizeof(char));
			strcpy(newNode->text, text);
		}
	}
	
	newNode->type = type;
	newNode->next = table[address];
	table[address] = newNode;

	return newNode;
}

//procura elemento na hash
HASH_NODE * hashFind (char *text, int address, int type) {
	HASH_NODE *node;
				
	for (node = table[address]; node != NULL; node = node->next) {
		if (!strcmp(node->text, text) && node->type == type ) { //o elemento é procurado de acordo com seu campo "text" e seu tipo
			return node;
		}
	}

	return 0;

}

