%{
/*
 * Description: Lua lexer for Trabalho de Compiladores
 * Author: Diedre e Daniel
 */
#include "Expression.h"
#include "Parser.h"
 
#include <stdio.h>
%}

%option outfile="Lexer.c" header-file="Lexer.h"
%option warn nodefault
 
%option reentrant noyywrap never-interactive nounistd
%option bison-bridge

number		[0-9]+
ID          [a-zA-Z][a-zA-Z0-9]*
blank       [ \r\n\t]*
comment     "/*".*"*/"|"--".*
string      \"(\\.|[^"])*\"

%%
and 		{printf("Token: %s Type: AND\n", yytext); return TOKEN_AND;}
break 		{printf("Token: %s Type: BRK\n", yytext);return TOKEN_BREAK;}
do    		{printf("Token: %s Type: DO\n", yytext);return TOKEN_DO;}
else		{printf("Token: %s Type: ELS\n", yytext);return TOKEN_ELSE;}
elseif		{printf("Token: %s Type: ELSIF\n", yytext);return TOKEN_ELSEIF;}
end			{printf("Token: %s Type: END\n", yytext);return TOKEN_END;}
false		{printf("Token: %s Type: FALSE\n", yytext);return TOKEN_FALSE;}
for			{printf("Token: %s Type: FOR\n", yytext);return TOKEN_FOR;}
function 	{printf("Token: %s Type: FUNC\n", yytext);return TOKEN_FUNCTION;}
if			{printf("Token: %s Type: IF\n", yytext);return TOKEN_IF;}
in			{printf("Token: %s Type: IN\n", yytext);return TOKEN_IN;}	
local 		{printf("Token: %s Type: LOCAL\n", yytext);return TOKEN_LOCAL;}
nil			{printf("Token: %s Type: NULL\n", yytext);return TOKEN_NIL;}
not			{printf("Token: %s Type: NOT\n", yytext);return TOKEN_NOT;}
or			{printf("Token: %s Type: OR\n", yytext);return TOKEN_OR;}
repeat		{printf("Token: %s Type: REPEAT\n", yytext);return TOKEN_REPEAT;}
return		{printf("Token: %s Type: RETURN\n", yytext);return TOKEN_RETURN;}
then		{printf("Token: %s Type: THEN\n", yytext);return TOKEN_THEN;}
true        {printf("Token: %s Type: TRUE\n", yytext);return TOKEN_TRUE;}
until	 	{printf("Token: %s Type: UNTIL\n", yytext);return TOKEN_UNTIL;}
while		{printf("Token: %s Type: WHILE\n", yytext);return TOKEN_WHILE;}

{ID}   		{printf("Token: %s Type: ID \n", yytext);return TOKEN_ID;}
{number} 	{printf("Token: %s Type: NUMBER \n", yytext);sscanf(yytext, "%d", &yylval->value); return TOKEN_NUMBER; }


{comment}   {printf("Comment detectado, ignorando. \n");return TOKEN_COMMENT;}
{string} 	{printf("Token: %s Type: STRING \n", yytext); return TOKEN_STRING;} 
"+"			{printf("Token: %s Type: PLUS\n", yytext);return TOKEN_PLUS;}
"-"			{printf("Token: %s Type: SUB\n", yytext);return TOKEN_MINUS;}
"*"			{printf("Token: %s Type: ADD\n", yytext);return TOKEN_MULTIPLY;}
"/"			{printf("Token: %s Type: DIV\n", yytext);return TOKEN_DIV;}
"%"			{printf("Token: %s Type: MOD\n", yytext);return TOKEN_MOD;}
"^"			{printf("Token: %s Type: HAT\n", yytext);return TOKEN_HAT;}
"#"			{printf("Token: %s Type: CROSS\n", yytext);return TOKEN_CROSS;}
"=="		{printf("Token: %s Type: EQUAL\n", yytext);return TOKEN_EQUAL;}
"~="		{printf("Token: %s Type: AEQUAL\n", yytext);return TOKEN_AEQUAL;}
"<="		{printf("Token: %s Type: LEQUAL\n", yytext);return TOKEN_LEQUAL;}
">="		{printf("Token: %s Type: GEQUAL\n", yytext);return TOKEN_GEQUAL;}
"<"			{printf("Token: %s Type: LESS\n", yytext);return TOKEN_LESSER;}
">"			{printf("Token: %s Type: MORE\n", yytext);return TOKEN_GREATER;}
"="			{printf("Token: %s Type: EQUAL\n", yytext);return TOKEN_ASSIGN;}
"("			{printf("Token: %s Type: LPAREN\n", yytext);return TOKEN_LPAREN;}
")"			{printf("Token: %s Type: RPAREN\n", yytext);return TOKEN_RPAREN;}
"{"			{printf("Token: %s Type: LKEY\n", yytext);return TOKEN_LKEY;}
"}"			{printf("Token: %s Type: RKEY\n", yytext);return TOKEN_RKEY;}
"["			{printf("Token: %s Type: RBOX\n", yytext);return TOKEN_RBOX;}
"]"			{printf("Token: %s Type: LBOX\n", yytext);return TOKEN_LBOX;}
";"			{printf("Token: %s Type: SEMICOLON\n", yytext);return TOKEN_SEMICOLON;}
":"			{printf("Token: %s Type: TWOPOINTS\n", yytext);return TOKEN_TWOPOINTS;}
","			{printf("Token: %s Type: COLON\n", yytext);return TOKEN_COLON;}
"."     	{printf("Token: %s Type: POINT\n", yytext);return TOKEN_POINT;}
".."		{printf("Token: %s Type: TWOPOINTS\n", yytext);return TOKEN_DOUBLEPOINT;}
"..." 		{printf("Token: %s Type: ETC\n", yytext);return TOKEN_ETC;}
{blank}     ;
.			{printf("Lexical error! %s not recognized \n", yytext);}
  
%%

int yyerror(const char *msg) {
    fprintf(stderr,"Error:%s\n",msg); return 0;
}
