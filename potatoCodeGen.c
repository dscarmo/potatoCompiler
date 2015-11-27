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

void storeReg(no *ast){
	
	if(!strcmp(ast->type, "number")){
	printf("li $a0, %d\n",(ast->value));
  	printf("sw $a0, 0($sp)\n");
	}else if(!strcmp(ast->type, "id")){
	printf("lw $a0, %s\n",(ast->svalue));
  	printf("sw $a0, 0($sp)\n");
	}

}

void storeTemp(no *ast){
	
	if(!strcmp(ast->type, "number")){
	printf("li $a0, %d\n",(ast->value));
  	printf("lw $t1, 4($sp)\n");
	}else if(!strcmp(ast->type, "id")){
	printf("lw $a0, %s\n",(ast->svalue));
  	printf("lw $t1, 4($sp)\n\n");
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
			if(!strcmp(ast->next->type, "+")){
				printf ("%s: .word  %d\n", (ast->down)->svalue,(ast->next->down)->value + (ast->next->next)->value);				
			}
			else if(!strcmp(ast->next->type, "-")){
				printf ("%s: .word  %d\n", (ast->down)->svalue,(ast->next->down)->value - (ast->next->next)->value);				
			}
			else if(!strcmp(ast->next->type, "*")){
				printf ("%s: .word  %d\n", (ast->down)->svalue,(ast->next->down)->value * (ast->next->next)->value);				
			}
			else if(!strcmp(ast->next->type, "/")){
				printf ("%s: .word  %d\n", (ast->down)->svalue,(ast->next->down)->value / (ast->next->next)->value);				
			}
			else if(!strcmp(ast->next->type, "and")){
				printf ("%s: .word  %d\n", (ast->down)->svalue,(ast->next->down)->value & (ast->next->next)->value);				
			}
			else if(!strcmp(ast->next->type, "or")){
				printf ("%s: .word  %d\n", (ast->down)->svalue,(ast->next->down)->value | (ast->next->next)->value);				
			}
			else printf ("%s: .word  %d\n", (ast->down)->svalue,(ast->next)->value);
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
		storeReg(ast->next);		
  		printf("addiu $sp, $sp, -4\n\n");

  		storeTemp(ast->down);
  		printf("add $a0, $a0, $t1\n\n");
  
  		printf("addiu $sp, $sp, 4\n\n");
		
		
	}
	if (!strcmp(ast->type, "-")){
		storeReg(ast->next);
  		printf("addiu $sp, $sp, -4\n\n");

  		storeTemp(ast->down);
  
  		printf("sub $a0, $a0, $t1\n\n");
  
  		printf("addiu $sp, $sp, 4\n\n");
		
		
	}
	if (!strcmp(ast->type, "*")){
		storeReg(ast->next);
  		printf("addiu $sp, $sp, -4\n\n");

  		storeTemp(ast->down);
  
  		printf("mul $a0, $a0, $t1\n\n");
  
  		printf("addiu $sp, $sp, 4\n\n");
		
	}
	if (!strcmp(ast->type, "/")){
		storeReg(ast->next);
  		printf("addiu $sp, $sp, -4\n\n");

  		storeTemp(ast->down);;
  
  		printf("div $a0, $a0, $t1\n\n");
  
  		printf("addiu $sp, $sp, 4\n\n");
		
	}
	
	if (!strcmp(ast->type, "and")){
		storeReg(ast->down);
  		printf("addiu $sp, $sp, -4\n\n");

  		storeTemp(ast->next);;
  
  		printf("and $a0, $a0, $t1\n\n");
  
  		printf("addiu $sp, $sp, 4\n\n");
		
	}
	
	if (!strcmp(ast->type, "or")){
		storeReg(ast->down);
  		printf("addiu $sp, $sp, -4\n\n");

  		storeTemp(ast->next);;
  
  		printf("or $a0, $a0, $t1\n\n");
  
  		printf("addiu $sp, $sp, 4\n\n");
		
	}
}

void callComp(no* ast){
	
	if (!strcmp(ast->type, "==")){
		storeReg(ast->down);
  		printf("addiu $sp, $sp, -4\n\n");

  		storeTemp(ast->next);
		printf("beq $a0 $t1 label%d\n\n",labelNumber);
	}
	
	if (!strcmp(ast->type, ">")){
		storeReg(ast->down);
  		printf("addiu $sp, $sp, -4\n\n");

  		storeTemp(ast->next);
		printf("blt $a0 $t1 label%d\n\n",labelNumber);
	}
	
	if (!strcmp(ast->type, ">=")){
		storeReg(ast->down);
  		printf("addiu $sp, $sp, -4\n\n");

  		storeTemp(ast->next);
		printf("ble $a0 $t1 label%d\n\n",labelNumber);
	}

	if (!strcmp(ast->type, "<")){
		storeReg(ast->down);
  		printf("addiu $sp, $sp, -4\n\n");

  		storeTemp(ast->next);
		printf("bgt $a0 $t1 label%d\n\n",labelNumber);
	}

	if (!strcmp(ast->type, "<=")){
		storeReg(ast->down);
  		printf("addiu $sp, $sp, -4\n\n");

  		storeTemp(ast->next);
		printf("bge $a0 $t1 label%d\n\n",labelNumber);
	}

	if (!strcmp(ast->type, "~=")){
		storeReg(ast->down);
  		printf("addiu $sp, $sp, -4\n\n");

  		storeTemp(ast->next);
		printf("bne $a0 $t1 label%d\n\n",labelNumber);
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
		if (!strcmp((ast->next)->type, "number")){
			printf("li $a0 %d\n", (ast -> next)-> value);
			printf("sw $a0, %s\n\n",(ast->down) -> svalue);
			
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
				printf("lw $a0,%s\n",(ast -> next->down)-> svalue);
				callPrint();
			}
			else if (!strcmp((ast->next->down)->type, "number")){
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
		labelNumber++;
		printf("#inicio do if\n");		
		callComp(ast -> next);		
		printf("b label%d\n\n",labelNumber+1);
		//Check content of bloco
		printf("label%d: \n", labelNumber);
		printf("#inicio do bloco\n");
		codeGen((ast -> down));	
		printf("#fim do bloco e do if\n");
		printf("label%d: \n", labelNumber+1);
		labelNumber++;
	}	
	
	

	//while generation 
	if (!strcmp(ast->type, "while")){
		labelNumber++;
		printf("#inicio do while\n");		
		callComp(ast -> next);		
		printf("b label%d\n\n",labelNumber+1);
		//Check content of bloco
		printf("label%d: \n", labelNumber);
		printf("#inicio do bloco\n");
		codeGen((ast -> down));
		printf("#fim do bloco\n");
		callComp(ast -> next);
		printf("#Fim do while\n");	
		printf("label%d: \n", labelNumber+1);
		labelNumber++;
	}
	
}
