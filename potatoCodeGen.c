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
	///*
	if ((ast->down)->svalue != NULL)
		printf(" %s", (ast-> down)->svalue);
	else
		printf(" %d", (ast-> down)->value);
	
	printf(" %s", ast->type);
	
	if ((ast->next)->svalue != NULL)
		printf(" %s\n", (ast-> next)->svalue);
	else	
		printf(" %d\n", (ast-> down)->value);
}

void generateCode (no *ast){
	no *dummy = NULL;
	
	//Assign
	if (!strcmp(ast->type, "assign")){
		variableNumber++;
		printf(".local num ");
		printf("%s\n", (ast->down) -> svalue);
		printf("%s =", (ast->down) -> svalue);
		if (!strcmp((ast->next)->type, "number"))
			printf(" %d\n", (ast -> next)-> value);
		else if (!strcmp((ast->next)->type, "id"))
			printf(" %s\n", (ast -> next)-> svalue);
		else getExpression(ast->next);
	}
	
	//Print generation
	if (!strcmp(ast->type, "chamada de funcao")){
		printf("%s", (ast->down)->svalue);
		if ((ast->next)->svalue != NULL)
			printf(" %s\n", (ast->next)->svalue);
	}
	
	
	//If generation 
	if (!strcmp(ast->type, "if")){
		printf("if ");
		if (checkConstruction(ast, "if", "bloco", "true"))
			printf("1 ");
		else if (checkConstruction(ast, "if", "bloco", "false"))
			printf("0 ");
		else{ 
			getExpression(ast -> next);		
		}
		labelNumber++;
		printf("goto label%d\n", labelNumber);
		//Check content of bloco
		printf("label%d: \n", labelNumber);
		generateCode((ast -> down) -> down);		
	}	
}
