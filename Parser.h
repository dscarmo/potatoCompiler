/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 18 "Parser.y" /* yacc.c:1909  */

 
#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void* yyscan_t;
#endif
 

#line 53 "Parser.h" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOKEN_PLUS = 258,
    TOKEN_MULTIPLY = 259,
    TOKEN_AND = 260,
    TOKEN_BREAK = 261,
    TOKEN_DO = 262,
    TOKEN_ELSE = 263,
    TOKEN_ELSEIF = 264,
    TOKEN_END = 265,
    TOKEN_FALSE = 266,
    TOKEN_FOR = 267,
    TOKEN_FUNCTION = 268,
    TOKEN_IF = 269,
    TOKEN_IN = 270,
    TOKEN_LOCAL = 271,
    TOKEN_NIL = 272,
    TOKEN_NOT = 273,
    TOKEN_OR = 274,
    TOKEN_REPEAT = 275,
    TOKEN_RETURN = 276,
    TOKEN_THEN = 277,
    TOKEN_TRUE = 278,
    TOKEN_UNTIL = 279,
    TOKEN_WHILE = 280,
    TOKEN_ID = 281,
    TOKEN_COMMENT = 282,
    TOKEN_STRING = 283,
    TOKEN_LPAREN = 284,
    TOKEN_RPAREN = 285,
    TOKEN_MINUS = 286,
    TOKEN_NUMBER = 287,
    TOKEN_DIV = 288,
    TOKEN_MOD = 289,
    TOKEN_HAT = 290,
    TOKEN_CROSS = 291,
    TOKEN_EQUAL = 292,
    TOKEN_AEQUAL = 293,
    TOKEN_NEQUAL = 294,
    TOKEN_LEQUAL = 295,
    TOKEN_GEQUAL = 296,
    TOKEN_LESSER = 297,
    TOKEN_GREATER = 298,
    TOKEN_ASSIGN = 299,
    TOKEN_LKEY = 300,
    TOKEN_RKEY = 301,
    TOKEN_LBOX = 302,
    TOKEN_RBOX = 303,
    TOKEN_SEMICOLON = 304,
    TOKEN_TWOPOINTS = 305,
    TOKEN_COLON = 306,
    TOKEN_POINT = 307,
    TOKEN_DOUBLEPOINT = 308,
    TOKEN_ETC = 309
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 35 "Parser.y" /* yacc.c:1909  */

    int value;
    SExpression *expression;

#line 125 "Parser.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (SExpression **expression, yyscan_t scanner);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
