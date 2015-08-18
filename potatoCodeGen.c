#include "ast.h"
#include "potatoCodeGen.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int variableNumber = 0;
int labelNumber = 0;

void codeGen(no *ast){
	
	if 	(ast == NULL){
		return;
	} else {
		codeGen(ast->down);
	
		generateCode(ast);
				
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

void getExpression (no *ast){
	printf("%d ", (ast -> down) -> value);
	printf("%s ", ast->type);
	printf("%d \n ", (ast-> next) -> value);
}

void generateCode (no *ast){
	//Assign
	if (!strcmp(ast->type, "assign")){
		variableNumber++;
		printf(".local num variable%d\n", variableNumber);
		printf("variable%d =", variableNumber);
		if (!strcmp((ast->next)->type, "number"))
			printf(" %d\n", (ast -> next)-> value);
		else getExpression(ast->next);
	}
	
	//If generation 
	if (!strcmp(ast->type, "if")){
		printf("if ");
		if (checkConstruction(ast, "if", "bloco", "true"))
			printf("1 ");
		else if (checkConstruction(ast, "if", "bloco", "false"))
			printf("0 ");
		else{ 
			generateCode(ast -> next);		
		}
		labelNumber++;
		printf("goto label%d\n", labelNumber);
		//Check content of bloco
		printf("label%d: \n", labelNumber);
		generateCode((ast -> down) -> down);		
	}	
}
