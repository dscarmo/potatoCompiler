%{
#include <iostream>
#include "ast.h"
#include "potatoParser.tab.h"

using namespace std;
#define YY_DECL extern "C" int yylex()
int line_num = 1;
int parCounter = 0;
%}

number		[0-9]+
ID          [a-zA-Z][a-zA-Z0-9]*
blank       [ \r\n\t]*
comment     "/*".*"*/"|"--".*
string      \"(\\.|[^"])*\"

%%
and 		{printf("Token: %s Type: AND\n", yytext); return TOKEN_AND;}
do    		{printf("Token: %s Type: DO\n", yytext);return TOKEN_DO;}
else		{printf("Token: %s Type: ELSE\n", yytext);return TOKEN_ELSE;}
end			{printf("Token: %s Type: END\n", yytext);return TOKEN_END;}
for			{printf("Token: %s Type: FOR\n", yytext);return TOKEN_FOR;}
function 	{printf("Token: %s Type: FUNC\n", yytext);return TOKEN_FUNCTION;}
if			{printf("Token: %s Type: IF\n", yytext);return TOKEN_IF;}
not			{printf("Token: %s Type: NOT\n", yytext);return TOKEN_NOT;}
or			{printf("Token: %s Type: OR\n", yytext);return TOKEN_OR;}
then		{printf("Token: %s Type: THEN\n", yytext);return TOKEN_THEN;}
while		{printf("Token: %s Type: WHILE\n", yytext);return TOKEN_WHILE;}
var 		{printf("Token: %s Type: VAR\n", yytext);return TOKEN_VAR;}

{ID}   		{printf("Token: %s Type: ID \n", yytext); yylval.sval = strdup(yytext); return TOKEN_ID;}
{number} 	{printf("Token: %s Type: NUMBER \n", yytext); yylval.ival = atoi(yytext); return TOKEN_NUMBER; }


{comment}   {printf("Comment detectado, ignorando. \n");}
{string} 	{printf("Token: %s Type: STRING \n", yytext); yylval.sval = strdup(yytext); return TOKEN_STRING;} 
"+"			{printf("Token: %s Type: PLUS\n", yytext);return TOKEN_PLUS;}
"-"			{printf("Token: %s Type: SUB\n", yytext);return TOKEN_MINUS;}
"*"			{printf("Token: %s Type: ADD\n", yytext);return TOKEN_MULTIPLY;}
"/"			{printf("Token: %s Type: DIV\n", yytext);return TOKEN_DIV;}
"#"			{printf("Token: %s Type: CROSS\n", yytext);return TOKEN_CROSS;}
"=="		{printf("Token: %s Type: EQUAL\n", yytext);return TOKEN_EQUAL;}
"~="		{printf("Token: %s Type: AEQUAL\n", yytext);return TOKEN_AEQUAL;}
"<="		{printf("Token: %s Type: LEQUAL\n", yytext);return TOKEN_LEQUAL;}
">="		{printf("Token: %s Type: GEQUAL\n", yytext);return TOKEN_GEQUAL;}
"<"			{printf("Token: %s Type: LESS\n", yytext);return TOKEN_LESSER;}
">"			{printf("Token: %s Type: MORE\n", yytext);return TOKEN_GREATER;}
"="			{printf("Token: %s Type: ASSIGN\n", yytext);return TOKEN_ASSIGN;}
"("			{printf("Token: %s Type: LPAREN\n", yytext);parCounter++;return TOKEN_LPAREN;}
")"			{printf("Token: %s Type: RPAREN\n", yytext);parCounter--;return TOKEN_RPAREN;}
"{"			{printf("Token: %s Type: LKEY\n", yytext);return TOKEN_LKEY;}
"}"			{printf("Token: %s Type: RKEY\n", yytext);return TOKEN_RKEY;}
"["			{printf("Token: %s Type: RBOX\n", yytext);return TOKEN_RBOX;}
"]"			{printf("Token: %s Type: LBOX\n", yytext);return TOKEN_LBOX;}
";"			{printf("Token: %s Type: SEMICOLON\n", yytext);return TOKEN_SEMICOLON;}
":"			{printf("Token: %s Type: TWOPOINTS\n", yytext);return TOKEN_TWOPOINTS;}
","			{printf("Token: %s Type: COLON\n", yytext);return TOKEN_COLON;}
"."     	{printf("Token: %s Type: POINT\n", yytext);return TOKEN_POINT;}

\n			{++line_num;}
\n\n			{line_num=line_num+2;}
\n\n\n			{line_num=line_num+3;}
\n\n\n\n		{line_num=line_num+4;}
\n\n\n\n\n		{line_num=line_num+5;}
{blank}     ;
.			{printf("Lexical error! %s not recognized \n", yytext);}
  
