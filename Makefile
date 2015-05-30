potatoParser.tab.c potatoParser.tab.h: potatoParser.y
	bison -d potatoParser.y

lex.yy.c: potatoLexer.l potatoParser.tab.h
	flex potatoLexer.l

potatoParser: lex.yy.c potatoParser.tab.c potatoParser.tab.h
	g++ potatoParser.tab.c lex.yy.c -lfl -o potatoParser
