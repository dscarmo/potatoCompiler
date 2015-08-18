#include "ast.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static no *alocarNo(){
	no *n = (no *)malloc(sizeof(no));
 
    if (n == NULL){
    	printf("Houve um problema na alocação do nó.");
        return NULL;
    }
 
 	n->value = 0;
 	n->svalue = "default string";
    n->type = NULL;
    n->down = NULL;
    n->next = NULL;
 
    return n;
}

no *createNode (const char *type, no *down, no *next){
	no *n = alocarNo();
	

    n->type = type;
    n->down = down;
    n->next = next;
    
    return n;
}

no *createNumber(int value){
	no *n = alocarNo();
	n->value = value;
    n->type = "number";
    n->cGenType = NUMBER;
    n->down = NULL;
    n->next = NULL;
    
    return n;
}

no *createString(const char* svalue){
	no *n = alocarNo();
	n->svalue = svalue;
    n->type = "string";
    n->down = NULL;
    n->next = NULL;
    
    return n;
}

no *createId(const char* svalue){
	no *n = alocarNo();
	n->svalue = svalue;
    n->type = "id";
    n->down = NULL;
    n->next = NULL;
    
    return n;
}


void printAst(no *n){
	if 	(n == NULL){
		return;
	} else {
		printAst(n->down);
				
		printf("%s", n->type);
						
		//if (!strcmp(n->type, "id"))
		//	printf(", name: %s \n", n->svalue); //bugando
		//else 
		if (!strcmp(n->type, "number"))
			printf(" value: %d \n", n->value);
		else 
			printf("\n");
					
		printAst(n->next);
	}	
}



