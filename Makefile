#
# UFRGS - Compiladores B - Marcelo Johann - 2009/2 - Etapa 1
#
# Makefile for single compiler call
# All source files must be included from code embedded in scanner.l
# In our case, you probably need #include "hash.c" at the beginning
# and #include "main.c" in the last part of the scanner.l
#

#etapa1: lex.yy.c
#	gcc -o etapa1 lex.yy.c
#lex.yy.c: scanner.l
#	lex scanner.l
etapa2: lex.yy.o main.o hash.o y.tab.o
	gcc -o etapa2 lex.yy.o main.o hash.o y.tab.o
main.o: main.c lex.yy.c
	gcc -c main.c
hash.o: hash.c
	gcc -c hash.c
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c
lex.yy.c: scanner.l y.tab.o
	lex --header-file=lex.yy.h scanner.l
y.tab.o: y.tab.c
	gcc -c y.tab.c
y.tab.c: parser.y
	yacc -d parser.y

clean:
	rm lex.yy.c lex.yy.h y.tab.c y.tab.h *.o etapa2




