%{
#include <cstdio>
#include <iostream>
#include "ast.h"
#include "potatoCodeGen.h"

using namespace std;

// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
extern int line_num;
no *ast;
void yyerror(const char *s);
%}

%union {
	int ival;
	const char *sval;
	no *ast;
}

//Keywords
%token TOKEN_AND
%token TOKEN_BREAK
%token TOKEN_DO
%token TOKEN_ELSE
%token TOKEN_ELSEIF
%token TOKEN_END
%token TOKEN_FALSE
%token TOKEN_FOR
%token TOKEN_FUNCTION
%token TOKEN_IF
%token TOKEN_IN
%token TOKEN_LOCAL
%token TOKEN_NIL
%token TOKEN_NOT
%token TOKEN_OR
%token TOKEN_REPEAT
%token TOKEN_RETURN
%token TOKEN_THEN
%token TOKEN_TRUE
%token TOKEN_UNTIL
%token TOKEN_WHILE
%token TOKEN_VAR

//Valued Terminals
%token <sval> TOKEN_STRING
%token <ival> TOKEN_NUMBER
%token <sval> TOKEN_ID

//Operator/pontuation Terminals
%token TOKEN_LPAREN
%token TOKEN_RPAREN
%token TOKEN_PLUS
%token TOKEN_MULTIPLY
%token TOKEN_MINUS
%token TOKEN_DIV
%token TOKEN_MOD
%token TOKEN_HAT
%token TOKEN_CROSS
%token TOKEN_EQUAL
%token TOKEN_AEQUAL
%token TOKEN_NEQUAL
%token TOKEN_LEQUAL
%token TOKEN_GEQUAL
%token TOKEN_LESSER
%token TOKEN_GREATER
%token TOKEN_ASSIGN
%token TOKEN_LKEY
%token TOKEN_RKEY
%token TOKEN_LBOX
%token TOKEN_RBOX
%token TOKEN_SEMICOLON
%token TOKEN_TWOPOINTS
%token TOKEN_COLON
%token TOKEN_POINT
%token TOKEN_DOUBLEPOINT
%token TOKEN_ETC
%start Input

%type <ast>else
%type <ast>declaracaodevar
%type <ast> bloco 
%type <ast> comando 
%type <ast> exp
//%type <ast> chamadadefuncao
%type <ast> listaexp
%type <sval> opbin
%type <sval> opunaria
%%

///*//Debug Area
//prototype: createNode (char *type, no *down, no *next);
Input:
	bloco {printf("programa finalizado \n"); ast = $1;}
	;

bloco:
	comando {printf("bloco de um comando encontrado \n"); $$ = createNode("bloco", $1, NULL);} 
	| comando bloco {printf("varios comandos encontrados \n"); $$ = createNode("bloco", $1, $2); } 
	;

//Comandos principais e coisas auxiliares
comando:
	declaracaodevar;
	| TOKEN_ID TOKEN_ASSIGN exp {printf("assignemt de id para comando %s\n", $1); $$ = createNode("assign", createId($1), $3);if(checkVar($1)==0) yyerror("Variavel nao declarada");}
	| TOKEN_IF exp TOKEN_THEN bloco else TOKEN_END {printf("if exp bloco comando\n"); $$ = createNode("if", $4, $2);}
	| TOKEN_WHILE exp TOKEN_DO bloco TOKEN_END {$$ = createNode("while", $4, $2);}
	| TOKEN_ID TOKEN_LPAREN listaexp TOKEN_RPAREN {printf("funcao ID \n"); $$ = createNode("chamada de funcao", createId($1), $3);}
	;
else:
	|TOKEN_ELSE bloco{printf("bloco else\n"); $$ = createNode("else",NULL , $2);}
	;
declaracaodevar:
	TOKEN_VAR TOKEN_ID{printf("criacao de variavel %s\n", $2); $$ = createNode("criavar", createId($2), NULL);addLista($2);}
	|TOKEN_VAR TOKEN_ID TOKEN_ASSIGN exp{printf("criacao de variavel com valor inicial %s\n", $2);addLista($2); $$ = createNode("criavar", createId($2), $4);}
	;

//	


listaexp: {}
	| exp {$$ = createNode("umaexp", $1, NULL);}
	| exp TOKEN_COLON listaexp {$$ = createNode("variasexp", $1, $3);}
	;


//Expressoes e simbolos
exp: 
	  TOKEN_NUMBER {$$ = createNumber($1);}
	| TOKEN_ID {$$ = createId($1);if(checkVar($1)==0) yyerror("Variavel nao declarada");}
	| exp opbin exp {printf("operacao %s para exp\n", $2); $$ = createNode($2, $1, $3);}
	| opunaria exp {printf("operacao opunaria\n"); $$ = createNode($1, $2, NULL);}
	;	
//$$ = createId($1);if(checkVar($1)==0) yyerror("Variavel nao declarada")
opbin:
	TOKEN_PLUS {$$ = "+";}
	| TOKEN_MINUS {$$ = "-";} 
	| TOKEN_MULTIPLY {$$ = "*";}
	| TOKEN_DIV {$$ = "/";}
	| TOKEN_LESSER {$$ = "<";}
	| TOKEN_LEQUAL {$$ = "<=";}
	| TOKEN_GREATER {$$ = ">";}
	| TOKEN_GEQUAL {$$ = ">=";}
	| TOKEN_EQUAL {printf("equal no opbin!\n"); $$ = "==";}
	| TOKEN_AEQUAL {$$ = "~=";}
	| TOKEN_AND {$$ = "and";}
	| TOKEN_OR {$$ = "or";}
	;
//

opunaria:	
	TOKEN_MINUS {$$ = "-";}
	|TOKEN_NOT {$$ = "not";} 

%%


void separatingPhases(const char* string){
	cout << "\n\n\n /////////////////////////////\n" << "Executando fase de " << string << "\n////////////////////////////////\n\n\n";
}

int main(int argc, char * argv[]) {
	if (argc != 3){
		cout << "\nArgumentos incorretos. Como usar: ./potatoParser arquivo_entrada arquivo_saida\n" << endl;
		exit(-1);
	}
	
	//Inicializa arquivo de saida
	initializeOutput(argv[2]);
	
	//Cria lista para variaveis na geracao de código
	criaLista();
	
	//Começa 
	separatingPhases("Parser e Léxico");
		
	// usar arquivo como entrada
	FILE *myfile = fopen(argv[1], "r");
	if (!myfile) {
		cout << "Cade o .potato file D:" << endl;
		return -1;
	}
	
	// yyin = arquivo
	yyin = myfile;

	// parse
	do {
		yyparse();
	} while (!feof(yyin));
	
	
	separatingPhases("Representação Intermediária - Absctract Syntax Tree (notação posfixa):");
	printAst(ast);
	printf("\n");
	
	separatingPhases("Geraçao do  MIPS");
	
	codeGenBegins(ast);
	
	printf("Sucesso! Código MIPs gravado no arquivo de saida especificado!\n digite \"cat %s\" no terminal para abrir o código.\n\n", argv[2]);
}


void yyerror(const char *s) {
	cout << "NOOOO! parse error na linha " << line_num << "  Message: " << s << endl;
	exit(-1);
}



