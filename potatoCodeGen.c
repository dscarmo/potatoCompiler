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



void varGen(no *ast){
	
	if 	(ast == NULL){
		return;
	} else {
		varGen(ast->down);
	
		generateVar(ast);
				
		varGen(ast->next);
		
	}
}

void generateVar(no *ast){
	if (!strcmp(ast->type, "criavar")){
		if (!ast->next)		 
			printf ("%s: .word  0\n", (ast->down)->svalue);
		else{	
			printf ("%s: .word  %d\n", (ast->down)->svalue,(ast->next)->value);
		}	

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

void callExpression(no* ast){
	if (!strcmp(ast->type, "+")){
		printf("li $a0, %d\n",(ast->down)->value);
  		printf("sw $a0, 0($sp)\n");
  		printf("addiu $sp, $sp, -4\n\n");

  		printf("li $a0, %d\n",(ast->next)->value);
  		printf("lw $t1, 4($sp)\n\n");
  
  		printf("add $a0, $a0, $t1\n\n");
  
  		printf("addiu $sp, $sp, 4\n\n");
		
		
	}
	if (!strcmp(ast->type, "-")){
		printf("li $a0, %d\n",(ast->down)->value);
  		printf("sw $a0, 0($sp)\n");
  		printf("addiu $sp, $sp, -4\n\n");

  		printf("li $a0, %d\n",(ast->next)->value);
  		printf("lw $t1, 4($sp)\n\n");
  
  		printf("sub $a0, $a0, $t1\n\n");
  
  		printf("addiu $sp, $sp, 4\n\n");
		
		
	}
	if (!strcmp(ast->type, "*")){
		printf("li $a0, %d\n",(ast->down)->value);
  		printf("sw $a0, 0($sp)\n");
  		printf("addiu $sp, $sp, -4\n\n");

  		printf("li $a0, %d\n",(ast->next)->value);
  		printf("lw $t1, 4($sp)\n\n");
  
  		printf("mul $a0, $a0, $t1\n\n");
  
  		printf("addiu $sp, $sp, 4\n\n");
		
	}
	if (!strcmp(ast->type, "/")){
		printf("li $a0, %d\n",(ast->down)->value);
  		printf("sw $a0, 0($sp)\n");
  		printf("addiu $sp, $sp, -4\n\n");

  		printf("li $a0, %d\n",(ast->next)->value);
  		printf("lw $t1, 4($sp)\n\n");
  
  		printf("mul $a0, $a0, $t1\n\n");
  
  		printf("addiu $sp, $sp, 4\n\n");
		
	}
}

void callPrint(){
	printf("li $v0, 1\n");
  	printf("syscall\n\n");
}


void generateCode (no *ast){
	no *dummy = NULL;
	
	//Assign
	if (!strcmp(ast->type, "assign")){
		variableNumber++;
		//printf(".data ");
		//printf("%s\n", (ast->down) -> svalue);
		//printf("%s =", (ast->down) -> svalue);
		if (!strcmp((ast->next)->type, "number")){
			printf("li $a0 %d\n", (ast -> next)-> value);
			printf("sw $a0, 0($sp)\n\n");
  			//printf("addiu $sp, $sp, -4\n\n");
			//printf("addiu $sp, $sp, 4\n\n");
			printf("sw $a0, %s\n\n",(ast->down) -> svalue);
			printf("lw $a0, %s\n\n",(ast->down) -> svalue);
			
		}
		else if (!strcmp((ast->next)->type, "id")){
			printf("lw $t0, %s\n",(ast -> next)-> svalue) ; 
			printf("sw $t0, %s\n\n",(ast->down) -> svalue);			
			//printf(" %s\n", (ast -> next)-> svalue);
		}
		else{	
			callExpression(ast -> next);
			printf("sw $a0, %s\n\n",(ast->down) -> svalue);
			printf("lw $a0, %s\n\n",(ast->down) -> svalue);
		 	//getExpression(ast->next);
		}
	}
	
	//Print generation
	if (!strcmp(ast->type, "chamada de funcao")){
		if (!strcmp((ast->down)->svalue, "print")){
			if (!strcmp((ast->next->down)->type, "id")){
				//printf(" %s\n", (ast -> next->down)-> svalue);
				callPrint();
			}
			else if (!strcmp((ast->next->down)->type, "number")){
				//printf(" %d\n", (ast -> next->down)-> value);
				printf("li $a0, %d\n",(ast -> next->down)-> value);
  				printf("sw $a0, 0($sp)\n\n");
				callPrint();
			}
			else{
				callExpression(ast -> next ->down);
				callPrint();
			}
		}

		
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

//HUE

