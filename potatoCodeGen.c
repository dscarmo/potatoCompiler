#include "ast.h"
#include "potatoCodeGen.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int variableNumber = 0;
int labelNumber = 0;
int whileLabel= 0;
FILE *output;

void initializeOutput(char *args){
	output = fopen(args, "w");
	if (output != NULL)
		printf ("\nArquivo de saída inicializado com sucesso.");
	else
	{
		printf ("Erro ao gerar arquivo de saída.");
		exit(-1);
	}
	
	fputs("#Arquivo de saida do potato Compiler\n", output);
}

void codeGenBegins (no *ast){
	fprintf(output, ".data\n");
	varGen(ast);
	fprintf(output, "\n\n");
	fprintf(output, ".text\n");
	fprintf(output, ".globl main\n\n");
	fprintf(output, "main:\n\n");
	codeGen(ast);
	fprintf(output, "li $v0, 10\n");  
  	fprintf(output, "syscall\n\n"); 
}

void codeGen(no *ast){
	
	if 	(ast == NULL){
		return;
	} else {
		
	
		generateCode(ast);
		
		codeGen(ast->down);
				
		codeGen(ast->next);
		
	}
}
int opCount=0;
void storeReg(no *ast){
	
	if(!strcmp(ast->type, "number")){
		fprintf(output, "li $a0, %d\n",(ast->value));
  		fprintf(output, "sw $a0, 0($sp)\n");
		fprintf(output, "addiu $sp, $sp, -4\n\n");
	}
	else if(!strcmp(ast->type, "id")){
		fprintf(output, "lw $a0, %s\n",(ast->svalue));
  		fprintf(output, "sw $a0, 0($sp)\n");
		fprintf(output, "addiu $sp, $sp, -4\n\n");
	}else {
		opCount++;
		callExpression(ast);
		}
}

