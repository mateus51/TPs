
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     COMMA = 258,
     COLON = 259,
     SEMICOLON = 260,
     PROC = 261,
     SIN = 262,
     LOG = 263,
     COS = 264,
     ORD = 265,
     ABS = 266,
     SQRT = 267,
     EXP = 268,
     EOFILE = 269,
     EOLN = 270,
     PROGRAM = 271,
     INTEGER = 272,
     REAL = 273,
     BOOLEAN = 274,
     CHAR = 275,
     VALUE = 276,
     REFERENCE = 277,
     BEGIN_TOK = 278,
     END = 279,
     IF = 280,
     THEN = 281,
     ELSE = 282,
     REPEAT = 283,
     UNTIL = 284,
     READ = 285,
     WRITE = 286,
     FALSE = 287,
     TRUE = 288,
     ATRIB = 289,
     LPAR = 290,
     RPAR = 291,
     NOT = 292,
     EQ = 293,
     NE = 294,
     GT = 295,
     LT = 296,
     GE = 297,
     LE = 298,
     ADDOP = 299,
     MULOP = 300,
     ID = 301,
     INTEGER_CONSTANT = 302,
     REAL_CONSTANT = 303,
     CHAR_CONSTANT = 304
   };
#endif
/* Tokens.  */
#define COMMA 258
#define COLON 259
#define SEMICOLON 260
#define PROC 261
#define SIN 262
#define LOG 263
#define COS 264
#define ORD 265
#define ABS 266
#define SQRT 267
#define EXP 268
#define EOFILE 269
#define EOLN 270
#define PROGRAM 271
#define INTEGER 272
#define REAL 273
#define BOOLEAN 274
#define CHAR 275
#define VALUE 276
#define REFERENCE 277
#define BEGIN_TOK 278
#define END 279
#define IF 280
#define THEN 281
#define ELSE 282
#define REPEAT 283
#define UNTIL 284
#define READ 285
#define WRITE 286
#define FALSE 287
#define TRUE 288
#define ATRIB 289
#define LPAR 290
#define RPAR 291
#define NOT 292
#define EQ 293
#define NE 294
#define GT 295
#define LT 296
#define GE 297
#define LE 298
#define ADDOP 299
#define MULOP 300
#define ID 301
#define INTEGER_CONSTANT 302
#define REAL_CONSTANT 303
#define CHAR_CONSTANT 304




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{


	int integer;
	float real;
	char *string;



} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


