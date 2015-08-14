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
 	n->svalue = NULL;
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
		printf("%s \n",n->type);
		if (n->type == "number")
			printf("value: %d \n", n->value);
			
		//Print de strings bugando
		//if (n->type == "string")
		//	printf("string: %s \n", n->svalue);
		//if (n->type == "id")
		//	printf("id: %s \n", n->svalue);
		//if (n->next != NULL)
			//printf("-->");
		
		printAst(n->next);
		
		//if (n->down != NULL)
			//printf("\n|\n");
		
		printAst(n->down);
	}	
}



