#include "ast.h"
#include "potatoCodeGen.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int variableNumber = 0;
int labelNumber = 0;
int whileLabel=0;

void codeGen(no *ast){
	
	if 	(ast == NULL){
		return;
	} else {
		
	
		generateCode(ast);
		
		codeGen(ast->down);
				
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
		
		if (!ast->next){
			if(!strcmp(ast->down->type, "number")){		
				printf("li $t1 %d\n",ast->down->value);		
				printf("neg $a0 $t1\n\n");		
			}
			else if(!strcmp(ast->down->type, "id")){
				printf("lw $t1 %s\n",ast->down->svalue);		
				printf("neg $a0 $t1\n\n");
			}		
		}
		else{		
		
		storeReg(ast->next);
  		printf("addiu $sp, $sp, -4\n\n");

  		storeTemp(ast->down);
  
  		printf("sub $a0, $a0, $t1\n\n");
  
  		printf("addiu $sp, $sp, 4\n\n");
		}
		
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

	if (!strcmp(ast->type, "not")){
		if (!ast->next){
			if(!strcmp(ast->down->type, "number")){		
				printf("li $t1 %d\n",ast->down->value);		
				printf("not $a0 $t1\n\n");		
			}
			else if(!strcmp(ast->down->type, "id")){
				printf("lw $t1 %s\n",ast->down->svalue);		
				printf("not $a0 $t1\n\n");
			}				
		
		}
	}
}

void callComp(no* ast,int returnLabel){
	
	if (!strcmp(ast->type, "==")){
		storeReg(ast->down);
  		printf("addiu $sp, $sp, -4\n\n");

  		storeTemp(ast->next);
		printf("beq $a0 $t1 label%d\n\n",returnLabel);
	}
	
	if (!strcmp(ast->type, ">")){
		storeReg(ast->down);
  		printf("addiu $sp, $sp, -4\n\n");

  		storeTemp(ast->next);
		printf("blt $a0 $t1 label%d\n\n",returnLabel);
	}
	
	if (!strcmp(ast->type, ">=")){
		storeReg(ast->down);
  		printf("addiu $sp, $sp, -4\n\n");

  		storeTemp(ast->next);
		printf("ble $a0 $t1 label%d\n\n",returnLabel);
	}

	if (!strcmp(ast->type, "<")){
		storeReg(ast->down);
  		printf("addiu $sp, $sp, -4\n\n");

  		storeTemp(ast->next);
		printf("bgt $a0 $t1 label%d\n\n",returnLabel);
	}

	if (!strcmp(ast->type, "<=")){
		storeReg(ast->down);
  		printf("addiu $sp, $sp, -4\n\n");

  		storeTemp(ast->next);
		printf("bge $a0 $t1 label%d\n\n",returnLabel);
	}

	if (!strcmp(ast->type, "~=")){
		storeReg(ast->down);
  		printf("addiu $sp, $sp, -4\n\n");

  		storeTemp(ast->next);
		printf("bne $a0 $t1 label%d\n\n",returnLabel);
	}
}

void callWhileComp(no* ast,int returnLabel){
	
	if (!strcmp(ast->type, "==")){
		storeReg(ast->down);
  		printf("addiu $sp, $sp, -4\n\n");

  		storeTemp(ast->next);
		printf("beq $a0 $t1 wlabel%d\n\n",returnLabel);
	}
	
	if (!strcmp(ast->type, ">")){
		storeReg(ast->down);
  		printf("addiu $sp, $sp, -4\n\n");

  		storeTemp(ast->next);
		printf("blt $a0 $t1 wlabel%d\n\n",returnLabel);
	}
	
	if (!strcmp(ast->type, ">=")){
		storeReg(ast->down);
  		printf("addiu $sp, $sp, -4\n\n");

  		storeTemp(ast->next);
		printf("ble $a0 $t1 wlabel%d\n\n",returnLabel);
	}

	if (!strcmp(ast->type, "<")){
		storeReg(ast->down);
  		printf("addiu $sp, $sp, -4\n\n");

  		storeTemp(ast->next);
		printf("bgt $a0 $t1 wlabel%d\n\n",returnLabel);
	}

	if (!strcmp(ast->type, "<=")){
		storeReg(ast->down);
  		printf("addiu $sp, $sp, -4\n\n");

  		storeTemp(ast->next);
		printf("bge $a0 $t1 wlabel%d\n\n",returnLabel);
	}

	if (!strcmp(ast->type, "~=")){
		storeReg(ast->down);
  		printf("addiu $sp, $sp, -4\n\n");

  		storeTemp(ast->next);
		printf("bne $a0 $t1 wlabel%d\n\n",returnLabel);
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
			//printf("lw $a0, %s\n\n",(ast->down) -> svalue);
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
		int endLabelif;		
		labelNumber++;
		endLabelif=labelNumber;
		printf("#inicio do if\n");		
		callComp(ast -> next,endLabelif);		
		printf("b Endlabel%d\n\n",endLabelif);
		//Check content of bloco
		printf("label%d: \n", labelNumber);
		printf("#inicio do bloco\n");
		codeGen((ast -> down));	
		printf("#fim do bloco e do if\n");
		printf("Endlabel%d: \n",endLabelif);
		labelNumber++;
	}		

	

	//while generation 
	if (!strcmp(ast->type, "while")){
		int endLabel;		
		whileLabel++;
		endLabel=whileLabel;
		printf("#inicio do while\n");		
		callWhileComp(ast -> next,endLabel);		
		printf("b wEndlabel%d\n\n",endLabel);
		//Check content of bloco
		printf("wlabel%d: \n", whileLabel);
		printf("#inicio do bloco\n");
		codeGen((ast -> down));
		printf("#fim do bloco\n");
		callWhileComp(ast -> next,endLabel);
		printf("#Fim do while\n");	
		printf("wEndlabel%d: \n", endLabel);
		whileLabel++;
	}
	
}
