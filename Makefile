potatoParser.tab.c potatoParser.tab.h: potatoParser.y
	bison -d potatoParser.y

lex.yy.c: potatoLexer.l potatoParser.tab.h
	flex potatoLexer.l

potatoParser: clean lex.yy.c potatoParser.tab.c potatoParser.tab.h
	g++ potatoParser.tab.c lex.yy.c ast.c potatoCodeGen.c -lfl -o potatoParser
	
clean:
	rm -f potatoParser.tab.c potatoParser.tab.h lex.yy.c potatoParser 
