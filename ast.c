#include "ast.h"
#include <stdlib.h>
#include <stdio.h>

static no *alocarNo(){
	no *n = (no *)malloc(sizeof(no));
 
    if (n == NULL){
    	printf("Houve um problema na alocação do nó.");
        return NULL;
    }
 
    n->type = NULL;
    n->down = NULL;
    n->next = NULL;
 
    return n;
}

no *createNode (char *type, no *down, no *next){
	no *n = alocarNo();
	
	n->type = type;
    n->down = down;
    n->next = next;
}

