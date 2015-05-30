%{
#include <cstdio>
#include <iostream>
using namespace std;

// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
extern int line_num;
 
void yyerror(const char *s);
%}

%union {
	int ival;
	char *sval;
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
%token TOKEN_ID

//Valued Terminals
%token <sval> TOKEN_STRING
%token <ival> TOKEN_NUMBER

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
%token ENDL

%%
//Grammar

//input:
	//trecho {}
	//;

trecho:
	comandokey ultimocomandobox {}
	;
comandokey: 	    
	|
	comando semicolonbox comandokey  
	;
ultimocomandobox:
	|
	ultimocomando semicolonbox
	;
semicolonbox:
	|
	TOKEN_SEMICOLON
	;

bloco:
	trecho {}
	;
	
comando:
	listavar TOKEN_ASSIGN listaexp {}
	| chamadadefuncao {}
	| TOKEN_WHILE exp TOKEN_DO bloco TOKEN_END {}
	| TOKEN_IF exp TOKEN_THEN bloco elseifkey elsebox TOKEN_END {printf("Reduziu um IF");}
	| TOKEN_FOR TOKEN_ID TOKEN_ASSIGN exp TOKEN_COLON exp colonexpbox TOKEN_DO bloco TOKEN_END {}
	| TOKEN_FUNCTION nomedafuncao corpodafuncao {}
	;
elseifkey:
	| TOKEN_ELSEIF exp TOKEN_THEN bloco elseifkey
	;
elsebox:
	| TOKEN_ELSE bloco
	;
colonexpbox:
	|
	TOKEN_COLON exp
	;


ultimocomando:
	TOKEN_RETURN listaexpbox {} 
	| TOKEN_BREAK {}
	;	
listaexpbox:
	| listaexp
	;

		
nomedafuncao:
	TOKEN_ID pointidkey twopointidbox{}
	;
pointidkey:
	| TOKEN_POINT TOKEN_ID pointidkey
	;
twopointidbox:
	| TOKEN_TWOPOINTS TOKEN_ID
	;
	
listavar:
	var colonvarkey {}
	;
colonvarkey:
	| TOKEN_COLON var colonvarkey

var:
	TOKEN_ID {}
	| expprefixo TOKEN_LBOX exp TOKEN_RBOX {}
	| expprefixo TOKEN_POINT TOKEN_ID {}
	|
	;
	
listadenomes:
	TOKEN_ID colonidkey {}
	;
colonidkey:
	| TOKEN_COLON TOKEN_ID colonidkey
	;


listaexp:
	expcolonkey exp {}
	;
expcolonkey:
	| exp TOKEN_COLON expcolonkey
	;
	
exp: 
	TOKEN_NIL {}
	| TOKEN_FALSE {}
	| TOKEN_TRUE {}
	| TOKEN_NUMBER {}
	| TOKEN_STRING {}
	| TOKEN_ETC {}
	| funcao {}
	| expprefixo {}
	| exp opbin exp {}
	| opunaria exp {}
	;
	
expprefixo:
	var {}
	| chamadadefuncao {}
	| TOKEN_LPAREN exp TOKEN_RPAREN {}
	;

chamadadefuncao:
	expprefixo args {}
	| expprefixo TOKEN_TWOPOINTS TOKEN_ID args {}
	;
	
args: 
	TOKEN_LPAREN listaexpbox TOKEN_RPAREN {}
	| TOKEN_STRING {}
	;
	
funcao:
	TOKEN_FUNCTION corpodafuncao {}
	;
	
corpodafuncao:
	TOKEN_LPAREN listaparbox TOKEN_RPAREN bloco TOKEN_END {}
	;
listaparbox:
	| listapar
	;

listapar:
	listadenomes colonetcbox {}
	| TOKEN_ETC
	;
colonetcbox:
	| TOKEN_COLON TOKEN_ETC
	;


	
opbin:
	TOKEN_PLUS {}
	| TOKEN_MINUS {} 
	| TOKEN_MULTIPLY {}
	| TOKEN_DIV {}
	| TOKEN_HAT {}
	| TOKEN_MOD {}
	| TOKEN_DOUBLEPOINT {}
	| TOKEN_LESSER {}
	| TOKEN_LEQUAL {}
	| TOKEN_GREATER {}
	| TOKEN_GEQUAL {}
	| TOKEN_EQUAL {}
	| TOKEN_NEQUAL {}
	| TOKEN_AND {}
	| TOKEN_OR {}
	;
	
opunaria:
	TOKEN_MINUS {}
	| TOKEN_NOT {}
	| TOKEN_CROSS {}
	;

%%
//Functions

int main(int, char**) {
	// open a file handle to a particular file:
	FILE *myfile = fopen("in.potato", "r");
	// make sure it's valid:
	if (!myfile) {
		cout << "I can't open a .potato file!" << endl;
		return -1;
	}
	// set flex to read from it instead of defaulting to STDIN:
	yyin = myfile;

	// parse through the input until there is no more:
	do {
		yyparse();
	} while (!feof(yyin));
	
}

void yyerror(const char *s) {
	cout << "NOOOOOOoooo!1 parse error on line" << line_num << "  Message: " << s << endl;
	// might as well halt now:
	exit(-1);
}


