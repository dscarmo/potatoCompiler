#include "ast.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


const char* varlist[200] ;
int j=0;
int size=0;
void criaLista(){
	for(int i=0;i < 200;i++){
		varlist[i]=0;
	}
}

void addLista(const char* c){
	varlist[j]=c;
	j++;
}

void printLista(){
	printf("%s\n",varlist[0]);
	printf("%s\n",varlist[1]);
}

int checkVar(const char* c){
	int i=0;
	for (int i=0;i<j;i++){
		if (strcmp (c,varlist[i])==0){
			return 1;
			}		
	}
	return 0;
}

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
		//Posfix print
		printAst(n->down);
		printAst(n->next);
		printf("%s", n->type);
						
		if (!strcmp(n->type, "id"))
			printf(", name: %s \n", n->svalue); //bugando
		else 
		if (!strcmp(n->type, "number"))
			printf(" value: %d \n", n->value);
		else 
			printf("\n");
					
		
	}	
}


