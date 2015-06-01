#ifndef __AST_H__
#define __AST_H__

typedef struct tno {
	const char *type;
	struct tno *down;
	struct tno *next; 
} no;

//no *createNumOrString (int value, char *string, int opt); desnecessario por enqnto

//no *createNode (char *type, no *down, no *next);


no *createNode (const char *type, no *down, no *next);

void printAst(no *n);

#endif 
