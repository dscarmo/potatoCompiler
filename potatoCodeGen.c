#include "ast.h"
#include "potatoCodeGen.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void codeGen(no *ast){
	
	if 	(ast == NULL){
		return;
	} else {
		codeGen(ast->down);
	
		checkAssign(ast);
		
		codeGen(ast->next);
		
	}
}

int checkConstruction(no *ast, const char *stype, const char *sdown, const char *snext){
	if (!strcmp(ast->type, stype)){
		if (!strcmp((ast -> down)-> type, sdown) & (!strcmp((ast -> next)-> type, snext)))
			return 1;
	} 
	else 
		return 0;	
}

void checkAssign (no *ast){
	if (checkConstruction(ast, "assign", "id", "number")){
		printf(".local variable \n");
		printf("variable =");
		printf(" %d\n", (ast -> next)-> value);
	}
}
