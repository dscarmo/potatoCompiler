%{
#include <cstdio>
#include <iostream>
#include "ast.h"
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
	
	//float fval;
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

%type <ast> bloco 
%type <ast> comando 
%type <ast> exp
%type <ast> nomedafuncao 
%type <ast> corpodafuncao
%type <ast> chamadadefuncao
%type <ast> args
%type <ast> listaexp
%type <ast> listapares
%type <sval> opbin

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
	TOKEN_ID TOKEN_ASSIGN exp {printf("assignemt para comando\n"); $$ = createNode("assign", createId($1), $3);}
	| TOKEN_IF exp TOKEN_THEN bloco elseif else TOKEN_END {printf("if exp bloco comando\n"); $$ = createNode("if", $4, $2);}
	| TOKEN_WHILE exp TOKEN_DO bloco TOKEN_END {$$ = createNode("while", $4, $2);}
	| TOKEN_FOR TOKEN_ID TOKEN_ASSIGN exp TOKEN_COLON exp colonexp TOKEN_DO bloco TOKEN_END {$$ = createNode("for", $9, $4);}
	| TOKEN_FUNCTION nomedafuncao corpodafuncao {$$ = createNode("function", $3, $2);}
	| chamadadefuncao {$$ = createNode("chamadadefuncao", $1, NULL);}
	;
elseif:
	| TOKEN_ELSEIF exp TOKEN_THEN bloco elseif
	;
else:
	| TOKEN_ELSE bloco
	;
colonexp:
	| TOKEN_COLON exp
	;
//

//MY FUCKING FUNCTION CALL
chamadadefuncao:
	TOKEN_ID TOKEN_LPAREN args TOKEN_RPAREN {printf("args para chamadadefuncao"); $$ = createNode("chamadadefuncao", createId($1), $3);}
	;
args: {}
	| listaexp  {$$ = createNode("expargs", $1, NULL);}
	| TOKEN_STRING {$$ = createString($1);}
	;

listaexp: {}
	| exp {$$ = createNode("umaexp", $1, NULL);}
	| exp TOKEN_COLON listaexp {$$ = createNode("variasexp", $1, $3);}
	;



//Nome da função
nomedafuncao:
	TOKEN_ID pointidrec twopointid{$$ = createNode("nomedafuncao", createId($1), NULL);}
	;
pointidrec:
	| TOKEN_POINT TOKEN_ID pointidrec
	;
twopointid:
	| TOKEN_TWOPOINTS TOKEN_ID
	;
	
//Corpo da Função
corpodafuncao:
	TOKEN_LPAREN listapares TOKEN_RPAREN bloco TOKEN_END {$$ = createNode("corpodafuncao", $4, $2);}
	;
listapares: {$$ = createNode("semargs", NULL, NULL);}
	| listapar {$$ = createNode("listadeargs", NULL, NULL);}
	;		
listapar:
	listadenomes colonetc {}
	| TOKEN_ETC
	;
colonetc:
	| TOKEN_COLON TOKEN_ETC
	;
listadenomes:
	TOKEN_ID colonidrec {}
	;
colonidrec:
	| TOKEN_COLON TOKEN_ID colonidrec
	;
//

//Expressoes e simbolos
exp: 
	TOKEN_NIL {$$ = createNode("null", NULL, NULL);}
	| TOKEN_FALSE {$$ = createNode("false", NULL, NULL);}
	| TOKEN_TRUE {$$ = createNode("true", NULL, NULL);}
	| TOKEN_NUMBER {$$ = createNumber($1);}
	| TOKEN_STRING {$$ = createString($1);}
	| TOKEN_ETC {$$ = createNode("etc", NULL, NULL);}
	| TOKEN_ID {$$ = createString($1);}
	| exp opbin exp {printf("operacao para exp\n"); $$ = createNode($2, $1, $3);}
	;	

opbin:
	TOKEN_PLUS {$$ = "+";}
	| TOKEN_MINUS {$$ = "-";} 
	| TOKEN_MULTIPLY {$$ = "*";}
	| TOKEN_DIV {$$ = "/";}
	| TOKEN_HAT {$$ = "^";}
	| TOKEN_MOD {$$ = "%";}
	| TOKEN_DOUBLEPOINT {$$ = "..";}
	| TOKEN_LESSER {$$ = "<";}
	| TOKEN_LEQUAL {$$ = "<=";}
	| TOKEN_GREATER {$$ = ">";}
	| TOKEN_GEQUAL {$$ = ">=";}
	| TOKEN_EQUAL {printf("equal no opbin!\n"); $$ = "==";}
	| TOKEN_NEQUAL {$$ = "<=";}
	| TOKEN_AND {$$ = "and";}
	| TOKEN_OR {$$ = "or";}
	;
//	

%%
//Functions
/*void astTest(){
	no *filho1 = createNode("filho", NULL, NULL);
	no *brother1 = createNode("brother", NULL, NULL);
	no *initial = createNode("initial", filho1, brother1);
	printf("criou os nos");
	printAst(initial);
}*/


int main(int, char**) {
	
	
	// usar arquivo como entrada
	FILE *myfile = fopen("in.potato", "r");
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
	
	printf("Testando AST... \n");
	printAst(ast);
	printf("\n");
	//printf("Testando print da net");
	//printPaths (ast);
	//Horrivel! Deixa pa la. 
}

void yyerror(const char *s) {
	cout << "NOOOO! parse error na linha " << line_num << "  Message: " << s << endl;
	// might as well halt now:
	exit(-1);
}

