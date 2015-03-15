#define HASH_SIZE 997

typedef struct hash_node
{
	int type;
	char * text;
	struct hash_node * next;
}HASH_NODE;

HASH_NODE * hashTable[HASH_SIZE];

void hashInit(void);
int hashAddress(char * text);
HASH_NODE * hashInsert(char * text, int type);
void hashPrint(void);