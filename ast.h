#ifndef __AST_H__
#define __AST_H__

#define NUMBER 1

typedef struct tno {
	const char *type;
	int value;
	int cGenType;
	const char *svalue;
	struct tno *down;
	struct tno *next; 
} no;

//no *createNumOrString (int value, char *string, int opt); desnecessario por enqnto

no *createNode (const char *type, no *down, no *next);

no *createNumber(int value);

no *createString(const char* svalue);

no *createId(const char* svalue);

no *createNode (const char *type, no *down, no *next);

void printAst(no *n);


#endif 