void storeTemp(no *ast){
	
	if(!strcmp(ast->type, "number")){
		fprintf(output, "li $a0, %d\n",(ast->value));
  		fprintf(output, "lw $t1, 4($sp)\n");
	}
	else if(!strcmp(ast->type, "id")){
		fprintf(output, "lw $a0, %s\n",(ast->svalue));
  		fprintf(output, "lw $t1, 4($sp)\n\n");
	}else{	
		opCount++;
		callExpression(ast);
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
			fprintf(output, "%s: .word  0\n", (ast->down)->svalue);
		else{	
			if(!strcmp(ast->next->type, "+")){
				fprintf(output, "%s: .word  %d\n", (ast->down)->svalue,(ast->next->down)->value + (ast->next->next)->value);				
			}
			else if(!strcmp(ast->next->type, "-")){
				fprintf(output, "%s: .word  %d\n", (ast->down)->svalue,(ast->next->down)->value - (ast->next->next)->value);				
			}
			else if(!strcmp(ast->next->type, "*")){
				fprintf(output, "%s: .word  %d\n", (ast->down)->svalue,(ast->next->down)->value * (ast->next->next)->value);				
			}
			else if(!strcmp(ast->next->type, "/")){
				fprintf(output, "%s: .word  %d\n", (ast->down)->svalue,(ast->next->down)->value / (ast->next->next)->value);				
			}
			else if(!strcmp(ast->next->type, "and")){
				fprintf(output, "%s: .word  %d\n", (ast->down)->svalue,(ast->next->down)->value & (ast->next->next)->value);				
			}
			else if(!strcmp(ast->next->type, "or")){
				fprintf(output, "%s: .word  %d\n", (ast->down)->svalue,(ast->next->down)->value | (ast->next->next)->value);				
			}
			else fprintf(output, "%s: .word  %d\n", (ast->down)->svalue,(ast->next)->value);
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
		fprintf(output, " %s", (ast-> down)->svalue);
	else
		fprintf(output, " %d", (ast-> down)->value);
	
	fprintf(output, " %s", ast->type);
	
	if ((ast->next)->svalue != NULL)
		fprintf(output, " %s\n", (ast-> next)->svalue);
	else	
		fprintf(output, " %d\n", (ast-> down)->value);
}


void callExpression(no* ast){
	printf("%s\n\n",ast->type);
	if ((!strcmp(ast->type, "exppar"))){
		printf("%d\n\n\n",opCount);
		if (ast->down) callExpression(ast -> down);
		if (ast->next) callExpression(ast -> next);
		
	
	}	
	else{	
	
	if (!strcmp(ast->type, "+")){
		if(opCount==0){		
			storeReg(ast->down);		
  		
  			storeTemp(ast->next);
  			if (opCount==0){
				fprintf(output, "add $a0, $a0, $t1\n\n");
  
  				fprintf(output, "addiu $sp, $sp, 4\n\n");
				}
			}
		else{
			if(!strcmp(ast->down->type, "number")){			
				fprintf(output, "li $t1, %d\n",(ast->down->value));
  				fprintf(output, "add $a0, $a0, $t1\n\n");
				fprintf(output, "addiu $sp, $sp, 4\n\n");
				fprintf(output, "sw $a0, 0($sp)\n");
				fprintf(output, "addiu $sp, $sp, -4\n\n");
				}
			if(!strcmp(ast->down->type, "id")){
				fprintf(output, "lw $t1, %s\n",(ast->down->svalue));
  				fprintf(output, "add $a0, $a0, $t1\n\n");
				fprintf(output, "addiu $sp, $sp, 4\n\n");
				fprintf(output, "sw $a0, 0($sp)\n");
				fprintf(output, "addiu $sp, $sp, -4\n\n");
			}
			if(!strcmp(ast->next->type, "number")){
				fprintf(output, "li $t1, %d\n",(ast->next->value));
  				fprintf(output, "add $a0, $a0, $t1\n\n");
				fprintf(output, "addiu $sp, $sp, 4\n\n");
				fprintf(output, "sw $a0, 0($sp)\n");
				fprintf(output, "addiu $sp, $sp, -4\n\n");
			}
			if(!strcmp(ast->next->type, "id")){
				fprintf(output, "lw $t1, %s\n",(ast->next->svalue));
  				fprintf(output, "add $a0, $a0, $t1\n\n");
				fprintf(output, "addiu $sp, $sp, 4\n\n");
				fprintf(output, "sw $a0, 0($sp)\n");
				fprintf(output, "addiu $sp, $sp, -4\n\n");
			}
			if (ast->down) callExpression(ast->down);
  			if (ast->next) callExpression(ast->next);
			
  			//fprintf(output, "addiu $sp, $sp, 4\n\n");
			}
		}
			
	
	else if (!strcmp(ast->type, "-")){
		
		if (!ast->next){
			if(!strcmp(ast->down->type, "number")){		
				fprintf(output, "li $t1 %d\n",ast->down->value);		
				fprintf(output, "neg $a0 $t1\n\n");		
			}
			else if(!strcmp(ast->down->type, "id")){
				fprintf(output, "lw $t1 %s\n",ast->down->svalue);		
				fprintf(output, "neg $a0 $t1\n\n");
			}		
		}
		else{
			if(opCount==0){		
			storeReg(ast->down);		
  		
  			storeTemp(ast->next);
  			if (opCount==0){
				fprintf(output, "sub $a0, $t1, $a0\n\n");
  
  				fprintf(output, "addiu $sp, $sp, 4\n\n");
				}
			}
		else{
			if(!strcmp(ast->down->type, "number")){			
				fprintf(output, "li $t1, %d\n",(ast->down->value));
  				fprintf(output, "sub $a0, $a0, $t1\n\n");
				fprintf(output, "addiu $sp, $sp, 4\n\n");
				fprintf(output, "sw $a0, 0($sp)\n");
				fprintf(output, "addiu $sp, $sp, -4\n\n");
				}
			if(!strcmp(ast->down->type, "id")){
				fprintf(output, "lw $t1, %s\n",(ast->down->svalue));
  				fprintf(output, "sub $a0, $a0, $t1\n\n");
				fprintf(output, "addiu $sp, $sp, 4\n\n");
				fprintf(output, "sw $a0, 0($sp)\n");
				fprintf(output, "addiu $sp, $sp, -4\n\n");
			}
			if(!strcmp(ast->next->type, "number")){
				fprintf(output, "li $t1, %d\n",(ast->next->value));
  				fprintf(output, "sub $a0, $a0, $t1\n\n");
				fprintf(output, "addiu $sp, $sp, 4\n\n");
				fprintf(output, "sw $a0, 0($sp)\n");
				fprintf(output, "addiu $sp, $sp, -4\n\n");
			}
			if(!strcmp(ast->next->type, "id")){
				fprintf(output, "lw $t1, %s\n",(ast->next->svalue));
  				fprintf(output, "sub $a0, $a0, $t1\n\n");
				fprintf(output, "addiu $sp, $sp, 4\n\n");
				fprintf(output, "sw $a0, 0($sp)\n");
				fprintf(output, "addiu $sp, $sp, -4\n\n");
			}
			if (ast->down) callExpression(ast->down);  			
			if (ast->next) callExpression(ast->next);
			
  			//fprintf(output, "addiu $sp, $sp, 4\n\n");
			}		
		/*
		storeReg(ast->down);
  		
  		storeTemp(ast->next);
  
  		fprintf(output, "sub $a0, $t1, $a0\n\n");
  
  		fprintf(output, "addiu $sp, $sp, 4\n\n");
		*/
		}
		
	}
	else if (!strcmp(ast->type, "*")){
		
		if(opCount==0){		
			storeReg(ast->down);		
  		
  			storeTemp(ast->next);
  			if (opCount==0){
				fprintf(output, "mul $a0, $a0, $t1\n\n");
  
  				fprintf(output, "addiu $sp, $sp, 4\n\n");
				}
			}
		else{
			if(!strcmp(ast->down->type, "number")){			
				fprintf(output, "li $t1, %d\n",(ast->down->value));
  				fprintf(output, "mul $a0, $a0, $t1\n\n");
				fprintf(output, "addiu $sp, $sp, 4\n\n");
				fprintf(output, "sw $a0, 0($sp)\n");
				fprintf(output, "addiu $sp, $sp, -4\n\n");
				}
			if(!strcmp(ast->down->type, "id")){
				fprintf(output, "lw $t1, %s\n",(ast->down->svalue));
  				fprintf(output, "mul $a0, $a0, $t1\n\n");
				fprintf(output, "addiu $sp, $sp, 4\n\n");
				fprintf(output, "sw $a0, 0($sp)\n");
				fprintf(output, "addiu $sp, $sp, -4\n\n");
			}
			if(!strcmp(ast->next->type, "number")){
				fprintf(output, "li $t1, %d\n",(ast->next->value));
  				fprintf(output, "mul $a0, $a0, $t1\n\n");
				fprintf(output, "addiu $sp, $sp, 4\n\n");
				fprintf(output, "sw $a0, 0($sp)\n");
				fprintf(output, "addiu $sp, $sp, -4\n\n");
			}
			if(!strcmp(ast->next->type, "id")){
				fprintf(output, "lw $t1, %s\n",(ast->next->svalue));
  				fprintf(output, "mul $a0, $a0, $t1\n\n");
				fprintf(output, "addiu $sp, $sp, 4\n\n");
				fprintf(output, "sw $a0, 0($sp)\n");
				fprintf(output, "addiu $sp, $sp, -4\n\n");
			}
			if (ast->down) callExpression(ast->down);
  			if (ast->next) callExpression(ast->next);
			
  			//fprintf(output, "addiu $sp, $sp, 4\n\n");
			}		
		/*		
		storeReg(ast->down);
  		

  		storeTemp(ast->next);
  
  		fprintf(output, "mul $a0, $a0, $t1\n\n");
  
  		fprintf(output, "addiu $sp, $sp, 4\n\n");
		*/
		
	}
	else if (!strcmp(ast->type, "/")){
		if(opCount==0){		
			storeReg(ast->down);		
  		
  			storeTemp(ast->next);
  			if (opCount==0){
				fprintf(output, "div $a0, $a0, $t1\n\n");
  
  				fprintf(output, "addiu $sp, $sp, 4\n\n");
				}
			}
		else{
			if(!strcmp(ast->down->type, "number")){			
				fprintf(output, "li $t1, %d\n",(ast->down->value));
  				fprintf(output, "div $a0, $a0, $t1\n\n");
				fprintf(output, "addiu $sp, $sp, 4\n\n");
				fprintf(output, "sw $a0, 0($sp)\n");
				fprintf(output, "addiu $sp, $sp, -4\n\n");
				}
			if(!strcmp(ast->down->type, "id")){
				fprintf(output, "lw $t1, %s\n",(ast->down->svalue));
  				fprintf(output, "div $a0, $a0, $t1\n\n");
				fprintf(output, "addiu $sp, $sp, 4\n\n");
				fprintf(output, "sw $a0, 0($sp)\n");
				fprintf(output, "addiu $sp, $sp, -4\n\n");
			}
			if(!strcmp(ast->next->type, "number")){
				fprintf(output, "li $t1, %d\n",(ast->next->value));
  				fprintf(output, "div $a0, $a0, $t1\n\n");
				fprintf(output, "addiu $sp, $sp, 4\n\n");
				fprintf(output, "sw $a0, 0($sp)\n");
				fprintf(output, "addiu $sp, $sp, -4\n\n");
			}
			if(!strcmp(ast->next->type, "id")){
				fprintf(output, "lw $t1, %s\n",(ast->next->svalue));
  				fprintf(output, "div $a0, $a0, $t1\n\n");
				fprintf(output, "addiu $sp, $sp, 4\n\n");
				fprintf(output, "sw $a0, 0($sp)\n");
				fprintf(output, "addiu $sp, $sp, -4\n\n");
			}
			if (ast->down) callExpression(ast->down);
  			if (ast->next) callExpression(ast->next);
			
  			//fprintf(output, "addiu $sp, $sp, 4\n\n");
			}		
		/*		
		storeReg(ast->down);
  		

  		storeTemp(ast->next);;
  
  		fprintf(output, "div $a0, $t1, $a0\n\n");
  
  		fprintf(output, "addiu $sp, $sp, 4\n\n");
		*/
		
	}
	
	else if (!strcmp(ast->type, "and")){
		storeReg(ast->down);
  		

  		storeTemp(ast->next);;
  
  		fprintf(output, "and $a0, $a0, $t1\n\n");
  
  		fprintf(output, "addiu $sp, $sp, 4\n\n");
		
	}
	
	else if (!strcmp(ast->type, "or")){
		storeReg(ast->down);
  		

  		storeTemp(ast->next);;
  
  		fprintf(output, "or $a0, $a0, $t1\n\n");
  
  		fprintf(output, "addiu $sp, $sp, 4\n\n");
		
	}

	else if (!strcmp(ast->type, "not")){
		if (!ast->next){
			if(!strcmp(ast->down->type, "number")){		
				fprintf(output, "li $t1 %d\n",ast->down->value);		
				fprintf(output, "not $a0 $t1\n\n");		
			}
			else if(!strcmp(ast->down->type, "id")){
				fprintf(output, "lw $t1 %s\n",ast->down->svalue);		
				fprintf(output, "not $a0 $t1\n\n");
			}				
		
		}
	}
}
}

void callComp(no* ast,int returnLabel){
	if ((!strcmp(ast->type, "exppar"))){
		callComp(ast -> down,returnLabel);
	
	}else	{
	if (!strcmp(ast->type, "==")){
		storeReg(ast->down);
  		

  		storeTemp(ast->next);
		fprintf(output, "beq $a0 $t1 label%d\n\n",returnLabel);
	}
	
	if (!strcmp(ast->type, ">")){
		storeReg(ast->down);
  		

  		storeTemp(ast->next);
		fprintf(output, "blt $a0 $t1 label%d\n\n",returnLabel);
	}
	
	if (!strcmp(ast->type, ">=")){
		storeReg(ast->down);
  		

  		storeTemp(ast->next);
		fprintf(output, "ble $a0 $t1 label%d\n\n",returnLabel);
	}

	if (!strcmp(ast->type, "<")){
		storeReg(ast->down);
  		

  		storeTemp(ast->next);
		fprintf(output, "bgt $a0 $t1 label%d\n\n",returnLabel);
	}

	if (!strcmp(ast->type, "<=")){
		storeReg(ast->down);
  		
  		storeTemp(ast->next);
		fprintf(output, "bge $a0 $t1 label%d\n\n",returnLabel);
	}

	if (!strcmp(ast->type, "~=")){
		storeReg(ast->down);
  		

  		storeTemp(ast->next);
		fprintf(output, "bne $a0 $t1 label%d\n\n",returnLabel);
	}
	
}
}

void callWhileComp(no* ast,int returnLabel){
if ((!strcmp(ast->type, "exppar"))){
	callWhileComp(ast -> down,returnLabel);
	
}else	{	
	if (!strcmp(ast->type, "==")){
		storeReg(ast->down);
  		

  		storeTemp(ast->next);
		fprintf(output, "beq $a0 $t1 wlabel%d\n\n",returnLabel);
	}
	
	if (!strcmp(ast->type, ">")){
		storeReg(ast->down);
  		

  		storeTemp(ast->next);
		fprintf(output, "blt $a0 $t1 wlabel%d\n\n",returnLabel);
	}
	
	if (!strcmp(ast->type, ">=")){
		storeReg(ast->down);
  		

  		storeTemp(ast->next);
		fprintf(output, "ble $a0 $t1 wlabel%d\n\n",returnLabel);
	}

	if (!strcmp(ast->type, "<")){
		storeReg(ast->down);
  		

  		storeTemp(ast->next);
		fprintf(output, "bgt $a0 $t1 wlabel%d\n\n",returnLabel);
	}

	if (!strcmp(ast->type, "<=")){
		storeReg(ast->down);
  		

  		storeTemp(ast->next);
		fprintf(output, "bge $a0 $t1 wlabel%d\n\n",returnLabel);
	}

	if (!strcmp(ast->type, "~=")){
		storeReg(ast->down);
  		

  		storeTemp(ast->next);
		fprintf(output, "bne $a0 $t1 wlabel%d\n\n",returnLabel);
	}
}
}

void callPrint(){
	fprintf(output, "li $v0, 1\n");
  	fprintf(output, "syscall\n\n");
}

int isWhile=0;
int isIf=0;
int ifCount=0;
int whileCount=0;

void generateCode (no *ast){
	no *dummy = NULL;
	
	//Assign
	if (!strcmp(ast->type, "assign")){
		if (isIf == 1){
			ifCount++;
		}if (isWhile==1){
			whileCount++;
		}if ((isWhile==0 && whileCount > 0) && (isIf==0 && ifCount > 0)){
			whileCount--;
			ifCount--;
		}else if (isWhile==0 && whileCount > 0){
			whileCount--;
		}else if (isIf==0 && ifCount > 0){
			ifCount--;
		}else{	
		variableNumber++;
		if (!strcmp((ast->next)->type, "number")){
			fprintf(output, "li $a0 %d\n", (ast -> next)-> value);
			fprintf(output, "sw $a0, %s\n\n",(ast->down) -> svalue);
			opCount=0;
			
		}
		else if (!strcmp((ast->next)->type, "id")){
			fprintf(output, "lw $a0, %s\n",(ast -> next)-> svalue) ; 
			fprintf(output, "sw $a0, %s\n\n",(ast->down) -> svalue);
			opCount=0;			
			//fprintf(output, " %s\n", (ast -> next)-> svalue);
		}
		else{	
			callExpression(ast -> next);
			fprintf(output, "sw $a0, %s\n\n",(ast->down) -> svalue);
			opCount=0;
			//fprintf(output, "lw $a0, %s\n\n",(ast->down) -> svalue);
		 	//getExpression(ast->next);
			}
		}	
	}
	
	//Print generation
	if (!strcmp(ast->type, "chamada de funcao")){
		if (isIf == 1){
			ifCount++;
		}if (isWhile==1){
			whileCount++;
		}if ((isWhile==0 && whileCount > 0) && (isIf==0 && ifCount > 0)){
			whileCount--;
			ifCount--;
		}else if (isWhile==0 && whileCount > 0){
			whileCount--;
		
		}else if (isIf==0 && ifCount > 0){
			ifCount--;
		}else{	
		if (!strcmp((ast->down)->svalue, "print")){
			if (!strcmp((ast->next->down)->type, "id")){
				fprintf(output, "lw $a0,%s\n",(ast -> next->down)-> svalue);
				callPrint();
			}
			else if (!strcmp((ast->next->down)->type, "number")){
				fprintf(output, "li $a0, %d\n",(ast -> next->down)-> value);
  				fprintf(output, "sw $a0, 0($sp)\n\n");
				callPrint();
			}
			else{
				callExpression(ast -> next ->down);
				callPrint();
				opCount=0;
			}
		}

	}
	}
	
	//If generation 
	if (!strcmp(ast->type, "if")){
		if (isIf == 1){
			ifCount++;
		}if (isWhile==1){
			whileCount++;
		}if ((isWhile==0 && whileCount > 0) && (isIf==0 && ifCount > 0)){
			whileCount--;
			ifCount--;
		}else if (isWhile==0 && whileCount > 0){
			whileCount--;
		}else if (isIf==0 && ifCount > 0){
			ifCount--;
		}else{			
		int endLabelif;		
		labelNumber++;
		endLabelif=labelNumber;
		isIf=1;
		fprintf(output, "#inicio do if\n");		
		callComp(ast -> next,endLabelif);
		opCount==0;		
		fprintf(output, "b Endlabel%d\n\n",endLabelif);
		//Check content of bloco
		fprintf(output, "label%d: \n", labelNumber);
		fprintf(output, "#inicio do bloco\n");
		codeGen((ast -> down));	
		fprintf(output, "#fim do bloco e do if\n");
		fprintf(output, "Endlabel%d: \n",endLabelif);
		if (isWhile==1) 
			whileCount=whileCount - ifCount;
		isIf=0;
		labelNumber++;
		}
	}
	
	//while generation 
	if (!strcmp(ast->type, "while")){
		if (isIf == 1){
			ifCount++;
		}if (isWhile==1){
			whileCount++;
		}if ((isWhile==0 && whileCount > 0) && (isIf==0 && ifCount > 0)){
			whileCount--;
			ifCount--;
		}if (isWhile==0 && whileCount > 0){
			whileCount--;
		}else if (isIf==0 && ifCount > 0){
			ifCount--;
		}else{			
		int endLabel;		
		whileLabel++;
		endLabel=whileLabel;
		isWhile=1;
		fprintf(output, "#inicio do while\n");		
		callWhileComp(ast -> next,endLabel);
		opCount==0;		
		fprintf(output, "b wEndlabel%d\n\n",endLabel);
		//Check content of bloco
		fprintf(output, "wlabel%d: \n", whileLabel);
		fprintf(output, "#inicio do bloco\n");
		codeGen((ast -> down));
		fprintf(output, "#fim do bloco\n");
		callWhileComp(ast -> next,endLabel);
		fprintf(output, "#Fim do while\n");	
		fprintf(output, "wEndlabel%d: \n", endLabel);
		if (isIf==1) ifCount=ifCount-whileCount;
		isWhile=0;
		whileLabel++;
		}
	}
	
}
