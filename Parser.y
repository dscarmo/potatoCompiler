%{
 
/*
 * Parser.y file
 * To generate the parser run: "bison Parser.y"
 */
 
#include "Expression.h"
#include "Parser.h"
#include "Lexer.h"
 
int yyerror(SExpression **expression, yyscan_t scanner, const char *msg) {
    // Add error handling routine as needed
}
 
%}
 
%code requires {
 
#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void* yyscan_t;
#endif
 
}
 
%output  "Parser.c"
%defines "Parser.h"
 
%define api.pure
%lex-param   { yyscan_t scanner }
%parse-param { SExpression **expression }
%parse-param { yyscan_t scanner }
 
%union {
    int value;
    SExpression *expression;
}
 
%left '+' TOKEN_PLUS
%left '*' TOKEN_MULTIPLY
 
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

%token TOKEN_COMMENT
%token TOKEN_STRING

%token TOKEN_LPAREN
%token TOKEN_RPAREN
%token TOKEN_PLUS
%token TOKEN_MULTIPLY
%token TOKEN_MINUS
%token <value> TOKEN_NUMBER
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


 
%type <expression> expr
 
%%
 
input: 
	expr { *expression = $1; }
    ;
 
expr:
    expr[L] TOKEN_PLUS expr[R] { $$ = createOperation( ePLUS, $L, $R ); }

    | expr[L] TOKEN_MULTIPLY expr[R] { $$ = createOperation( eMULTIPLY, $L, $R ); }
    | TOKEN_LPAREN expr[E] TOKEN_RPAREN { $$ = $E; }
    | TOKEN_NUMBER { $$ = createNumber($1); }
    ;
    
/*
 * 
 */
 
%%
