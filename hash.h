/*
Integrantes do grupo:
Igor Ladeira Pereira - 218760
Rafael Finkelstein - 194640
*/


#define HASH_SIZE 997



typedef struct hash_node {
	char *text;
	int type; 	
	struct hash_node *next;
} HASH_NODE;

void hashInit (void);
void hashPrint (void);
int hashAddress (char *text);
HASH_NODE * hashInsert (char *text, int type);
HASH_NODE * hashFind (char *text, int address, int type);
